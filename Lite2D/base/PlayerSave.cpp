#include"PlayerSave.h"
#include "../3party/tinyxml/tinyxml.h"
#include <fstream>
#include <thread>

PlayerSave* PlayerSave::getInstance()
{
	static PlayerSave*ins = nullptr;

	if (ins == nullptr)
	{

#ifdef PLAYERSAVE_USING_TINYXML
		ins = new PlayerSaveTinyXml;
#else
		ins = new PlayerSaveSTL;
#endif
	}

	return ins;
}



/*////////////////////////////////////////////////////////////////////////////////////
*
*									using tinyxml for data
*
*
*//////////////////////////////////////////////////////////////////////////////////////


static TiXmlElement *FindElement(TiXmlDocument*doc, const std::string & key)
{
	auto root = doc->RootElement();

	while (root)
	{
		if (root->Value() == key)
		{
			return root;
		}
		root = root->NextSiblingElement();
	}

	return nullptr;
}


PlayerSaveTinyXml::PlayerSaveTinyXml()
{
	doc = new TiXmlDocument(filename);
	doc->LoadFile(TiXmlEncoding::TIXML_ENCODING_UTF8);
}


PlayerSaveTinyXml::~PlayerSaveTinyXml()
{
	delete doc;
}


void PlayerSaveTinyXml::setFloat(const std::string& key, float value)
{

	TiXmlElement*ele = FindElement(doc, key);

	char str[100];
	sprintf(str, "%f", value);

	if (ele)
	{//replace the element
		auto child = ele->FirstChild();
		child->SetValue(str);

	}
	else
	{//create a new element
		ele = new TiXmlElement(key.c_str());
		ele->LinkEndChild(new TiXmlText(str));
		doc->LinkEndChild(ele);
	}
	this->save();

}


void PlayerSaveTinyXml::setInt(const std::string& key, int value)
{

	TiXmlElement*ele = FindElement(doc, key);

	char str[100];
	sprintf(str, "%d", value);

	if (ele)
	{//replace the element
		auto child = ele->FirstChild();
		child->SetValue(str);

	}
	else
	{//create a new element
		ele = new TiXmlElement(key.c_str());
		ele->LinkEndChild(new TiXmlText(str));
		doc->LinkEndChild(ele);
	}
	this->save();



}



void PlayerSaveTinyXml::setString(const std::string& key, const std::string& value)
{

	TiXmlElement*ele = FindElement(doc, key);

	if (ele)
	{//replace the element
		auto child = ele->FirstChild();
		child->SetValue(value.c_str());

	}
	else
	{//create a new element
		ele = new TiXmlElement(key.c_str());
		ele->LinkEndChild(new TiXmlText(value.c_str()));
		doc->LinkEndChild(ele);
	}
	this->save();




}


float PlayerSaveTinyXml::getFloat(const std::string& key)const
{

	TiXmlElement*ele = FindElement(doc, key);

	if (ele)
	{
		return  atof(ele->FirstChild()->Value());
	}
	else
	{
		return 0.0f;
	}
}


int PlayerSaveTinyXml::getInt(const std::string& key)const
{
	TiXmlElement*ele = FindElement(doc, key);

	if (ele)
	{
		return  atoi(ele->FirstChild()->Value());
	}
	else
	{
		return 0;
	}

}



std::string PlayerSaveTinyXml::getString(const std::string& key)const
{

	TiXmlElement*ele = FindElement(doc, key);
	std::string str;

	if (ele)
	{

		str = std::string(ele->FirstChild()->Value());

	}
	return  std::move(str);

}


bool PlayerSaveTinyXml::getBool(const std::string &key)const
{

	TiXmlElement*ele = FindElement(doc, key);

	if (ele)
	{
		return  !strcmp(ele->FirstChild()->Value(), "true");
	}
	else
	{
		return false;
	}


}

void PlayerSaveTinyXml::setBool(const std::string& key, bool value)
{


	TiXmlElement*ele = FindElement(doc, key);

	char * str;

	if (value)
	{
		str = "true";
	}
	else
	{
		str = "false";
	}

	if (ele)
	{//replace the element
		auto child = ele->FirstChild();
		child->SetValue(str);
	}
	else
	{//create a new element
		ele = new TiXmlElement(key.c_str());
		ele->LinkEndChild(new TiXmlText(str));
		doc->LinkEndChild(ele);
	}
	this->save();


}


void PlayerSaveTinyXml::removeKey(const std::string&key)
{

	TiXmlElement*ele = FindElement(doc, key);
	if (ele)
	{
		doc->RemoveChild(ele);
		this->save();
	}
}


void PlayerSaveTinyXml::save()
{
	std::thread t([&]()
	{
		doc->SaveFile();
	});

	t.detach();
}


void PlayerSaveTinyXml::clear()
{
	// 	std::fstream file;
	// 	file.open(filename, std::ios::out);
	// 
	// 	file.write("",strlen(""));	 
	// 
	// 	file.close();

	doc->Clear();
	this->save();

}


void PlayerSaveTinyXml::syncTinyXml()
{
	delete doc;
	doc = new TiXmlDocument(filename);
	doc->LoadFile(TiXmlEncoding::TIXML_ENCODING_UTF8);

}



/*////////////////////////////////////////////////////////////////////////////////////
*
*									using STL for data
*
*
*//////////////////////////////////////////////////////////////////////////////////////


void PlayerSaveSTL::setFloat(const std::string& key, float value)
{


}


void PlayerSaveSTL::setInt(const std::string& key, int value)
{


}



void PlayerSaveSTL::setString(const std::string& key, const std::string& value)
{


}


float PlayerSaveSTL::getFloat(const std::string& key)const
{

	return 0.0f;
}


int PlayerSaveSTL::getInt(const std::string& key)const
{
	return 0;

}



std::string PlayerSaveSTL::getString(const std::string& key)const
{
	return "";
}


bool PlayerSaveSTL::getBool(const std::string &key)const
{
	return false;
}

void PlayerSaveSTL::setBool(const std::string& key, bool value)
{

}


void PlayerSaveSTL::removeKey(const std::string&key)
{

}


void PlayerSaveSTL::save()
{
	std::thread t([&]()
	{

	});

	t.detach();
}


void PlayerSaveSTL::clear()
{


}
