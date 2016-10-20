#ifndef __ACTIONMGR__
#define __ACTIONMGR__


#include "../Macros.h"
#include "../base/Ref.h"
#include "../base//Vec2.h"
#include <vector>

class Action;



class DLL ActionMgr :public Ref
{
public:


	void update() override;

   /**
    * @brief add a action to the Mgr
    */
	void addAction(Action*action);


	void stopAllActions();

	virtual ~ActionMgr();
private:

	std::vector<Action*> _action_queue;
};








#endif


