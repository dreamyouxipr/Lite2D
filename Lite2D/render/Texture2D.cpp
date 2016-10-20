#include"Texture2D.h"


// the  proof the points of coord and texture points arrary @see use
static float s_coord2f_png_or_jpg[] = { 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f };
static float s_coord2f_bmp[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f };


Texture2D*Texture2D::create(const std::string &file)
{
	Texture2D* tex = new Texture2D;

	auto image = new Image;
	image->initWithFile(file);

	tex->initWithImage(image);
	tex->_image = image;
	tex->autorelease();

	return tex;

}



GLuint Texture2D::getTextureID()const
{
	return _texture_id;

}




void Texture2D::initWithImage(Image*image)
{
	this->_image = image;


	// gain a id
	glGenTextures(1, &_texture_id);
	if (_texture_id == 0)
	{

		ASSERT(false, "gain a id error");

	}

	// bind new texture and init param




	GLenum _type;
	switch (image->getImageType())
	{
	case ImageType::BMP:_type = GL_BGR_EXT, _coord2fpoints = s_coord2f_bmp; break;
	case ImageType::PNG:_type = GL_RGBA, _coord2fpoints = s_coord2f_png_or_jpg; break;
	case ImageType::JPG:_type = GL_RGB, _coord2fpoints = s_coord2f_png_or_jpg; break;


	}

	glBindTexture(GL_TEXTURE_2D, _texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);



	if (image->getImageType() == ImageType::JPG)
	{// for translate  3 bits and 4 bits  
		// jpg file is 3 bits
		//JPG is RGB 3 bytes  GL default is 4 bytes
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0,
		_type, GL_UNSIGNED_BYTE, image->getData());
	glBindTexture(GL_TEXTURE_2D, _texture_id);




}


Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_texture_id);

	_image->release();
}

const Vec2& Texture2D::getRect()const
{
	return _image->getRect();


}


int Texture2D::getImageSize()const
{
	return  _image->getSize();


}

const std::string & Texture2D::getFileName()const
{

	return  _image->getFileName();
}


float *Texture2D::getCoord2fPoints()const
{
	return _coord2fpoints;
}


