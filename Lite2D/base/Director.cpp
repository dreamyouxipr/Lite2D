#include"Director.h"
#include "AutoReleeasePool.h"

#include "../glut.h"
#include "../glfw3.h"
#include <thread>
#include "../2d//Scene.h"
#include "EventDispatcher.h"
#include "../render/TextureCache.h"
#include "../render/RenderCmd.h"
#include "../render/RenderCmdQueue.h"
#include <mutex>
#include "Application.h"
static std::mutex _mutex_mainThread;

static Director* __instance = nullptr;


Director* Director::getInstance()
{
	if (__instance == nullptr)
	{
		__instance = new Director;

	}
	return __instance;


}


Director::~Director()
{
	//clear all refs in Pool;

	AutoReleasePool::getInstance()->clear();


	_currentscene->release();

	_scheduler->release();

	_glview->release();

	_eventdispatcher->release();

	TextureCache::getInstance()->release();


}

Director::Director() :
_glview(0),
_ShowDisplayStatus(true),
_isend(false),
_currentscene(nullptr)
{



}


void Director::init(Application*app)
{

	_glview = GLView::create(app->name, app->width, app->height);
	_renderQueue = RenderCmdQueue::create();

	_scheduler = new Scheduler;
	_eventdispatcher = EventDispatcher::create();
	_renderQueue->addCustomFuncToRenderThread([=]()
	{
	
		GLView::printHardWareInfo();
	});

	
}



void Director::addFuncToMainThread(const std::function<void()>& func)
{
	_mutex_mainThread.lock();
	_queue_other_thread_func.push_back(func);
	_mutex_mainThread.unlock();

}


void Director::processOtherThreadFunc()
{
	

	// 	for (int i = 0;i<_queue_other_thread_func.size(); ++i)
	// 	{
	// 		_queue_other_thread_func[i]();
	// 	}


	_mutex_mainThread.lock();

	for (int i = 0; i < _queue_other_thread_func.size(); ++i)
	{
		_queue_other_thread_func[i]();

	}
	_queue_other_thread_func.clear();

	_mutex_mainThread.unlock();
}


void Director::end()
{
	_isend = true;

}

bool Director::isEnd()const
{
	return _isend;
}

void Director::mainLoop()
{
	//process other thread callback func
	this->processOtherThreadFunc();

	_scheduler->update();

	QueryPerformanceCounter(&nLast);

	//_glview->pollEvents();
	//_eventdispatcher->pollEvents();

	_renderQueue->addCustomFuncToRenderThread([&](void)->void
	{
		_glview->pollEvents();
		_eventdispatcher->pollEvents();
	});
	

	{
	//	_glview->render();// gl render
	//	glEnable(GL_TEXTURE_2D);
		_renderQueue->clear();
		_currentscene->drawScene();//draw current scene ,add cmd to queue
		_renderQueue->NextTick();


		//glDisable(GL_TEXTURE_2D);
		//while (1)
		{
		}
	}


	QueryPerformanceCounter(&nNow);

	double x = (double)(nNow.QuadPart - nLast.QuadPart) / (double)nFreq.QuadPart;
	this->setRenderTime(x);

	if (_ShowDisplayStatus)
	{
	//	_glview->renderDisplayStatus();//show display status
	}

	//_glview->swapBuffers();




	//clear all refs in Pool;
	AutoReleasePool::getInstance()->clear();


}


void Director::setGLView(GLView*glview)
{
	_glview = glview;

}

void Director::setShowDisplayStatus(bool b)
{
	_ShowDisplayStatus = b;
}

void Director::draw()
{




}


const float Director::getDeltaTime()const
{
	return this->_deltaTime;

}

void Director::setDeltaTime(float delta)
{
	this->_deltaTime = delta;
}


Scheduler*Director::getScheduler()const
{
	return _scheduler;
}


float Director::getFPS()const
{
	return _fps;

}

float Director::getRenderTime()const
{
	return _renderTime;
}


void Director::setFPS(float t)
{
	_fps = t;
}

void Director::setRenderTime(float t)
{
	_renderTime = t;
}


void Director::runWithScene(Scene*scene)
{
	_scheduler->clear();

	if (_currentscene)
	{
		_currentscene->release();
	}
	_currentscene = scene;

	ASSERT(_currentscene->init(), "init scene error");

	;

}


const Vec2& Director::getWindowSize()const
{
	return _glview->getWindowSize();
}

EventDispatcher* Director::getEventDispatcher()const
{
	return _eventdispatcher;
}


