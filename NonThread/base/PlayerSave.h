#ifndef __PLAYERSAVE__
#define __PLAYERSAVE__

#include "../Macros.h"


/**
 * @brief using tinyxml for parse data
 */
#define PLAYERSAVE_USING_TINYXML



/**
 * @brief a lite api  interface for data persistence
 * @note you can save and read game data via this  class such as score player'sname etc.
 */
class DLL PlayerSave
{
public:
	static	PlayerSave*getInstance();

	/**
	* @return get value as float
	*/
	virtual float getFloat(const std::string & key)const = 0;

	/**
	* @return get value as int
	*/
	virtual int getInt(const std::string & key)const = 0;

	/**
	* @return get value as std::string
	*/
	virtual  std::string getString(const std::string& key)const = 0;

	/**
	* @return get value as Bool
	*/
	virtual bool getBool(const std::string&key)const = 0;

	/**
	* @brief set value as float
	*/
	virtual void setFloat(const std::string& key, float value) = 0;

	/**
	* @brief set value as int
	*/
	virtual void setInt(const std::string& key, int value) = 0;

	/**
	* @brief set value as std::string
	*/
	virtual void setString(const std::string& key, const std::string& value) = 0;

	/**
	 * @brief set value as Bool
	 */
	virtual void setBool(const std::string &key, bool value) = 0;

	/**
	 * @brief remove key-value
	 */
	virtual void removeKey(const std::string &key) = 0;

	/**
	 * @brief save data to file
	 */
	virtual void save() = 0;

	/**
	 * @brief clear file data
	 */
	virtual void clear() = 0;

	virtual ~PlayerSave(){};
protected:
	// file name to been used
	const char* filename = "Lite2DPlayerSave.xml";
	PlayerSave(){};

};







/*////////////////////////////////////////////////////////////////////////////////////
*
*									using tinyxml for data
*
*
*//////////////////////////////////////////////////////////////////////////////////////
class TiXmlDocument;
/**
 * @brief  using TinyXml 2
 */
class   PlayerSaveTinyXml :public PlayerSave
{

public:

	virtual float getFloat(const std::string & key)const override;
	virtual int getInt(const std::string & key)const override;
	virtual  std::string getString(const std::string& key)const override;

	virtual void setFloat(const std::string& key, float value)override;
	virtual void setInt(const std::string& key, int value)override;
	virtual void setString(const std::string& key, const std::string& value)override;


	virtual bool getBool(const std::string&key)const override;
	virtual void setBool(const std::string &key, bool value) override;

	virtual void removeKey(const std::string&key)override;


	virtual void save() override;
	virtual void clear() override;


	virtual ~PlayerSaveTinyXml();

protected:

	/**
	 * @brief sync doc with current file
	 * @warning will never been call
	 */
	void syncTinyXml();

	PlayerSaveTinyXml();
	friend class PlayerSave;
	TiXmlDocument*doc;//cache for tinyxml
};







/*////////////////////////////////////////////////////////////////////////////////////
*
*									using STL for data
*
*
*//////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief using stl for read and write data
 */
class PlayerSaveSTL :public PlayerSave
{
	virtual float getFloat(const std::string & key)const override;
	virtual int getInt(const std::string & key)const override;
	virtual  std::string getString(const std::string& key)const override;

	virtual void setFloat(const std::string& key, float value)override;
	virtual void setInt(const std::string& key, int value)override;
	virtual void setString(const std::string& key, const std::string& value)override;


	virtual bool getBool(const std::string&key)const override;
	virtual void setBool(const std::string &key, bool value) override;

	virtual void removeKey(const std::string&key)override;


	virtual void save() override;
	virtual void clear() override;


};



#endif
