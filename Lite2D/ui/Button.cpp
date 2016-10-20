#include"Button.h"
#include "../2d/Sprite.h"
#include "../base/EventDispatcher.h"



Button* Button::create(const std::string& file_normal, const std::string &file_clicked, std::function<void(Node*)> _callback)
{
	Button*ins = new Button;
	ins->initWithFile(file_normal, file_clicked);
	ins->_callback = _callback;
	ins->autorelease();
	//ins->release();

	return ins;

}

Button::~Button()
{
	_eventdispatcher->removeEventListener(_eventlistener);

	this->removeAllChildren();

}
 
void  Button::initWithFile(const std::string& file_normal, const std::string &file_clicked)
{

	_sp_normal = Sprite::create(file_normal);
	_sp_clicked = Sprite::create(file_clicked);

	this->addChild(_sp_clicked);
	this->addChild(_sp_normal);



	_sp_clicked->setVisible(false);

	_eventlistener = EventTouchListener::create(this);


	_eventdispatcher->addEventListener(EventType::TOUCH, _eventlistener);

	_rect = _sp_normal->getSize();

	_eventlistener->_began = [=](Ref*target, Event*event)
	{
		if (_visible == false)return false;

		if (event->isDirty() == false)
		{

			if (false == Math::isInUI(this->getGlobalPosition(),
				_sp_normal->getSize()*_sp_normal->getGlobalScale(), _sp_normal->getAnchorPoint(), event->getTouchGlobalPosition()))
			{
				return false;
			}


			_sp_normal->setVisible(false);
			_sp_clicked->setVisible(true);

			return true;
		}
		return false;
	};




	_eventlistener->_moved = [=](Ref*target, Event*event)
	{
		if (event->isDirty() == false)
		{

			if (false == Math::isInUI(this->getGlobalPosition(), _sp_normal->getSize()*_sp_normal->getGlobalScale()
				, _sp_normal->getAnchorPoint(), event->getTouchGlobalPosition()))
			{

				_sp_normal->setVisible(true);
				_sp_clicked->setVisible(false);

			}
			else
			{
				_sp_normal->setVisible(false);
				_sp_clicked->setVisible(true);
			}
		}

	};

	_eventlistener->_ended = [=](Ref*target, Event*event)
	{
		if (event->isDirty() == false)
		{
			_sp_normal->setVisible(true);
			_sp_clicked->setVisible(false);

			if (true == Math::isInUI(this->getGlobalPosition(), _sp_normal->getSize()*_sp_normal->getGlobalScale()
				, _sp_normal->getAnchorPoint(), event->getTouchGlobalPosition()))
			{
				_callback(this);
			}
		}

	};


}




