#include"AutoReleeasePool.h"


AutoReleasePool::AutoReleasePool()
{
	ref_queue.reserve(100);
}


AutoReleasePool::~AutoReleasePool()
{
	this->clear();
}



void AutoReleasePool::addObjct(Ref*ref)
{

	ref_queue.push_back(ref);


}


void AutoReleasePool::removeObject(Ref*ref)
{

	auto iter = std::find(ref_queue.begin(), ref_queue.end(), ref);

	if (iter == ref_queue.end())
	{
		return;
	}

	ref_queue.erase(iter);

}


void AutoReleasePool::clear()
{

	//log("[call]:%s", __FUNCTION__);


	//log("%d", ref_queue.size());

//	for (const auto & ref : ref_queue)
	{
	//	ref->release();
	}


	for (int i = 0;i<ref_queue.size(); ++i)
	{
		ref_queue[i]->release();
	}
	ref_queue.clear();

}



int AutoReleasePool::getSize()const
{
	return ref_queue.size();
}


AutoReleasePool* AutoReleasePool::getInstance()
{
	static AutoReleasePool* ins = nullptr;


	if (ins == nullptr)
	{
		ins = new AutoReleasePool;
	}
	return ins;
}


