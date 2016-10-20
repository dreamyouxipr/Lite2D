#include"Scheduler.h"



ScheduleCallBack::ScheduleCallBack(int tag)
{
	currentTime = 0.0f;
	totalTime = 0.0f;
	currentTime = 0.0f;
	currentTimes = 0;
	totalTimes = 0;
	this->tag = tag;

}

void Scheduler::clear()
{
	_callback_queue_every.clear();
	_callback_queue.clear();
}

ScheduleCallBack* ScheduleCallBack::create(CallBack_0&callback, float each_time, int times, int tag)
{
	auto ins = new ScheduleCallBack(tag);

	ins->callback = callback;
	ins->totalTimes = times;
	ins->totalTime = each_time;

	return ins;

}


void Scheduler::addSchedulerPerFrame(Ref*p)
{

	_callback_queue_every.push_back(p);

}


void Scheduler::update(float dt/* =0 */)
{
	//call function whild will been call each frame

	for (int i = 0; i < _callback_queue_every.size(); ++i)
	{
		_callback_queue_every[i]->update();
	}





	// Timer scheduler
	for (auto & callback : _callback_queue)
	{
		callback->currentTime += _interval;

		if (callback->currentTime >= callback->totalTime)
		{
			callback->currentTime = 0.0f;
			callback->callback();// call function
			++callback->currentTimes;
		}

	}



	for (auto iter = _callback_queue.begin(); iter != _callback_queue.end(); iter)
	{
		if ((*iter)->currentTimes >= (*iter)->totalTimes)
		{
			(*iter)->release();

			iter = _callback_queue.erase(iter);
		}
		else
		{
			++iter;
		}
	}


}


void Scheduler::addSchedule(CallBack_0  callback, float each_time, int times, int tag)
{
	_callback_queue.push_back(ScheduleCallBack::create(callback, each_time, times, tag));

}

void Scheduler::addSchedule(CallBack_0  callback, float each_time)
{
	_callback_queue.push_back(ScheduleCallBack::create(callback, each_time, 1, 0));

}



void Scheduler::removeScheduler(int tag)
{
	int _size = _callback_queue.size();

	auto iter = _callback_queue.begin();


	for (; iter != _callback_queue.end(); ++iter)
	{
		if ((*iter)->tag == tag)
		{
			break;
		}
	}

	if (iter == _callback_queue.end())
	{
		return;
	}

	_callback_queue.erase(iter);

}







void Scheduler::removeSchedulerPerFrame(Ref*p)
{
	auto iter =  std::find(_callback_queue_every.begin(), _callback_queue_every.end(), p);

	if (iter == _callback_queue_every.end())
	{
		return;
	}
	_callback_queue_every.erase(iter);

}



bool Scheduler::isExist(int tag)
{

	int _size = _callback_queue.size();

	auto iter = _callback_queue.begin();


	for (; iter != _callback_queue.end(); ++iter)
	{
		if ((*iter)->tag == tag)
		{
			break;
		}
	}

	if (iter == _callback_queue.end())
	{
		return false;
	}

	return true;
}

Scheduler::~Scheduler()
{
	auto iter = _callback_queue.begin();

	for (; iter != _callback_queue.end(); ++iter)
	{
		(*iter)->release();
	}

}