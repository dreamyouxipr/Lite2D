#include"ColorNode.h"
#include "../glfw3.h"


void  ColorNode::setFlipX(bool _is)
{
	this->_is_flipx = _is;
}


void  ColorNode::setFlipY(bool _is)
{
	this->_is_flipy = _is;
}


bool  ColorNode::getFlipX()const
{
	return this->_is_flipx;
}


bool  ColorNode::getFlipY()const
{
	return this->_is_flipy;
}


void ColorNode::update()
{

	log1("444");


	if (!_visible)
	{
		return;
	}
	_rect.x = 200;
	_rect.y = 200;


	glLoadIdentity();// vetex can work once





	// able alpha blend for the texture who has alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);




	//able opacity
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glColor4f(0, 1.0f, 1.0f, _opactiy);



	//start to render





	glBegin(GL_QUADS);

	//fix bug of transform of difference window size

	Vec2 windowSize = Director::getInstance()->getWindowSize();

	auto originalSize = _rect;




	Vec2 localAnchorPoint(originalSize.x*_anchor.x, originalSize.y*_anchor.y);
	Vec2 vertexes[4]{ -localAnchorPoint, { originalSize.x - localAnchorPoint.x, -localAnchorPoint.y }, originalSize - localAnchorPoint, { -localAnchorPoint.x, originalSize.y - localAnchorPoint.y } };
	auto globalPosition = getGlobalPosition();

	auto globalScale = getGlobalScale();
	auto globalRotation = getGlobalRotation();
	static Vec2 _glScale{ 2 / windowSize.x, 2 / windowSize.y };
	// init for rotating
	auto sin = Math::sin(globalRotation);
	auto cos = Math::cos(globalRotation);
	for (auto &vertex : vertexes)
	{
		// local transform
		// rotate
		{
			auto tempX = vertex.x;
			vertex.x = tempX*cos - vertex.y*sin;
			vertex.y = tempX*sin + vertex.y*cos;
		}
		vertex.x *= globalScale.x; vertex.y *= globalScale.y; // scale

		// global transform
		vertex.x += globalPosition.x;
		vertex.y += globalPosition.y;

		// gl transform
		vertex.x *= _glScale.x;
		vertex.y *= _glScale.y;
		vertex.x -= 1;
		vertex.y -= 1;


	}

	// draw

	float _coord2f[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f };

 

	// method two
	if (_is_flipx == false && _is_flipy == false)
	{
		glTexCoord2f(_coord2f[0], _coord2f[1]); glVertex2f(vertexes[0].x, vertexes[0].y);
		glTexCoord2f(_coord2f[2], _coord2f[3]); glVertex2f(vertexes[1].x, vertexes[1].y);
		glTexCoord2f(_coord2f[4], _coord2f[5]); glVertex2f(vertexes[2].x, vertexes[2].y);
		glTexCoord2f(_coord2f[6], _coord2f[7]); glVertex2f(vertexes[3].x, vertexes[3].y);
	}
	else if (_is_flipx == true && _is_flipy == false)
	{
		glTexCoord2f(_coord2f[0], _coord2f[1]); glVertex2f(vertexes[1].x, vertexes[1].y);
		glTexCoord2f(_coord2f[2], _coord2f[3]); glVertex2f(vertexes[0].x, vertexes[0].y);
		glTexCoord2f(_coord2f[4], _coord2f[5]); glVertex2f(vertexes[3].x, vertexes[3].y);
		glTexCoord2f(_coord2f[6], _coord2f[7]); glVertex2f(vertexes[2].x, vertexes[2].y);
	}
	else if (_is_flipx == false && _is_flipy == true)
	{
		glTexCoord2f(_coord2f[0], _coord2f[1]); glVertex2f(vertexes[3].x, vertexes[3].y);
		glTexCoord2f(_coord2f[2], _coord2f[3]); glVertex2f(vertexes[2].x, vertexes[2].y);
		glTexCoord2f(_coord2f[4], _coord2f[5]); glVertex2f(vertexes[1].x, vertexes[1].y);
		glTexCoord2f(_coord2f[6], _coord2f[7]); glVertex2f(vertexes[0].x, vertexes[0].y);
	}
	else if (_is_flipx == true && _is_flipy == true)
	{
		glTexCoord2f(_coord2f[0], _coord2f[1]); glVertex2f(vertexes[2].x, vertexes[2].y);
		glTexCoord2f(_coord2f[2], _coord2f[3]); glVertex2f(vertexes[3].x, vertexes[3].y);
		glTexCoord2f(_coord2f[4], _coord2f[5]); glVertex2f(vertexes[0].x, vertexes[0].y);
		glTexCoord2f(_coord2f[6], _coord2f[7]); glVertex2f(vertexes[1].x, vertexes[1].y);
	}


	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glEnd();

	Node::draw();
















}