#include"HttpClient.h"
#include "HttpRequest.h"
#include "HttpRespone.h"
#include "../base/Director.h"

#include "../3party/curl/curl.h"



static int write_data(void *buffer, size_t size, size_t buffer_size, void *_respone)
{

	HttpRespone *respone = (HttpRespone*)_respone;


	HttpRequest*request = respone->getHttpRequest();

	respone->writeData(buffer, buffer_size);

	request->release();





	Director::getInstance()->addFuncToMainThread([=]()
	{
		const HttpCallBack & x = request->getHttpCallback();

		x(request, respone);

		request->release();
		respone->release();
	});




	return 0;
}


HttpClient* HttpClient::getInstance()
{
	static HttpClient*ins = nullptr;
	if (ins == nullptr)
	{
		ins = new HttpClient;
	}
	return ins;

}





void HttpClient::doRequest_curl(HttpRequest*request)
{

	HttpRespone *respone = HttpRespone::create();


	CURL*easy_handle = curl_easy_init();
	curl_easy_setopt(easy_handle, CURLOPT_URL, request->getUrl().c_str());
	curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, respone);
	curl_easy_setopt(easy_handle, CURLOPT_TIMEOUT, this->_time_read);
	curl_easy_setopt(easy_handle, CURLOPT_CONNECTTIMEOUT, this->_time_connect);



	// do post or get
	if (request->getHttpType() == HttpType::POST)
	{//post 

		curl_easy_setopt(easy_handle, CURLOPT_HTTPPOST, 1);
		curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDS, request->getPostData().c_str());
	}
	else if (request->getHttpType() == HttpType::GET)
	{//get

		curl_easy_setopt(easy_handle, CURLOPT_HTTPGET, 1);

	}
	respone->setHttpRequest(request);
	request->setCURLhandle(easy_handle);

	// perform
	auto succ = curl_easy_perform(easy_handle);

	// do http status code 404 200 etc.
	int code;
	curl_easy_getinfo(easy_handle, CURLINFO_RESPONSE_CODE, &code);

	std::cout << "  code:" << code << std::endl;
	switch (code)
	{
	case 200:
	{
				respone->setHttpStatus(HttpStatus::OK);
	}break;

	case  0:
	{//timeout such read and connect
			   respone->setHttpStatus(HttpStatus::TIMEOUT);
			   write_data(0, 0, 0, respone);

	}break;
	default:
	{//404 etc.
			   respone->setHttpStatus(HttpStatus::NETERROR);
	}
		break;
	}
	respone->setOriginHttpCode(code);

}






void HttpClient::workFunc()
{
	while (true)
	{
		HttpRequest* request;

		_mutex.lock();

		if (_queue_request.size() <= 0)
		{
			_condition.wait(_mutex);
		}
		request = _queue_request.front();
		_queue_request.pop();
		_mutex.unlock();

		//	log("net thread  %d", _queue_request.size());

		this->doRequest_curl(request);


	}

}




HttpClient::HttpClient()
{
	this->_time_connect = 5;
	this->_time_read = 10;
	curl_global_init(CURL_GLOBAL_WIN32);

	auto t = std::thread([=]
	{
		this->workFunc();
	});


	t.detach();
}



void HttpClient::send(HttpRequest*request)
{
	request->retain();

	_mutex.lock();
	_queue_request.push(request);
	_mutex.unlock();

	_condition.notify_one();


}


HttpClient::~HttpClient()
{
	_condition.notify_all();
}
