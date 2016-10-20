#ifndef __SCALEBY__
#define __SCALEBY__


#include "ScaleTo.h"


/**
* @brief scale a Node
*/
class DLL ScaleBy : public ScaleTo
{
public:
	/**
	* @brief  create a object whilh autorelease()
	*/
	static ScaleBy*create(Vec2&scale, float _time);

	/**
	* @brief  create a object whilh autorelease()
	*/
	static ScaleBy*create(float scale, float _time);

protected:

	ScaleBy(const Vec2 &scale, float _time);

 

};






#endif


