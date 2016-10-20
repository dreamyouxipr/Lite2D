#include"Sequence.h"
#include <stdarg.h>

Sequence::Sequence() :current(0)
{
 
}

Sequence*  Sequence::create(Action *_action1, ...)
{
	Sequence *ins = new Sequence;
	ins->autorelease();

	ins->addAction(_action1);
 
	va_list li;

	Action*action=nullptr;

	va_start(li, _action1);
 
	while (action = va_arg(li, Action*))
	{
		ins->addAction(action);

	}
	va_end(li);

	return ins;

}

void Sequence::addAction(Action*action)
{
	action->retain();
	_queue.push_back(action);

}




void Sequence::update()
{
 
	if (_queue[current]->isDone())
	{
		++current;
	}

	if (current < _queue.size())
	{
		_queue[current]->update();

	}
	else
	{

		this->clear();
		this->_isdone = true;
		return;
	}

}

void Sequence::setTarget(Node*target)
{
	this->target = target;

	for (const auto & ac : _queue)
	{
		ac->setTarget(target);

	}

}

void Sequence::clear()
{
	for (const auto & ac : _queue)
	{
		ac->release();

	}
	_queue.clear();
}

Sequence::~Sequence()
{
	this->clear();
	current = 0;
}