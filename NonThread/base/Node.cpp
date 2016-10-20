#include"Node.h"
#include "../2d/Action.h"
#include "../2d/ActionMgr.h"


Node * Node::create()
{
	Node*obj = new Node;

	if (obj)
	{
		obj->autorelease();
		return obj;
	}
	return nullptr;

}


Node::Node() :
_localZ(0),
_tag(0),
_name("unnamed"),
_visible(true),
_opactiy(1.0f),
_parent(nullptr),
_rotation(0.0f)
{ 
	_scheduler = Director::getInstance()->getScheduler();
	_actionMgr = new ActionMgr;
	_eventdispatcher = Director::getInstance()->getEventDispatcher();


	//set default anchor point
	_anchor.x = 0.5f;
	_anchor.y = 0.5f;
	// set scale
	_scale.x = 1.0f;
	_scale.y = 1.0f;
	// set position
	_position.x = 0;
	_position.y = 0;
}


Node::~Node()
{
	_actionMgr->release();
	this->removeAllChildren();

}

void Node::draw()
{
	_actionMgr->update();


	if (!_visible)
	{
		return;
	}
	//draw all child

	for (int i = 0; i < _children.size(); ++i)
	{
		_children[i]->draw();
	}

}

void Node::addScheduleUpdate()
{
	_scheduler->addSchedulerPerFrame(this);


}
void Node::removeScheduleUpdate()
{
	_scheduler->removeSchedulerPerFrame(this);


}
void Node::setPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;

}

void Node::setPosition(const Vec2 &pos)
{
	_position = pos;
}

void Node::setPositionX(float x)
{
	_position.x = x;

}
void Node::setPositionY(float y)
{
	_position.y = y;
}


const Vec2& Node::getPosition()const
{
	return _position;
}

float Node::getPositionX()const
{
	return _position.x;
}


float Node::getPositionY()const
{
	return _position.y;
}


void Node::setScale(float s)
{
	_scale.x = s;
	_scale.y = s;
}

void Node::setScale(const Vec2 &scale)
{
	_scale = scale;
}

void Node::setScale(float x, float y)
{
	_scale.x = x;
	_scale.y = y;

}

void Node::setScaleX(float x)
{
	_scale.x = x;
}

void Node::setScaleY(float y)
{
	_scale.y = y;
}

const Vec2& Node::getScale() const
{
	return _scale;
}


float Node::getScaleX()const
{
	return _scale.x;
}

float Node::getScaleY()const
{
	return _scale.y;
}

void Node::setOpacity(float _opacity)
{
	this->_opactiy = _opacity;
}

float Node::getOpacity()const
{
	return _opactiy;

}

void Node::setRotation(float rotation)
{
	this->_rotation = rotation;
}

float Node::getRotation()const
{
	return	_rotation;
}


void Node::addChild(Node* child)
{
	this->addChild(child, 0);
}

void Node::addChild(Node*child, int z)
{
	_children.push_back(child);
	child->_parent = this;
	child->retain();
}


void Node::removeChild(Node*child, bool clean)
{
	auto iter = std::find(_children.begin(), _children.end(), child);

	if (iter == _children.end())
	{
		return;
	}

	_children.erase(iter);

	if (clean)
	{
		child->release();
	}
}


void Node::removeAllChildren(bool clean)
{
	if (clean)
	{
		for (const auto & child : _children)
		{
			child->release();
		}
	}

	_children.clear();

	//log("Node::removeAllChildren(bool clean)");


}



int Node::getChildCount()const
{
	return _children.size();
}



void Node::setTag(int tag)
{
	_tag = tag;
}

int Node::getTag()const
{
	return _tag;
}


void Node::setName(const std::string&name)
{
	_name = name;
}

const char*Node::getName()const
{
	return _name.c_str();
}


void Node::setVisible(bool isVisible)
{
	_visible = isVisible;
}

bool Node::getVisible()const
{
	return _visible;
}

bool Node::isVisible()const
{
	return _visible;
}


void Node::setParent(Node*parent)
{
	parent->addChild(this);
}

Node*Node::getParent()const
{
	return _parent;
}



void Node::update()
{


}


void Node::setAnchorPoint(const Vec2&anchor)
{
	_anchor = anchor;
}

const Vec2& Node::getAnchorPoint()const
{
	return _anchor;

}

void Node::runAction(Action*action)
{
	if (action)
	{
		action->setTarget(this);
		action->retain();
		_actionMgr->addAction(action);
	}
}

Vec2 Node::getGlobalPosition()
{
	if (_parent)
	{
		float parentGlobalRotation = _parent->getGlobalRotation();
		float sin = Math::sin(parentGlobalRotation);
		float cos = Math::cos(parentGlobalRotation);
		return _parent->getGlobalPosition() + Vec2{ _position.x*cos - _position.y*sin, _position.x*sin + _position.y*cos };
	}
	return _position;
}

Vec2 Node::getGlobalPoint(const Vec2& localPoint)
{
	auto sin = Math::sin(_rotation);
	auto cos = Math::cos(_rotation);
	return getGlobalPosition() + Vec2{ localPoint.x*cos - localPoint.y*sin, localPoint.x*sin + localPoint.y*cos };
}

Vec2 Node::getGlobalScale()
{
	if (_parent)
	{
		auto parentGlobalScale = _parent->getGlobalScale();
		return{ parentGlobalScale.x*_scale.x, parentGlobalScale.y*_scale.y };
	}
	return _scale;
}

float Node::getGlobalRotation()
{
	return _parent ? _parent->getGlobalRotation() + _rotation : _rotation;
}