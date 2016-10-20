#include"FadeIn.h"
#include "../base/Node.h"



void FadeIn::update()
{
	if (!_isLoop)return;

	current += _speed;

	if (current >= _total_time)
	{
		_isdone = true;
	}
	else
	{
		target->setOpacity(current / _total_time);
	}
}


FadeIn* FadeIn::create(float _time)
{
	FadeIn* ac = new FadeIn(_time);
	ac->autorelease();
	return ac;

}


FadeIn::FadeIn(float _time)
{
	this->_total_time = _time;

}


