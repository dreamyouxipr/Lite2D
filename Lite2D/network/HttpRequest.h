#ifndef __HTTPREQUEST__
#define __HTTPREQUEST__



#include "../base/Ref.h"
#include "../3party/curl/curl.h"
#include <functional>

class HttpRequest;
class HttpRespone;

enum class HttpType
{
	POST,
	GET,
};



typedef std::function<void(HttpRequest*request, HttpRespone*respone)>
HttpCallBack;//the call back std::function

/**
 * @brief http request
 */
class DLL HttpRequest :public Ref
{
public:

	/**
	 * @brief set url
	 */
	void setUrl(const std::string&_url);

	/**
	 * @return the url
	 */
	const std::string &getUrl()const;

	/**
	 * @brief set http type (get,post)
	 */
	void setHttpType(HttpType _type);

	/**
	 * @return thr http type
	 */
	HttpType getHttpType()const;

	void autorelease() = delete;

	/**
	 * @brief set curl easy_handle
	 */
	void setCURLhandle(CURL*handle);

	/**
	 * @return thr curl easy_handle
	 */
	CURL*getCURLhandle()const;

	/**
	 * @brief set http callback
	 * @warning you should not release the respone  and request in your callback function
	 */
	void setCallback(const HttpCallBack& _callback);

	/**
	 * @return the callback
	 */
	const HttpCallBack& getHttpCallback();

	/**
	 * @brief set post data for post type
	 */
	void setPostData(const std::string& data);

	/**
	 * @return post data
	 */
	const std::string & getPostData()const;


	~HttpRequest();

	/**
	 * @brief create a instance of HttpRequest
	 */
	static HttpRequest*create(const std::string& _url = "", HttpType _type = HttpType::GET);

private:
	HttpRequest(const std::string& _url, HttpType _type);
	CURL* easy_handle;
	std::string _postdata;

	std::string _url;
	HttpType _type;// http type post and get
	HttpCallBack _callback;

};














#endif


