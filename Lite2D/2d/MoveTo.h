#ifndef __MOVETO__
#define __MOVETO__


#include "../Macros.h"
#include "../base/Ref.h"
#include "../base//Vec2.h"


#include "Action.h"

class Action;

/**
 * @brief move to action this will move the target to the point
 */
class DLL MoveTo : public Action
{
public:

	/**
	* @brief  create a object with autorelease()
	*/
	static MoveTo*create(Vec2&pos, float _time);

	virtual void update() override;

	MoveTo(const Vec2 &pos, float _time);
 
	MoveTo(){};

protected:
	Vec2 _addition;


};






#endif


