#ifndef __TEXTURECACHE__
#define __TEXTURECACHE__





#include "../base/Ref.h" 

#include <vector>
#include <unordered_map>
class Texture2D;





/**
 * @brief all texture will been cache in this if not ,this will add to cache
 * a sprite is get texture from this
 * this will require from texture if not exist in the cache
 */
class DLL TextureCache :public Ref
{

public:
	/**
	 * @return the instance
	 */
	static TextureCache*getInstance();


	/**
	 * @brief add a texture2d in to cache
	 */
	void addTexture2D(Texture2D *texture, std::string &filename);


	/**
	 * @brief remove a texture2d
	 */
	void removeTexture2DByName(const std::string &name);

	/**
	 * @return a texture2d
	 */
	Texture2D*getTexture2DByName(const std::string & name);

	/**
	 * @brief add file to cache
	 * @return Texture2D*
	 */
	Texture2D* addFile(const std::string &file);

	/**
	 * @brief print the cahe info
	 */
	void printInfo();

	/**
	 * @brief remove all textures by call release()
	 */
	void removeAllTextures();

	virtual ~TextureCache();
private:

	std::unordered_map<unsigned int, Texture2D*> _cache_map;//cache map

	/**
	 * @return the hash code by file name
	 */
	unsigned int Hash(const std::string & name);


};











#endif


