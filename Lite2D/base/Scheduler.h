#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Ref.h"

#include <functional>
#include <vector>

typedef  std::function<void(void)> CallBack_0;




class  ScheduleCallBack :public Ref
{

public:
	static ScheduleCallBack*create(CallBack_0&callback, float each_time, int times, int tag);

public:
	CallBack_0 callback;
	int totalTimes;
	int currentTimes;

	float currentTime;
	float totalTime;

	ScheduleCallBack(int tag);
	int tag;

};








/**
 * @brief scheduler
 */
class DLL Scheduler :public Ref
{
public:

	/**
	 * @brief add a scheduler
	 * @param CallBack_0 the callback func [](void)
	 * @param each_time #float the time delay to callback function
	 * @param times #int the times for loop call. if is 0 then will not be add
	 * @param tag #int
	 */
	void addSchedule(CallBack_0  callback, float each_time, int times, int tag);

	/**
	* @brief add a scheduler
	* @param CallBack_0 the callback func [](void)
	* @param each_time #float the time delay to callback function
	* call times is 1 and tag is 0
	*/
	void addSchedule(CallBack_0  callback, float each_time);


	/**
	 * @brief remove scheduler
	 */
	void removeScheduler(int tag);

	/**
	 * @brief add a function (void update())which will been call each frame
	 * @note Ref must has a function named void update()
	 */
	void addSchedulerPerFrame(Ref*p);

	void removeSchedulerPerFrame(Ref*p);



	virtual ~Scheduler();

	//	void setInterval(float interval = 1 / 60.0);
private:
	friend class Director;
	void update(float dt = 0.0f);
	/**
	 * @return is exist the scheduler by tag ?
	 */
	bool isExist(int tag);
	void clear();
private:




	//the queue of Timer function
	std::vector<ScheduleCallBack*> _callback_queue;

	//the queue of function which will been call every frame.
	std::vector<Ref*> _callback_queue_every;
	float _interval = 1.0f / 60.0f;

};












#endif


