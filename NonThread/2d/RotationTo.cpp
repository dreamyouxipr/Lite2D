#include"RotationTo.h"
#include "../base/Node.h"


RotationTo::RotationTo(float rotation, float _time)
{
	_total_time = _time;
	_addition = rotation;


}





RotationTo* RotationTo::create(float rotation, float _time)
{
	RotationTo*ac = new RotationTo(rotation, _time);

	ac->autorelease();
	return ac;
}


void RotationTo::update()
{
	if (!_isLoop)return;

	if (_is_init == false)
	{
		_is_init = true;
		_addition -= target->getRotation();

		_addition /= 60.0f*_total_time;

	}




	current += _speed;

	if (current >= _total_time)
	{// action done


		current = 0.0f;
		_isdone = true;

	}
	else
	{// 

		float rotation = target->getRotation();
		rotation += _addition;
		target->setRotation(rotation);
	}

}
