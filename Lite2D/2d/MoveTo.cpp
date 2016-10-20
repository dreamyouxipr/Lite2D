#include"MoveTo.h"
#include "../base/Node.h"


MoveTo::MoveTo(const Vec2 &pos, float _time)
{
	_addition = pos;

	_total_time = _time;
}


MoveTo* MoveTo::create(Vec2&pos, float _time)
{
	MoveTo*ac = new MoveTo(pos, _time);

	ac->autorelease();

	return ac;


}

void MoveTo::update()
{
	if (!_isLoop)return;
	if (_is_init == false)
	{
		_is_init = true;
		_addition.sub(target->getPosition());
		_addition.div(60.0f*_total_time);

	}

	current += _speed;

	if (current > _total_time)
	{// action done


		current = 0.0f;
		_isdone = true;

	}
	else
	{// 

		Vec2 pos = target->getPosition();

		pos.add(_addition);
		target->setPosition(pos);
	}

}



