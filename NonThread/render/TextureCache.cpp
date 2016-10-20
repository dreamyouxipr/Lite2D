#include"TextureCache.h"
#include "Texture2D.h"

#include "../3party/xxhash/xxhash.h"

static TextureCache*ins = nullptr;

TextureCache*  TextureCache::getInstance()
{
	if (ins == nullptr)
	{
		ins = new TextureCache;
	}
	return ins;


}



unsigned int TextureCache::Hash(const std::string & name)
{
	return XXH32(name.c_str(), name.size(), 0);


}


Texture2D*TextureCache::getTexture2DByName(const std::string & name)
{
	auto hash = Hash(name);

	auto iter = _cache_map.find(hash);

	if (iter == _cache_map.end())
	{
		// can not find the texture the create a texture

		auto texture = Texture2D::create(name);
		texture->retain();
		_cache_map.insert(std::pair<unsigned int, Texture2D*>(hash, texture));

		return texture;
	}
	return iter->second;



}


Texture2D* TextureCache::addFile(const std::string &file)
{
	auto hash = Hash(file);

	auto iter = _cache_map.find(hash);

	if (iter != _cache_map.end())
	{
		return iter->second;
	}

	auto texture = Texture2D::create(file.c_str());
	texture->retain();

	_cache_map.insert(std::pair<unsigned int, Texture2D*>(hash, texture));

	return texture;
}


void TextureCache::addTexture2D(Texture2D *texture, std::string &filename)
{
	_cache_map.insert(std::pair<unsigned int, Texture2D*>(Hash(filename), texture));

}


void TextureCache::removeTexture2DByName(const std::string &name)
{
	auto iter = _cache_map.find(Hash(name));

	if (iter == _cache_map.end())
	{
		return;


	}

	_cache_map.erase(iter);

}

void TextureCache::removeAllTextures()
{
	for (const auto& tex : _cache_map)
	{

		tex.second->release();
	}

	_cache_map.clear();
}


void TextureCache::printInfo()
{
	int total = 0, count = 0;
	Texture2D*texture;

	//scan all cache
	for (const auto& tex1 : _cache_map)
	{
		++count;
		texture = tex1.second;

		total += texture->getImageSize();

		log("[TextureCache]: file:%s   size:%d Kb   width:%d pix   height:%d pix   Ref count:%d ",
			texture->getFileName().c_str(), texture->getImageSize() / 1024
			, (int)(texture->getRect().x),
			(int)(texture->getRect().y), texture->getReferenceCount());

	}
	log("[TextureCache]:total %d Kb  %d files\n", total / 1024, count);


}



TextureCache::~TextureCache()
{

	this->removeAllTextures();
}