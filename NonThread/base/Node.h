#ifndef __NODE__
#define __NODE__

#include "../Macros.h"


#include "Director.h"
#include "Vec2.h"

#include <vector>
#include "Ref.h"
#include "Scheduler.h"
#include "../math/Math.h"

class Action;
class ActionMgr;
class EventDispatcher;

/**
 * @brief Node is a drawable and visible object you can override draw() to
 * draw your own obj
 *
 */
class DLL Node :public Ref
{
public:


	/**
	 * @brief create a node with autorelease
	 */
	static Node*create();


	/**
	 * @brief if you want to show something please overwrite this function
	 */
	virtual void  draw();

	/**
	 * @brief set parent
	 */
	void setParent(Node*parent);

	/**
	 * @brief return parent
	 * @return Node*
	 */
	Node*getParent()const;

	/**
	 * @brief add child
	 */
	void addChild(Node* child);
	void addChild(Node* child, int z);

	/**
	 * @brief remove child
	 */
	void removeChild(Node*child, bool clean = true);

	/**
	 * @brief remove all children
	 */
	void removeAllChildren(bool clean = true);

	/**
	 * @return children count
	 */
	int getChildCount()const;

	virtual ~Node();

	/**
	 * @brief will be called each frame
	 */
	virtual void update();

public:
	//_position
	void setPosition(float x, float y);
	void setPosition(const Vec2 & pos);
	void setPositionX(float x);
	void setPositionY(float y);

	const Vec2 & getPosition()const;
	float getPositionX()const;
	float getPositionY()const;



	//_scale
	void setScale(float x, float y);
	void setScale(float s);
	void setScale(const Vec2& scale);
	void setScaleX(float x);
	void setScaleY(float y);

	const Vec2& getScale()const;
	float getScaleX()const;
	float getScaleY()const;

	int getTag()const;
	void setTag(int tag);

	void setName(const std::string&name);
	const char* getName()const;

	bool isVisible()const;
	void setVisible(bool isVisible);
	bool getVisible()const;

	/**
	 * @brief set the anchor point
	 */
	void setAnchorPoint(const Vec2&anchor);


	/**
	 * @return the anchor point
	 */
	const Vec2&getAnchorPoint()const;

	/**
	 * @brief set opacity in [0,1]
	 */
	void setOpacity(float _opacity);
	float getOpacity()const;

	/**
	 * @reture rotation
	 */
	float getRotation()const;
	void setRotation(float rotation);

	Vec2 getGlobalPosition();
	Vec2 getGlobalScale();
	Vec2 getGlobalPoint(const Vec2 &localPoint);
	float getGlobalRotation();
protected:
	bool _visible;

	Vec2 _position;
	Vec2 _scale;
	std::vector<Node*> _children;
	int _localZ;
	int _tag;
	std::string _name;
	Node*_parent;

	Scheduler *_scheduler;
	
	Vec2 _anchor;
	float _opactiy;
	float _rotation;

public:
	Node();
	void addScheduleUpdate();
	void removeScheduleUpdate();
	//action 
	ActionMgr*_actionMgr;
	EventDispatcher*_eventdispatcher;

	void runAction(Action*action);
};











#endif


