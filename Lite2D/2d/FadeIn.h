#ifndef __FADEIN__
#define __FADEIN__

#include "../Macros.h"
#include "Action.h"


/**
 * @brief this action will set the Node's opacity 0.0f to 1.0f in given time
 */
class  DLL FadeIn :public Action
{

public:

	/**
	* @brief create a action
	* @note this will call autorelease()   
	*/
	static FadeIn*create(float _time);

protected:

	/**
	 * @brief update action
	 */
	virtual void update() override;

	FadeIn(float _time);

	FadeIn(){};

};






#endif


