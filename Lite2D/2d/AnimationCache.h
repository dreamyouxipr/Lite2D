#ifndef __ANIMATIONCACHE__
#define __ANIMATIONCACHE__




#include "Animation.h"
#include<unordered_map>



/**
 * @brief the animation cache
 *
 */
class DLL AnimationCache :public Ref
{

public:
	/**
	 * @return the instance
	 */
	static AnimationCache *getInstance();


	/**
	 * @brief add a animation to the cache by name
	 */
	void addAnimation(const std::string &name, Animation*animation);

	/**
	 * @return a animation by name
	 * @note if not find will return nullptr
	 */
	Animation*getAnimation(const std::string&name);


	/**
	 * @brief remove a animation by name
	 */
	void removeAnimation(const std::string &name);


	/**
	 * @brief remove all animation
	 */
	void removeAllAnimations();


private:

	std::unordered_map<std::string, Animation*> _map;

	AnimationCache();
};









#endif


