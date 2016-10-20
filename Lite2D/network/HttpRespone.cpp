#include"HttpRespone.h"



void * HttpRespone::getData()
{
	return _data;
}


int  HttpRespone::getSize()const
{
	return _size;
}


void HttpRespone::setHttpRequest(HttpRequest*request)
{
	this->request = request;
}


HttpRequest* HttpRespone::getHttpRequest()const
{
	return request;
}


void  HttpRespone::writeData(void*data, int _size)
{
	_data = new char[_size + 1];

	memset(_data, 0, _size + 1);

	memcpy(_data, data, _size);

}


HttpRespone::HttpRespone()
{
	_data = nullptr;
}

HttpRespone::~HttpRespone()
{
	if (_data)
	{
		delete _data;
	}
}


HttpRespone*HttpRespone::create()
{
	HttpRespone*ins = new HttpRespone;

	return ins;
}

void  HttpRespone::setHttpStatus(HttpStatus s)
{
	this->_status = s;
}


HttpStatus  HttpRespone::getHttpStatus()const
{
	return _status;
}


void  HttpRespone::setOriginHttpCode(int code)
{
	this->_code_origin = code;
}


int  HttpRespone::getOriginHttpCode()const
{
	return this->_code_origin;
}