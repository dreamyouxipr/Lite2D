#ifndef __CALLFUNC__
#define __CALLFUNC__


#include "../Macros.h"
#include "Action.h"
#include <functional>


/**
 * @brief this action will call a func after given time
 */
class  DLL CallFunc :public Action
{

public:

	/**
	* @brief create a action
	* @note this will call autorelease()
	*/
	static CallFunc*create(const std::function<void(void)>& _func, float _time);

protected:

	/**
	 * @brief update action
	 */
	virtual void update() override;

	CallFunc(const std::function<void(void)>& _func, float _time);

	//CallFunc(){};

	std::function<void(void)> _func;


};





#endif


