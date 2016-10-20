#include"MoveBy.h"
#include "../base/Node.h"


MoveBy::MoveBy(const Vec2 &pos, float _time)
{
	_addition = pos;
	_addition.div(_time * 60.0f);
	_is_init = true;
	_total_time = _time;
}

 


MoveBy* MoveBy::create(Vec2&pos, float _time)
{
	MoveBy*ac = new MoveBy(pos, _time);

	ac->autorelease();

	return ac;


}