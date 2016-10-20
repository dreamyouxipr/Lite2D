#ifndef __IMAGE__
#define __IMAGE__


#include "../base/Ref.h"


#include "../glut.h"
#include "../glfw3.h"
#include "../base/Vec2.h"



enum class ImageType
{
	PNG,
	JPG,
	BMP
};


/**
 * @brief  read difference image file to one binary image data
 * @note we support bmp jpg png file;
 * for difference file type  tranfrm to one type bianary data for Texture2D
 */
class DLL Image :public Ref
{
public:


	/**
	 * @brief init image with a file
	 */
	void initWithFile(const std::string &file);

	/**
	 * @retuen the binary  image data
	 */
	const GLubyte*getData()const;


	/**
	 * @return image's width and height
	 */
	const Vec2& getRect()const;


	/**
	 * @return the memeory size;
	 */
	int getSize()const;


	/**
	 * @return image file name;
	 */
	const std::string &getFileName()const;

	/**
	 * @return the file type
	 * only bmp jpg png are support
	 */
	ImageType  getImageType()const;

	/**
	 * @note release the binary data;
	 */
	virtual ~Image();
	Image();
private:

	int size;// the memeory size ,bytes

	/**
	 * @brief load the bmp file
	 */
	void loadWithBmp();

	/**
	* @brief load the png file
	*/
	void loadWithPng();

	/**
	* @brief load the jpg file
	*/
	void loadWithJpg();


	Vec2 _rect;//file width and height
	Vec2 _rectVec;// the rect width and height


	const GLubyte *_data;// image binary data
	ImageType _type;//image type 
	std::string file; //file name
public:

	GLint width, height;// texture height width

};




#endif


