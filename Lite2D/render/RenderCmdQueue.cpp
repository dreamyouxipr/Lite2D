#include "RenderCmdQueue.h"
#include "RenderCmd.h"
#define  DEFAULT_FPS 120

using namespace std;

static atomic<int> _Render_Fps(0);

static LARGE_INTEGER perFrame, nFreq;


static void   ThreadFunc(RenderCmdQueue * reder)
{
	Director::getInstance()->getGLView()->init(); // init gl in render thread 

	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;

	QueryPerformanceFrequency(&nFreq);
	perFrame.QuadPart = (LONGLONG)(1.0 / DEFAULT_FPS * nFreq.QuadPart);

	QueryPerformanceCounter(&nLast);

	float delta = 0.0f;
	while (true)
	{
		QueryPerformanceCounter(&nNow);
		if (nNow.QuadPart - nLast.QuadPart > perFrame.QuadPart)
		{
			delta = (float)(nNow.QuadPart - nLast.QuadPart) / (float)nFreq.QuadPart;
			reder->render();
			reder->setRenderFPS(1.0f / delta + 1);

			nLast.QuadPart = nNow.QuadPart;
		}
			//else
		{
			//std::this_thread::sleep_for(std::chrono::microseconds(0));
		}
	}

}

RenderCmdQueue* RenderCmdQueue::create()
{
	RenderCmdQueue*ret = new RenderCmdQueue;
	if (ENABLE_RENDER_THREAD)
	{
		std::thread t(&ThreadFunc, ret); t.detach();
	}
	else
	{
		Director::getInstance()->getGLView()->init(); // init gl in render thread 

	}
	return ret;

}


void RenderCmdQueue::addRenderCmd(RenderCmd*cmd)
{
	_mutex.lock();
	_queue.push_back(cmd);
	_mutex.unlock();
}


void RenderCmdQueue::clear()
{
	isNextTick = false;
	_mutex.lock();
	++_tick_status;
//	if (_tick_status > 5)
	{
		_tick_status = 0;
		auto dir = Director::getInstance();

		_cache_fps = dir->getFPS();
		_cache_last_fps = this->getRenderFPS();
		_cache_redertime = dir->getRenderTime();

	}
	this->clearAllRenderCmd();

	_mutex.unlock();
}

void  RenderCmdQueue::setVerticalSynchronization(bool enable)
{
	if (enable)
	{
		glfwSwapInterval(0xff);
	}
	else
	{
		glfwSwapInterval(0x0);
	}
}

void RenderCmdQueue::setMaxFPS(int fps)
{
	_mutex.lock();
	this->_max_fps = fps;
	perFrame.QuadPart = (LONGLONG)(1.0 / fps * nFreq.QuadPart);
	_mutex.unlock();
}

int RenderCmdQueue::getMaxFPS()const
{
	return _max_fps;
}


void RenderCmdQueue::NextTick()//thread safe 
{
	this->isNextTick = true;
	if (!ENABLE_RENDER_THREAD)
	{
		this->render();

	}
	else
	{

	}
}

void  RenderCmdQueue::clearAllRenderCmd()
{
	for (int i = 0; i < _queue.size(); i++)
	{
		if (_queue[i]->isDirty())
		{
			_queue[i]->release();
		}
	}
	_queue.clear();

}




void RenderCmdQueue::render()
{

	this->processOtherThreadFunc();

	do
	{
		if (isNextTick == false)break;

		std::lock_guard<std::mutex> lock(_mutex);
	//	cout << __FUNCTION__ << _queue.size() << endl;
		//	if (_queue.empty())break;

		glClear(GL_COLOR_BUFFER_BIT);
		//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_TEXTURE_2D);

		for (int i = 0; i < _queue.size(); i++)
		{
			RenderCmd *cmd = _queue[i];

			Texture2D*tex = cmd->tex_render;
			if (tex == nullptr)
			{
				auto it = tex_pool.find(cmd->tex->getFileName());
				if (it == tex_pool.end())
				{
					Texture2D* tex1 = new Texture2D;

					auto image = new Image;
					image->initWithFile(cmd->tex->getFileName());
					tex1->initWithImage(image);

					tex_pool[cmd->tex->getFileName()] = tex1;
					cmd->tex_render = tex1;
					tex = tex1;
				}
				else
				{
					tex = (*it).second;
				}
			}
	
			cmd->exec(tex);
			for (auto & tex : tex_pool)
			{

			///	cout << tex.second->getFileName() << endl;
			}




			/*
			RenderCmd *cmd = _queue[i];
			if (_queue[0]->tex_render)
			{
				cmd->exec(_queue[0]->tex_render);

			}
			else
			{
				static int oo = 0;
				oo++;
				cout << oo << endl;
				Texture2D* tex = new Texture2D;

				auto image = new Image;
				image->initWithFile(cmd->tex->getFileName());
				tex->initWithImage(image);

				_queue[0]->tex_render = tex;
			//	cmd->exec(tex);
			}
	*/






		}


		glDisable(GL_TEXTURE_2D);


		//render status
		auto dir = Director::getInstance();

		char str[100];
		glColor3f(1.0f, 1.0f, 1.0f);

		//show  pfs
		sprintf(str, "%.1f/%d", _cache_fps, _cache_last_fps);
		int n = strlen(str);
		glRasterPos3f(-1, -0.865, 0.0);
		for (int i = 0; i < n; i++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *(str + i));


		// show the sprite no of scene
		sprintf(str, "%d", _queue.size());
		n = strlen(str);
		glRasterPos3f(-1, -0.92, 0.0);
		for (int i = 0; i < n; i++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *(str + i));



		//show render time

		sprintf(str, "%f", _cache_redertime);
		//	str[7] = '\0';
		n = strlen(str);
		glRasterPos3f(-1, -0.975, 0.0);
		for (int i = 0; i < n; i++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *(str + i));
		Director::getInstance()->getGLView()->swapBuffers();


	} while (false);


}


void  RenderCmdQueue::processOtherThreadFunc()
{
	_mutex.lock();

	for (auto &func : _func)
	{
		Texture2D*  tex = func();
		tex_pool[tex->getFileName()] = tex;
	}
	_func.clear();

	for (auto &func : _func1)
	{
		func();
	}
	_func1.clear();

	_mutex.unlock();
}


void  RenderCmdQueue::addFuncToRenderThread(const std::function<Texture2D*(void)> &func)
{
	this->_mutex.lock();

	_func.push_back(func);
	this->_mutex.unlock();
}


void  RenderCmdQueue::addCustomFuncToRenderThread(const std::function<void(void)> &func)
{
	_mutex.lock();
	_func1.push_back(func);
	_mutex.unlock();
}
