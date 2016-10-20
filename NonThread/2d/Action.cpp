#include"Action.h"
#include "../base/Node.h"

Action::Action() :
_speed(1.0f / 60.0f),
_total_time(0.0f),
current(0.0f),
_isdone(false),
target(nullptr),
_isLoop(true)
{


}

void Action::pause()
{
	_isLoop = false;
}


void Action::resume()
{
	_isLoop = true;
}


void Action::setTag(int tag)
{
}

int Action::getTag()
{
	return _tag;
}

void Action::setTarget(Node*target)
{
	this->target = target;

}


Node*Action::getTatget()const
{
	return target;
}


void Action::update()
{

}

bool Action::isDone()const
{
	return _isdone;
}


Action::~Action()
{
//	log("~Action");


}
// 
// void Action::setLoopTimes(int times)
// {
// 	if (times < 0)
// 	{
// 		times = 0x7fffffff;
// 	}
// 	repeat = times;
// }

