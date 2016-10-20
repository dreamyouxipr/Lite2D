#ifndef __MACROS__
#define __MACROS__



//#define LITE2D


#ifdef LITE2D

#define DLL    _declspec(dllexport) 
#else 
#define DLL   _declspec(dllimport)
#endif

#include "assert.h"

#define ASSERT(cond,msg)  assert(cond)
//static assert
#define ASSERT_S(cond,msg) static_assert(cond,msg)



// safely delete
#define DELETE_S(p) do { if ((p)) delete (p); (p) = nullptr; } while(false);
#define DELETE_ARRAY_S(pArray) do { if ((pArray)) delete [] (pArray); (pArray) = nullptr; } while(false);



#pragma warning(disable:4251)
#pragma warning(disable:4996)
#pragma warning(disable:4005)
#pragma warning(disable:4099)
#pragma warning(disable:4018)


#include <iostream>


#endif


