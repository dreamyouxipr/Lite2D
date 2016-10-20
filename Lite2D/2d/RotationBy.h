#ifndef __ROTATIONBY__
#define __ROTATIONBY__


#include "RotationTo.h"


/**
* @brief rottion a Node
*/
class DLL RotationBy : public RotationTo
{
public:
 
	/**
	* @brief  create a object whilh autorelease()
	*/
	static RotationBy*create(float rotation, float _time);

protected:

	RotationBy(float rotation, float _time);

 

};






#endif


