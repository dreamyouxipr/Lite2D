#ifndef __HTTPCLIENT__
#define __HTTPCLIENT__



#include "../base/Ref.h"

#include <queue>

#include <thread>
#include <mutex>
#include <condition_variable>




class HttpRequest;
class HttpRespone;


/**
 * @brief http client
 * you can via this class for post and get
 */
class DLL HttpClient :public Ref
{

public:
	/**
	 * @brief send a request
	 */
	void send(HttpRequest*request);

	HttpClient();
	~HttpClient();


	/**
	 * @return the instance
	 */
	static HttpClient*getInstance();


	
	void setTimeoutForConnect(int t)
	{
		this->_time_connect = t;
	}

	void setTimeoutForRead(int t)
	{
		this->_time_read = t;
	}


private:

	std::queue<HttpRequest*>_queue_request;


	/**
	 * @brief the http work thread function
	 */
	void workFunc();

 
	/**
	 * @brief do post and get by curl
	 */
	void doRequest_curl(HttpRequest*request);


	std::condition_variable_any _condition;
	std::mutex _mutex;

	int _time_connect;
	int _time_read;


};










#endif


