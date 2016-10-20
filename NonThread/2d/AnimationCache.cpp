#include"AnimationCache.h"


AnimationCache*AnimationCache::getInstance()
{
	static AnimationCache*ins = nullptr;

	if (ins == nullptr)
	{
		ins = new AnimationCache;
	}
	return ins;

}

AnimationCache::AnimationCache()
{


}



void AnimationCache::addAnimation(const std::string &name, Animation*animation)
{
	_map.insert(std::pair<std::string, Animation*>(name, animation));
	animation->retain();
}



void AnimationCache::removeAllAnimations()
{
	for (const auto&ani : _map)
	{
		ani.second->release();

	}

	_map.clear();
}


void AnimationCache::removeAnimation(const std::string &name)
{
	auto iter = _map.find(name);
	if (iter == _map.end())
	{
		return;
	}
	(*iter).second->release();
	_map.erase(iter);

}



Animation*AnimationCache::getAnimation(const std::string&name)
{

	auto iter = _map.find(name);
	if (iter == _map.end())
	{
		return nullptr;
	}
	return (*iter).second;
}


