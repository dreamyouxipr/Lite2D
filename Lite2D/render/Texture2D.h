#ifndef __TEXTURE2D__
#define __TEXTURE2D__



#include "../base/Ref.h" 
#include "Image.h"


/**
 * @brief  this class for GL render texture2D get 
 * difference data (bmp png jpg )from class Image
 */
class DLL Texture2D :public Ref
{
public:
	static Texture2D*create(const std ::string &file);


	/**
	 * @brief init the texture2d with a image;
	 */
	void initWithImage(Image*image);

	/**
	 * @return the texture id
	 */
	GLuint getTextureID()const;

   /**
    * @return the image size of memeory 
    */
	int getImageSize()const;

   /**
    * @return the file name 
    */
	const std::string & getFileName()const;

	virtual ~Texture2D();

   /**
    * @return the image pixel width and height
    */
	const Vec2 &getRect()const;

   /**
    * @brief  proof the points of coord and texture
	* @see the use
    */
	float * getCoord2fPoints()const;

private:
	GLuint _texture_id;
	Image*_image;
	float *_coord2fpoints;

};







#endif


