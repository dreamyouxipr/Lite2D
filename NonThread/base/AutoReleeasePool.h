#ifndef __AUTORELEASEPOOL__
#define __AUTORELEASEPOOL__

#include "../Macros.h"


#include "Ref.h"
#include <vector>


/**
 * @brief autoreleasepool for Ref class function autorelease()
 * clear will be called each frame
 */


class DLL AutoReleasePool
{
public:
	/**
	 * @brief add ref to the pool
	 */
	void addObjct(Ref*);


	/**
	 * @brief remove  ref  from pool
	 */
	void removeObject(Ref*);


	/**
	 * @brief release all refs in pool
	 */
	void clear();


	/**
	 * @return the number of autorelease object
	 */
	int getSize()const;

	/**
	 * @brief return the instance
	 */
	static	AutoReleasePool*getInstance();


	virtual ~AutoReleasePool();
private:
	AutoReleasePool();
	std::vector<Ref*> ref_queue;


};










#endif


