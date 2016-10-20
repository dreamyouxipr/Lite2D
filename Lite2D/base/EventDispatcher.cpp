#include"EventDispatcher.h"
#include "Director.h"
#include "Node.h"


Node* Event::getTarget()const
{
	return _target;
}

EventTouchListener::EventTouchListener() :
_began(nullptr),
_ended(nullptr),
_moved(nullptr),
is_began(false)
{


}


EventTouchListener*  EventTouchListener::create(Node*target)
{
	EventTouchListener*ins = new EventTouchListener;

	if (!ins)return nullptr;

	ins->autorelease();

	ins->_target = target;

	return ins;

}

Vec2   EventTouchListener::getTouchGlobalPosition()  const
{
	return Vec2
		//(Director::getInstance()->getWindowSize().x -
		
		(_pos.x,
		Director::getInstance()->getWindowSize().y - _pos.y);
}

void  EventTouchListener::setPos(float x, float y)
{
	_pos.x = x;
	_pos.y = y;

}

void  EventTouchListener::setStatus(MouseEventType status)
{
	_status = status;
}





void EventDispatcher::addEventListener(EventType _type, EventTouchListener*_event)
{
	_event->retain();

	switch (_type)
	{
	case EventType::TOUCH:
	{
							 _touch_queue.push_back(_event);
	}
		break;
	case EventType::KEYBOARD:
		break;
	case EventType::UNKNOW:
		break;
	default:
		break;
	}


}


void EventDispatcher::removeEventListener(EventTouchListener*event)
{
	auto iter = std::find(_touch_queue.begin(), _touch_queue.end(), event);
	if (iter == _touch_queue.end())
	{
		return;
	}

	auto ev = *iter;
	ev->autorelease();
	ev->setDirty();

	_touch_queue.erase(iter);
}



void EventDispatcher::pollEvents()
{
	// update mouse position
	glfwGetCursorPos(glfwGetCurrentContext(), &_xx_pos_globle, &_yy_pos_globle);

	int current = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT);

	bool _change = false;

	if (_current_button_status == GLFW_RELEASE)
	{
		if (current == GLFW_PRESS)
		{
			//	std::cout << " press" << std::endl;
			point_begin_x = _xx_pos_globle;
			point_begin_y = _yy_pos_globle;
			_current_button_status = GLFW_PRESS;
			_mouse_eventtype = MouseEventType::BEGAN;
			_change = true;

		}
	}


	if (_current_button_status == GLFW_PRESS)
	{
		if (current == GLFW_RELEASE)
		{
			//std::cout << " release" << std::endl;
			_current_button_status = GLFW_RELEASE;
			_mouse_eventtype = MouseEventType::ENDED;
			_change = true;

		}
		else
		{
			if (_xx_pos_globle != point_begin_x && _yy_pos_globle != point_begin_y)
			{
				//std::cout << "moved" <<std:: endl;
				point_begin_x = _xx_pos_globle;
				point_begin_y = _yy_pos_globle;
				_mouse_eventtype = MouseEventType::MOVED;
				_change = true;
			}

		}
	}

	if (_change)
	{
		this->dispatcherEvent();
	}


}

void EventDispatcher::dispatcherEvent()
{

	// touch event
	EventTouchListener*event;

	for (int i = 0;i< _touch_queue.size(); ++i)
	{
		event = _touch_queue[i];

		event->setPos(static_cast<float>(_xx_pos_globle), static_cast<float>(_yy_pos_globle));

		switch (_mouse_eventtype)
		{

		case MouseEventType::ENDED:
		{


									  if (event->_ended)
									  if (event->is_began == true)
									  {
										  event->is_began = false;
										  event->_ended(event->getTarget(), event);

									  }
		}
			break;
		case MouseEventType::MOVED:
		{
									  if (event->_moved)
									  if (event->is_began == true)
									  {
										  event->_moved(event->getTarget(), event);

									  }
		}
			break;

		case MouseEventType::BEGAN:
		{
									  if (event->_began)
										  event->is_began = event->_began(event->getTarget(), event);
		}
			break;


		default:
			break;
		}


	}


}


EventDispatcher::~EventDispatcher()
{
	// touch event
	for (const auto& event : _touch_queue)
	{
		event->release();
	}
	_touch_queue.clear();

}
