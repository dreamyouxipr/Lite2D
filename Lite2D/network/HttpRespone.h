#ifndef __HTTPREPSONE__
#define __HTTPRESPONE__


#include "HttpRequest.h"




enum class HttpStatus
{
	OK,//=0
	TIMEOUT,//=1
	NETERROR,//=2
	UNKNOWN
};



/**
 * @brief http respone
 */
class DLL HttpRespone :public Ref
{
public:

	/**
	 * @return the respone data
	 */
	void * getData();

	/**
	 * @return the respone data size
	 */
	int getSize()const;


	void setHttpRequest(HttpRequest*request);
	HttpRequest*getHttpRequest()const;
	/**
	 * @brief write data to the respone
	 */
	void writeData(void*data, int _size);

	void setHttpStatus(HttpStatus s);


	/**
	 * @return http status
	 */
	HttpStatus  getHttpStatus()const;

	void autorelease() = delete;

	~HttpRespone();

	/**
	 * @brief create a HttpRespone instance
	 */
	static HttpRespone*create();

	void setOriginHttpCode(int code);

	/**
	 * @return the http status such as 404 200 etc.
	 */
	int getOriginHttpCode()const;
private:
	void *_data;/// respone data
	//	int _code;
	HttpStatus _status;
	int _code_origin;
	HttpRespone();
	int _size; // respone data size
	HttpRequest*request;

};













#endif


