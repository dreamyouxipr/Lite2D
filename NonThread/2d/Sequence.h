#ifndef __SEQUENCE__
#define __SEQUENCE__




#include "../Macros.h"
#include "../base/Ref.h"
#include "../base//Vec2.h"
#include <vector>

#include "Action.h"

/**
 * @brief create a sequence action
 */
class DLL Sequence :public Action
{

public:
	static Sequence*create(Action *_action1, ...);

	~Sequence();

	virtual void setTarget(Node*target)override;
protected:

	/**
	 * @brief add a action to sequence
	 * @note this will call retain()
	 */
	void addAction(Action*action);
	Sequence();
	virtual void update()override;
	void clear();
protected:
	int current;

	std::vector<Action*>_queue;

};







#endif


