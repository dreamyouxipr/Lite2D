#ifndef __RENDERCMD_QUEUE__
#define __RENDERCMD_QUEUE__



#include "../glut.h"
#include "../glfw3.h"
#include "../math/Math.h"
#include <vector>
#include "../base/Ref.h"
#include <atomic>
#include <thread>
#include <mutex>
#include "../base/Director.h"
#include "Texture2D.h"
#include <unordered_map>
#include <functional>


#define  ENABLE_RENDER_THREAD true




class RenderCmd;

class RenderCmdQueue
{

public:

	void addFuncToRenderThread(const std::function<Texture2D*(void)> &func);
	void addCustomFuncToRenderThread(const std::function<void(void)> &func);
private:

	std::unordered_map<std::string, Texture2D*> tex_pool;

	std::vector<std::function<Texture2D*(void)>> _func;
	std::vector <std::function<void(void)>> _func1;
	void processOtherThreadFunc();



	std::mutex _mutex;

public:

	void setRenderFPS(int fps)
	{
		_current_fps = fps;
	}
	int getRenderFPS()const
	{
		return _current_fps;
	}
	static RenderCmdQueue*create();
	void addRenderCmd(RenderCmd*cmd);

	void clear();
	void NextTick();//thread safe 


	void render();
	void setVerticalSynchronization(bool enable);
	void setMaxFPS(int fps);
	int getMaxFPS()const;

private:
	int _max_fps;
	int _current_fps;
	std::atomic<bool> isNextTick = false;
	std::vector<RenderCmd*> _queue;

	void clearAllRenderCmd();

	RenderCmdQueue()
	{
		_queue.reserve(5000);
	}
	int _tick_status = 0;
	float _cache_fps = 0.0f;
	int _cache_last_fps=0;
	float _cache_redertime = 0.0f;

};






#endif


