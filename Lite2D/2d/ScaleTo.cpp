#include"ScaleTo.h"
#include "../base/Node.h"


ScaleTo::ScaleTo(const Vec2 &scale, float _time)
{
	_total_time = _time;
	_addition = scale;


}



ScaleTo* ScaleTo::create(Vec2&pos, float _time)
{
	ScaleTo*ac = new ScaleTo(pos, _time);

	ac->autorelease();

	return ac;


}


ScaleTo* ScaleTo::create(float scale, float _time)
{
	ScaleTo*ac = new ScaleTo(Vec2(scale, scale), _time);

	ac->autorelease();
	return ac;
}


void ScaleTo::update()
{
	if (!_isLoop)return;

	if (_is_init == false)
	{
		_is_init = true;
		_addition.sub(target->getScale());

		_addition.div(60.0f*_total_time);

	}

	current += _speed;

	if (current >= _total_time)
	{// action done
		current = 0.0f;
		_isdone = true;
	}
	else
	{// 

		Vec2 _scale = target->getScale();
		_scale.add(_addition);
		target->setScale(_scale);
	}

}
