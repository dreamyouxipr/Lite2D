#include"RotationBy.h"
#include "../base/Node.h"

RotationBy::RotationBy(float rotation, float _time)
{
	_addition = rotation;
	_addition/=60.0f*_time;
	_is_init = true;
	_total_time = _time;
}


 

RotationBy* RotationBy::create(float rotation, float _time)
{
	RotationBy*ac = new RotationBy(rotation, _time);

	ac->autorelease();

	return ac;
}

 
