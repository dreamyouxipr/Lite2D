#include"ActionMgr.h"
#include "Action.h"


void ActionMgr::update()
{
 
	// remove 
	for (auto iter = _action_queue.begin(); iter != _action_queue.end();)
	{
		if ((*iter)->isDone())
		{
			Action*ac = *iter;
			iter=_action_queue.erase(iter);

			ac->release();	
		}
		else
		{
			++iter;
		}

	}

	//for (const auto& action : _action_queue)
	{
		//action->update();

	}
	for (int i = 0; i < _action_queue.size(); ++i)
	{
		//log("size is %d",_action_queue.size());

		_action_queue[i]->update();
	}

}




void ActionMgr::addAction(Action*action)
{
	_action_queue.push_back(action);
}


ActionMgr::~ActionMgr()
{
	this->stopAllActions();
 

}

void ActionMgr::stopAllActions()
{
	for (const auto& action : _action_queue)
	{
		action->release();
	}

	_action_queue.clear();
}





