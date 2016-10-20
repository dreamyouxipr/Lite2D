#ifndef __APPLICATION__
#define __APPLICATION__

#include "../Macros.h"


class   DLL  Application
{
public:
	virtual int run() = 0;
	Application();
	virtual void init() = 0;

	Application(const std::string&name, int width, int height);
private:
	std::string name;
	int width;
	int height;
	friend class Director;
};

class Director;

class DLL Application_Win32 :public Application
{
public:
	virtual int run()override;
	virtual void init()override;
	Application_Win32(const std::string&name, int width, int height)
		:Application(name, width, height)
	{

	}
	Application_Win32() :Application(){}

};



class DLL Application_Linux :public Application
{
public:
	virtual int run()override{ return 0; };



};



#endif


