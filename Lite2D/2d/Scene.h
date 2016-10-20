#ifndef __SCENE__
#define __SCENE__

 
 #include "../base/Node.h"
 


/**
 * @brief the game scene ,you can add sprite or others in  scene to show you own game
 */
class DLL Scene :public Node
{
public:
   /**
    * @brief you must init your scene in this function
    */
	virtual bool init() { return true; };

	Scene();
	virtual ~Scene();
	virtual void update()override{};
private:

   /**
    * @brief draw current scene
	* @note   only director can call this func
    */
	void drawScene();
	friend class Director;
};









#endif


