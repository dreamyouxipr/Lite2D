#include"CallFunc.h"
#include "../base/Node.h"


void CallFunc::update()
{
	if (!_isLoop)return;

	current += _speed;

	if (current >= _total_time)
	{
		_isdone = true;
		_func();

	}
 
}


CallFunc* CallFunc::create(const std::function<void(void)> &_func, float _time)
{
	CallFunc* ac = new CallFunc(_func,_time);
	ac->autorelease();
	return ac;

}


CallFunc::CallFunc(const std::function<void(void)>& _func, float _time)
{
	this->_total_time = _time;
	this->_func = _func;
}

