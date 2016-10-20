#ifndef __DIRTCTOR__
#define __DIRTCTOR__

#include "../Macros.h"

#include "Ref.h"
#include "Scheduler.h"
#include "GLView.h"
#include "windows.h"


class Application;
class Scene;
class EventDispatcher;
class RenderCmdQueue;

class  DLL Director :public Ref
{
public:

	/**
	 * @return the instance
	 */
	static Director*getInstance();

	/**
	 * @return the only scheduler in game
	 * @note the scheduler has only one of the game in Director
	 */
	Scheduler*getScheduler()const;

	/**
	 * @brief set opengl window
	 */
	void setGLView(GLView*glview);
	
	GLView* getGLView()
	{
		return this->_glview;
	}
	RenderCmdQueue *getRenderCmdQueue()
	{
		return _renderQueue;
	}
	float getFPS()const;


	float getRenderTime()const;

	/**
	 * @brief set display status  (FPS render time)
	 */
	void setShowDisplayStatus(bool b);


	/**
	 * @brief run with a new scene
	 * @note this func will call Scene::init();
	 */
	void runWithScene(Scene*scene);


	const Vec2& getWindowSize()const;

	/**
	* @brief get the two frame delta time
	*/
	const float getDeltaTime()const;



	/**
	 * @brief exit game
	 */
	void end();
	bool isEnd()const;
	virtual ~Director();

	EventDispatcher*getEventDispatcher()const;

	RenderCmdQueue * getRenderCmdQueue()const
	{
		return this->_renderQueue;
	}
private:

	RenderCmdQueue *_renderQueue;

	void init(Application*app);
	bool _isend;
	bool _ShowDisplayStatus;

	float _fps;
	float _renderTime;
	float _deltaTime;
	void setFPS(float t);
	void setRenderTime(float t);

	//friend class Application;
	friend class Application_Win32;



	Director();
	/**
	* @brief game  main loop
	* each frame loop
	*/
	void mainLoop();

	/**
	* @brief set the delta time of two frame
	*/
	void setDeltaTime(float delta);

	friend class Application;


	/**
	 * @brief draw scene
	 */
	void draw();


	Scheduler*_scheduler;// the scheduler
	GLView*_glview;//gl view
	EventDispatcher*_eventdispatcher;


	LARGE_INTEGER nFreq;
	LARGE_INTEGER perFrame;

	LARGE_INTEGER nLast;//render time
	LARGE_INTEGER nNow; //render time

public:
	void addFuncToMainThread(const std::function<void()>& func);

	void processOtherThreadFunc();
private:
	Scene*_currentscene;//current scene
	std::vector< std::function<void()>  > _queue_other_thread_func;

};











#endif


