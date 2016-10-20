//#include "../base/Node.h"


#include "Sprite.h"

#include "../render/TextureCache.h"



Sprite*Sprite::create(const std::string& file)
{
	Sprite*sp = new Sprite;

	//	sp->_texture2d = Texture2D::create(file.c_str());

	sp->_texture2d = TextureCache::getInstance()->addFile(file);
	sp->_texture2d->retain();
	sp->autorelease();

	++s_objectcount;

	return sp;

}


Sprite::Sprite() :
_is_flipy(false),
_is_flipx(false)
{

}


void Sprite::draw()
{

	if (!_visible)
	{
		return;
	}




	glLoadIdentity();// vetex can work once


	glBindTexture(GL_TEXTURE_2D, _texture2d->getTextureID());

	// able alpha blend for the texture who has alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);




	//able opacity
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glColor4f(1.0f, 1.0f, 1.0f, _opactiy);



	//start to render





	glBegin(GL_QUADS);

	//fix bug of transform of difference window size

	  Vec2 windowSize = Director::getInstance()->getWindowSize();

	auto originalSize = _texture2d->getRect();
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

	float *_coord2f = _texture2d->getCoord2fPoints();

	/*
	there are two methods to slove flip
	*/


	//method one
	/*
	int _index_1 = 0;
	int _index_2 = 1;
	int _index_3 = 2;
	int _index_4 = 3;

	if (_is_flipx)
	{
	_index_1 = 2; _index_3 = 0;
	}
	if (_is_flipy)
	{
	_index_2 = 3;	_index_4 = 1;
	}


	glTexCoord2f(_coord2f[0], _coord2f[1]); glVertex2f(vertexes[_index_1].x, vertexes[_index_1].y);
	glTexCoord2f(_coord2f[2], _coord2f[3]); glVertex2f(vertexes[_index_2].x, vertexes[_index_2].y);
	glTexCoord2f(_coord2f[4], _coord2f[5]); glVertex2f(vertexes[_index_3].x, vertexes[_index_3].y);
	glTexCoord2f(_coord2f[6], _coord2f[7]); glVertex2f(vertexes[_index_4].x, vertexes[_index_4].y);
	*/


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





	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glEnd();

	Node::draw();

}





void Sprite::draw1()
{

	if (!_visible)
	{
		return;
	}

	glLoadIdentity();// vetex can work once


	glBindTexture(GL_TEXTURE_2D, _texture2d->getTextureID());

	// able alpha blend for the texture who has alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);




	//able opacity
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glColor4f(1.0f, 1.0f, 1.0f, _opactiy);



	//start to render


	glBegin(GL_QUADS);

	//fix bug of transform of difference window size

	Vec2 windowsize = Director::getInstance()->getWindowSize();

	float xx = -1.0f; //position
	float yy = -1.0f;

	float scaleX = this->getGlobalScale().x; //scale
	float scaleY = this->getGlobalScale().y;

	float imageWidth = _texture2d->getRect().x / windowsize.x;
	float imageHeight = _texture2d->getRect().y / windowsize.y;

	// transform position with anchor point
	float x = (this->getGlobalPosition().x) / windowsize.x * 2.0f + imageWidth - (_anchor.x)*imageWidth * 2.0f;
	float y = (this->getGlobalPosition().y) / windowsize.y * 2.0f + imageHeight - (_anchor.y)*imageHeight * 2.0f;

	xx += x;
	yy += y;

	//for different image has different Texcoord
	float *_coord2f = _texture2d->getCoord2fPoints();


	//	glPushMatrix();


	// transform the vertexs
	glTexCoord2f(_coord2f[0], _coord2f[1]); glVertex2f(-imageWidth*scaleX + xx, -imageHeight*scaleY + yy);
	glTexCoord2f(_coord2f[2], _coord2f[3]); glVertex2f(imageWidth*scaleX + xx, -imageHeight *scaleY + yy);
	glTexCoord2f(_coord2f[4], _coord2f[5]); glVertex2f(imageWidth*scaleX + xx, imageHeight*scaleY + yy);
	glTexCoord2f(_coord2f[6], _coord2f[7]); glVertex2f(-imageWidth*scaleX + xx, imageHeight*scaleY + yy);


	//static float s_coord2f_bmp[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f };






	glRotatef(30, 1, 1, 1);



	//glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);





	glEnd();

	//	Node::draw();

}



Sprite::~Sprite()
{
	--s_objectcount;

	_texture2d->release();
}


const Vec2 &   Sprite::getSize()const
{
	return _texture2d->getRect();


}

void Sprite::setTexture2D(Texture2D *texture)
{
	this->_texture2d->release();
	this->_texture2d = texture;
	this->_texture2d->retain();


}

Texture2D* Sprite::getTexture2D()const
{
	return this->_texture2d;
}

void  Sprite::setFlipX(bool _is)
{
	this->_is_flipx = _is;
}


void  Sprite::setFlipY(bool _is)
{
	this->_is_flipy = _is;
}


bool  Sprite::getFlipX()const
{
	return this->_is_flipx;
}


bool  Sprite::getFlipY()const
{
	return this->_is_flipy;
}