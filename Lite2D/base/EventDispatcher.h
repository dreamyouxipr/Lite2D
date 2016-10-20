#ifndef __EVENTDISPATCHER__
#define __EVENTDISPATCHER__


#include "Ref.h"
#include "Vec2.h"

#include "../glfw3.h"
#include <functional>
#include <vector>
class Director;
class Node;


enum class EventType
{
	TOUCH,
	KEYBOARD,
	UNKNOW
};


enum class MouseEventType
{
	BEGAN,
	ENDED,
	MOVED
};



class DLL Event : protected Ref
{

public:

	Node*getTarget()const;

	virtual    Vec2  getTouchGlobalPosition()const = 0;
	void setDirty(bool b = true){ _is_dirty = b; };
	bool isDirty(){ return _is_dirty; }
protected:

	Node*_target;
	bool _is_dirty;

protected:
	Event():_is_dirty(false){};

};


/**
 * @brief you can set 3 public  std::function member for your own callback
 */
class DLL EventTouchListener :public Event
{
public:

	friend class EventDispatcher;

	/**
	 * @brief the call back when beging
	 */
	std::function<bool(Node*target, Event*event)> _began;

	/**
	* @brief the call back when ending
	*/
	std::function<void(Node*target, Event*event)> _ended;

	/**
	* @brief the call back when moving
	*/
	std::function<void(Node*target, Event*event)> _moved;


	/**
	 * @return the event Points of whole scene
	 * @note the point's zero Point at left-down of the screen
	 */
	virtual  Vec2 getTouchGlobalPosition() const override;


	/**
	 * @brief create a listener which is autorelease()
	 */
	static EventTouchListener*create(Node*target);

private:
	EventTouchListener();


	/**
	 * @brief set this listener's event Position
	 */
	void setPos(float x, float y);

	/**
	 * @brief set event status moved ended or began
	 */
	void setStatus(MouseEventType status);


private:

	bool is_began;//is _began function return true?

	Vec2 _pos;// event position
	MouseEventType _status;//event status
};


class DLL  EventKeyBord :public Event
{




};



/**
 * @brief the eventdispatcher only director has a object
 * a game has only one eventdispatcher
 */
class DLL  EventDispatcher : public Ref
{
public:


	/**
	 * @brief add a event listener to the queue
	 */
	void addEventListener(EventType _type, EventTouchListener* _event);

	/**
	 * @brief remove a event listener from queue
	 */
	void removeEventListener(EventTouchListener*event);

	virtual ~EventDispatcher();

protected:
	static EventDispatcher*create()
	{
		return new EventDispatcher;
	}
	/**
	 * @brief updata events
	 */
	void pollEvents();
	friend class Director;

private:

	// dispatch all events from  queue
	void dispatcherEvent();

	double _xx_pos_globle;
	double _yy_pos_globle;
	double   point_begin_x, point_begin_y;


	// mouse event type
	MouseEventType _mouse_eventtype;

	//current button statue
	int _current_button_status = GLFW_RELEASE;

	//events queue
	std::vector<EventTouchListener*> _touch_queue;

};







#endif

