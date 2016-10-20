#include"Application.h"
#include "conio.h"
#include <stdlib.h>
#include"time.h"
#include<functional>
#include "vector"


#include "../glut.h"
#include "../glfw3.h"
#include <thread>


#include <chrono>
#include <iostream>

#include "windows.h"
#include "Director.h"

using namespace std;
#include "../Lite2D.h"

Application::Application() :
Application("Lite2D", 1300, 600)
{



}




Application::Application(const std::string&name, int width, int height)
{
	// init all instance

	Director::getInstance();
	AutoReleasePool::getInstance();
	AudioEngine::getInstance();
	TextureCache::getInstance();
	AnimationCache::getInstance();
	PlayerSave::getInstance();
	HttpClient::getInstance();


	this->name = name;
	this->width = width;
	this->height = height;
	Director::getInstance()->init(this);
}














void Application_Win32::init()
{


	//auto glview = GLView::create("Lite2D", 1300, 700);
	//	Director::getInstance()->setGLView(glview);



}
int Application_Win32::run()
{

	//this->init();

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;
	LARGE_INTEGER perFrame;

	QueryPerformanceFrequency(&nFreq);
	perFrame.QuadPart = (LONGLONG)(1.0 / 60 * nFreq.QuadPart);

	auto director = Director::getInstance();
	director->perFrame.QuadPart = perFrame.QuadPart;
	director->nFreq.QuadPart = nFreq.QuadPart;

	QueryPerformanceCounter(&nLast);

	Director::getInstance()->getRenderCmdQueue()->addCustomFuncToRenderThread([]()
	{
		Director::getInstance()->getRenderCmdQueue()->setVerticalSynchronization(false);
	});

	while (!director->isEnd())
	{

		QueryPerformanceCounter(&nNow);
		if (nNow.QuadPart - nLast.QuadPart > perFrame.QuadPart)
		{
			director->mainLoop();

			float delta = (float)(nNow.QuadPart - nLast.QuadPart) / (float)nFreq.QuadPart;

			director->setFPS(1.0f / delta);
			director->setDeltaTime(delta);//set each frame  delta
			///cout << delta << endl;;
			nLast.QuadPart = nNow.QuadPart;
			//	Sleep(100);

		}
		else
		{
		//	std::this_thread::sleep_for(std::chrono::microseconds(0));
		}
	}



	return 0;
}