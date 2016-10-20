#ifndef __SPRITE__
#define __SPRITE__

#include "../render/Texture2D.h"
#include "../base//Node.h"



/**
 * @brief Sprite is a base image show object
 * can run action and animation
 */
class DLL Sprite :public Node
{
public:


	/**
	 * @brief create a Sprite object with autorelease()
	 */
	static Sprite*create(const std::string& file);



	/**
	 * @brief  you should not call this func unless you know what you are doing
	 */
	virtual void draw() override;
	void draw1();

	virtual ~Sprite();


	/**
	 * @return img width and height
	 */
	const Vec2 &getSize()const;

	/**
	 * @brief set thr texture
	 * this will release the origin texture
	 */
	void setTexture2D(Texture2D *texture);

	/**
	 * @return the texture2d
	 */
	Texture2D*getTexture2D()const;

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


private:
	Sprite();
	Texture2D* _texture2d;
	bool _is_flipx;
	bool _is_flipy;

};







#endif


