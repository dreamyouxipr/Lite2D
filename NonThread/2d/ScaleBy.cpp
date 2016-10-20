#include"ScaleBy.h"
#include "../base/Node.h"

ScaleBy::ScaleBy(const Vec2 &scale, float _time)
{
	_addition = scale;
	_addition.div(60.0f*_time);
	_is_init = true;
	_total_time = _time;

}


 

ScaleBy* ScaleBy::create(Vec2&pos, float _time)
{
	ScaleBy*ac = new ScaleBy(pos, _time);

	ac->autorelease();

	return ac;


}


ScaleBy* ScaleBy::create(float scale, float _time)
{ 
	return ScaleBy::create(Vec2(scale,scale),_time);
}


 