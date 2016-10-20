#ifndef __COLORNODE__
#define __COLORNODE__


#include "../base/Node.h"





class DLL ColorNode :public Node
{

public:


	/**
	* @brief set is flip x
	*/
	void setFlipX(bool _is);

	/**
	* @brief set is flip y
	*/
	void setFlipY(bool _is);

	/**
	* @return is flip x
	*/
	bool getFlipX()const;

	/**
	* @return is flip y
	*/
	bool getFlipY()const;

	virtual void update()override;

private:
	
	bool _is_flipx;
	bool _is_flipy;
	Vec2 _rect;

};











#endif


