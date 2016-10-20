#ifndef __ACTION__
#define __ACTION__


#include "../Macros.h"
#include "../base/Ref.h"

class Node;
class ActionMgr;
class Sequence;

/**
 * @brief  all action's super class
 * action will been attach to a Node's object  then action will be work
 * _target: is the target to run action
 * sub class override setTarget() to init sub class 's own
 * @see ScaleTo is a example
 * default loop time is 1
 *
 */
class DLL Action :public Ref, public Copy
{
public:
	/**
	 * @brief pause current action
	 */
	void pause();
	virtual Action* copy()const override{ return nullptr; };

	/**
	 * @brief resume current action
	 */
	void resume();

	void setTag(int tag);
	int getTag();
	Node*getTatget()const;

	/**
	* @brief set action target you can init you own action in this func
	*/
	virtual void setTarget(Node*target);
	~Action();
protected:
	friend class ActionMgr;
	friend class Sequence;
	virtual void update() override;
	bool isDone()const;
	Action();

protected:
	float _speed;//the action should been run speed (is time)
	float _total_time;//action last time
	bool _isdone;//if action is done
	float current;// current time 
	Node*target;// the target to run action 

	int _tag;
	bool _isLoop;// is loop ?
	bool _is_init = false;// is init right ?

};









#endif


