#include"HttpRequest.h"

HttpRequest*HttpRequest::create(const std::string& _url, HttpType _type)
{
	HttpRequest*ins = new HttpRequest(_url,_type);



	return ins;
}



void   HttpRequest::setUrl(const std::string&_url)
{
	this->_url = _url;

}


const std::string &HttpRequest::getUrl()const
{
	return _url;

}

void HttpRequest::setHttpType(HttpType _type)
{
	this->_type = _type;

}


HttpType HttpRequest::getHttpType()const
{
	return this->_type;
}




void HttpRequest::setCURLhandle(CURL*handle)
{
	this->easy_handle = handle;
}


CURL*HttpRequest::getCURLhandle()const
{
	return easy_handle;
}


void HttpRequest::setCallback(const HttpCallBack& _callback)
{
	this->_callback = _callback;

}


const  HttpCallBack& HttpRequest::getHttpCallback()
{
	return _callback;
}


void  HttpRequest::setPostData(const std::string& data)
{

	this->_postdata = data;

}

const std::string & HttpRequest::getPostData()const
{

	return _postdata;
}


HttpRequest::HttpRequest(const std::string& _url, HttpType _type)
{
	easy_handle = nullptr;
	this->_type = _type;
	this->_url = _url;
}

HttpRequest::~HttpRequest()
{
	if (easy_handle)
	{
		curl_easy_cleanup(easy_handle);
	}
}

