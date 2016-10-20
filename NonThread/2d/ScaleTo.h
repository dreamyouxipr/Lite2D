#ifndef __SCALETO__
#define __SCALETO__


#include "../Macros.h"
#include "../base/Ref.h"
#include "../base//Vec2.h"


#include "Action.h"

class Action;

/**
 * @brief scale a Node
 */
class DLL ScaleTo : public Action
{
public:
	/**
	 * @brief  create a object whilh autorelease()
	 */
	static ScaleTo*create(Vec2&scale, float _time);

	/**
	* @brief  create a object whilh autorelease()
	*/
	static ScaleTo*create(float scale, float _time);

protected:

	virtual void update() override;

	ScaleTo(const Vec2 &scale, float _time);

	ScaleTo(){};

	 
protected:
	Vec2 _addition;
 

};






#endif


