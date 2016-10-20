#ifndef __RENDERCMD__
#define __RENDERCMD__


#include "../glut.h"
#include "../glfw3.h"
#include "../math/Math.h"
#include <vector>
#include "../base/Ref.h"
#include "../base/Director.h"
#include "Texture2D.h"


// enable multi thread 



class RenderCmd :public Ref
{
public:
	virtual void exec(Texture2D*) = 0;
	float   *_coord2f = 0;
	Vec2 _vertex[4];
	float _opacity = 0.0f;
	Texture2D*tex=nullptr;
	Texture2D*tex_render = nullptr;
};


class RenderCmd_Quad :public RenderCmd
{
public:
	virtual void exec(Texture2D*)override;
};



#endif


