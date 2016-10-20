#ifndef __TEXT__
#define __TEXT__

#include "../base/Node.h"
#include "../glfw3.h"
#include "../glut.h"
class CharBitMap :public Ref
{
public:

	CharBitMap() :
		data(nullptr),
		width(0),
		height(0)
	{

	};

	void clear()
	{
		width = 0;
		height = 0;
		size = 0;
		texture_id = 0;
	}

	char*data;
	int width;
	int height;
	int size;
	unsigned short _char;
	virtual ~CharBitMap()
	{
		delete[] data;
	}
	GLuint texture_id;
};




class DLL VectorData :public Ref
{
public:
	void push(char*data, int size)
	{
		char* tmp = new char[_size + size];


		if (this->_size == 0)
		{
			memcpy(tmp, data, size);

			this->_size += size;


			_bytes = tmp;

			return;
		}

		memcpy(tmp, _bytes, _size);

		memcpy(tmp + size, data, size);

		this->_size += size;

	 


		_bytes = tmp;
	}
	void clear()
	{
		delete[] _bytes;
		_size = 0;
		_bytes = nullptr;

	}

	char*getData()const
	{
		return _bytes;
	}


	int getSize()const
	{
		return _size;
	}

	~VectorData(){ delete _bytes; }
	VectorData():_size(0),_bytes(nullptr){}

private:

	int _size ;
 
	char*_bytes;

};








class DLL Text :public Node
{
public:

	static Text*create(const std::string &text);

	void setString(const std::string &_string);
	const std::string& getString()const;

	Text();
	virtual ~Text();


	virtual void draw()override;

	void setFontSize(int _size);
	int getFontSize()const;
	void setColor(Color3B color);
	const Color3B& getColor()const;

private:

	std::string _string;
	int _fontsize;
	bool _is_need_update;
	bool _is_need_update_color;

	Color3B _color3b;

protected:
	/**
	 * @return a char bitmap data
	 */
	CharBitMap* getCharBitMapData(unsigned short _char);


  
	void clear();

	std::vector<CharBitMap*> _queue;

	Vec2 _rect;
	void updateColor();
	void updateString();
};








#endif


