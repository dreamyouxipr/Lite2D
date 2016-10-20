#ifndef __ANIMATION__
#define __ANIMATION__


#include "Action.h"
#include <vector>
class Sprite;
class Texture2D;



/**
 * @brief create a frame animation
 * @warning this only runAction on a Sprite
 */
class DLL  Animation :public Action
{
public:
	static Animation*create();
	/**
	 * @brief add a frame file
	 */
	void addFrameFile(const std::string file);
	/**
	 * @brief set delay time per frame
	 */
	void setPerFrameDelay(float delay);
	/**
	 * @brief  set loop times
	 * @note default is 1
	 */
	void setLoops(int loop);


	~Animation();


	/**
	 * @brief  set is show origin texture  when over
	 */
	void setOriginTexture(bool b);

protected:

	virtual void setTarget(Node*target)override;

	void reset();


	virtual void update()override;
	Animation();
	Sprite*_target;//target to run this action must is a Sprite
	bool is_origin;//is show origin texture?
	void clear();// clear 
	std::vector<Texture2D*> _queue;
	int current_index; // current frame count

	int loops = 0; // loops
	int current_loop = 0;
	Texture2D*_tex_origin;//


};







#endif


