#ifndef __FADEOUT__
#define __FADEOUT__


#include "../Macros.h"
#include "Action.h"


/**
 * @brief this action will set the Node's opacity 1.0f to 0.0f in given time
 */
class  DLL FadeOut :public Action
{

public:

	/**
	* @brief create a action
	* @note this will call autorelease()
	* @note when done will not release the Node while opacity is 0.0f
	*/
	static FadeOut*create(float _time);

protected:

	/**
	 * @brief update action
	 */
	virtual void update() override;

	FadeOut(float _time);

	FadeOut(){};

};







#endif


