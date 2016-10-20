#ifndef __MOVEBY__
#define __MOVEBY__


#include "MoveTo.h"


/**
* @brief move by action this will move the target to the point
*/
class DLL MoveBy : public MoveTo
{
public:

	/**
	* @brief  create a object whilh autorelease()
	*/
	static MoveBy*create(Vec2&pos, float _time);

	MoveBy(const Vec2 &pos, float _time);

 

};






#endif


