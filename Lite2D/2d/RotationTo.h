#ifndef __ROTATIONTO__
#define __ROTATIONTO__


#include "../Macros.h"
#include "../base/Ref.h"
#include "../base//Vec2.h"


#include "Action.h"

class Action;

/**
 * @brief rotation a Node
 */
class DLL RotationTo : public Action
{
public:
 
	/**
	* @brief  create a object whilh autorelease()
	*/
	static RotationTo*create(float rotation, float _time);

protected:

	virtual void update() override;

	RotationTo(float rotation, float _time);

	RotationTo(){};

	 
protected:
	float _addition;
 

};






#endif


