#include"Ref.h"
#include "AutoReleeasePool.h"


#include <list>
#include <typeinfo>

#include "windows.h"
#include "stdio.h"


static char log_buffer[5000000];// 5mb for buffer size

void log(const char *str, ...)
{

	va_list l;
	va_start(l, str);

	vsprintf(log_buffer, str, l);

	va_end(l);
	strcat(log_buffer, "\n\0");

	//	OutputDebugString("Lite2D:");
	OutputDebugString(log_buffer);

	//	printf(buffer);


}

void log1(const char *str, ...)
{

	va_list l;
	va_start(l, str);

	vsprintf(log_buffer, str, l);

	va_end(l);
	strcat(log_buffer, "\n\0");

 	printf(log_buffer);


}


std::list<Ref*> refAllocList;

int Ref::s_objectcount = 0;


static void trackRef(Ref*ref)
{
	refAllocList.push_back(ref);
}

static void untrackRef(Ref*ref)
{
	auto iter = std::find(refAllocList.begin(), refAllocList.end(), ref);

	if (iter == refAllocList.end())return;

	refAllocList.erase(iter);
}



void Ref::printTrack()
{
	if (refAllocList.size() == 0)
	{
		log("[Memeory]: all objects are delete");
		return;
	}


	for (const auto &ref : refAllocList)
	{
		log("[Memeory]:Ref's count %d\t    %s \t\tobject still in memeory address 0x%x",
			ref->getReferenceCount(), typeid(*ref).name(), ref);

	}

	log("[Memeory Track]: %d objects are alive\n", refAllocList.size());

}




Ref::Ref()
:referenceCount(1)
{
	trackRef(this);

}


Ref::~Ref()
{
	untrackRef(this);

}


int Ref::getReferenceCount() const
{
	return referenceCount;
}



void Ref::release()
{
	--referenceCount;

	if (referenceCount == 0)
	{//release the object

		delete this;
	}
}


void Ref::retain()
{
	++referenceCount;
}



void Ref::autorelease()
{

	AutoReleasePool::getInstance()->addObjct(this);

}


Color4B::Color4B(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}




Color3B::Color3B(unsigned char r, unsigned char g, unsigned char b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

