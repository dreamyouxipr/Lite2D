#ifndef __REF__
#define __REF__

#include "../Macros.h"






/**
 * @brief print the message in visual studio output windows
 */
void DLL log(const char *str, ...);

/**
* @brief print the message in std::cout
*/
void DLL log1(const char *str, ...);

class AutoReleasePool;


/**
 *this class is all object's super class
 */
class  DLL Ref
{
public:

	/**
	 * @brief this can been call each frame
	 */
	virtual void update(){};

	void setDirty(bool b= true)
	{
		_isDirty = b;
	}
	bool isDirty()const
	{
		return _isDirty;
	}
	/**
	 * @brief add ref to autorelase pool
	 * autorelease pool will clear all ref  each frame after render
	 * @see AutoReleasePool
	 */
	void autorelease();


	/**
	 * @brief retain the Ref's
	 * this will increase reference count by 1
	 */
	void retain();


	/**
	 * @brief  release this ref
	 * this will decrease refence count by 1
	 * if reference count is 0 then will delete
	 */
	void release();

	/**
	 * @return the reference count
	 *
	 */
	int getReferenceCount() const;


	Ref();

	virtual ~Ref();


	/**
	 * @brief print the memeory trackback
	 */
	static void printTrack();

	static int s_objectcount;



private:
	int referenceCount;
	bool _isDirty = false;


};




/**
 * @brief  for deep copy object  protocol
 */
class DLL Copy
{
public:
	virtual Ref*copy()const = 0;
	virtual ~Copy(){};

};




class TestRef :public Ref
{
public:

	TestRef()
	{
		this->autorelease();
	}
};




class DLL Color4B
{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	Color4B() :r(0xff), g(0xff), b(0xff), a(0xff){}
	Color4B(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
};


class DLL Color3B
{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	Color3B() :r(0xff), g(0xff), b(0xff){}
	Color3B(unsigned char r, unsigned char g, unsigned char b);
};











#endif


