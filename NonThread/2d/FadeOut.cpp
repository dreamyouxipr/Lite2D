#include"FadeOut.h"
#include "../base/Node.h"


void FadeOut::update()
{
	if (!_isLoop)return;

	current += _speed;

	if (current >= _total_time)
	{
		_isdone = true;
	}
	else
	{
		target->setOpacity(1.0f-current / _total_time);
	}
}


FadeOut* FadeOut::create(float _time)
{
	FadeOut* ac = new FadeOut(_time);
	ac->autorelease();
	return ac;

}


FadeOut::FadeOut(float _time)
{
	this->_total_time = _time;

}



