#include"../3party/freetype2/ft2build.h"


#include "../3party/freetype2/freetype/freetype.h"
#include "../3party/freetype2/freetype/ftglyph.h"
#include "../3party/freetype2/freetype/ftoutln.h"
#include "../3party/freetype2/freetype/fttrigon.h"

#include "Text.h"

#include "windows.h"
FT_Library library;

FT_Face face;



Text*Text::create(const std::string&text)
{
	Text*ins = new Text;
	ins->autorelease();
	ins->setString(text);
	return ins;



}
static bool _is_freetype_init = false;


Text::Text() :_fontsize(30),
_is_need_update(true),
_is_need_update_color(false)
{
	if (_is_freetype_init == false)
	{

		FT_Init_FreeType(&library);
		_is_freetype_init = true;
	}



	int err = FT_New_Face(library, "3.ttf", 0, &face);

	if (err == FT_Err_Unknown_File_Format || err)
	{
		log("open ttf file error");
		exit(0);
	}




}




Text::~Text()

{
	//FT_Done_FreeType(library);
	this->clear();

	Ref::s_objectcount -= this->_string.size();


}
LPWSTR toUnicode(const char* _str)
{
	LPWSTR _ret;
	int _len = strlen(_str) * 2;

	_ret = new WCHAR[_len];

	MultiByteToWideChar(CP_ACP, 0, _str, -1, _ret, _len);

	return _ret;
}


CharBitMap *Text::getCharBitMapData(unsigned short _char)
{
	CharBitMap *bitmap = new CharBitMap;




	FT_Set_Pixel_Sizes(face, _fontsize, _fontsize);
	//FT_Set_Char_Size(face, 2*64, 2*64, 900, 900);

	auto _index = FT_Get_Char_Index(face, _char);
	auto _glyph = FT_Load_Glyph(face, _index, FT_LOAD_DEFAULT);


	// 倾斜度，越大就越斜
	// 	float lean = 0.3;
	// 	FT_Matrix matrix;
	// 	matrix.xx = 0x10000L;
	// 	matrix.xy = lean * 0x10000L;
	// 	matrix.yx = 0;
	// 	matrix.yy = 0x10000L;
	// 	FT_Set_Transform(face, &matrix, 0);


	// 	FT_Glyph          glyph;
	// 
	// 	FT_Get_Glyph(face->glyph, &glyph);
	// 	FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 0);
	// 	FT_BitmapGlyph    bitmap_glyph = (FT_BitmapGlyph)glyph;
	// 	FT_Bitmap      bitmap1 = bitmap_glyph->bitmap;


	FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
	FT_Bitmap&bitmap1 = face->glyph->bitmap;






	int width = bitmap1.width;
	int height = bitmap1.rows;

	char* data1 = new char[width*height * 4];
	//	memset(data1, 0, width*height * 4);


	//make a bitmap
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			unsigned char _value = (i >= bitmap1.width || j >= bitmap1.rows) ? 0x0 :
				bitmap1.buffer[i + bitmap1.width*j];

			//R G B A
			data1[(4 * i + (height - j - 1) * width * 4)] = _color3b.r;  //R
			data1[(4 * i + (height - j - 1) * width * 4) + 1] = _color3b.g; // G
			data1[(4 * i + (height - j - 1) * width * 4) + 2] = _color3b.b;//B
			data1[(4 * i + (height - j - 1) * width * 4) + 3] =  _value; //A
		}
	}
	


	//memset(data1, 0xf0, width );

	//	memcpy(data1, bitmap1.buffer, width*height * 4);






	bitmap->data = data1;
	bitmap->height = height;
	bitmap->width = width;
	bitmap->size = width*height * 4;
	bitmap->_char = _char;

	//deal with ' '
	if (_char == 32)
	{
		bitmap->width = _fontsize / 2.0f;
	}


 	log1(" char %d   %d %d", _char, width, height);
// 
// 

	glGenTextures(1, &bitmap->texture_id);

	glBindTexture(GL_TEXTURE_2D, bitmap->texture_id);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);




	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap->width, bitmap->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, bitmap->data);
	//glBindTexture(GL_TEXTURE_2D, bitmap->texture_id);


	return bitmap;

}


void Text::draw()
{

	if (this->_is_need_update)
	{
		this->clear();
		this->updateString();
		this->_is_need_update = false;
	}
	if (this->_is_need_update_color)
	{
		this->updateColor();
		this->_is_need_update_color = false;
	}


	float width = 0;
	float height = 0;

	for (int i = 0; i < _queue.size(); i++)
	{
		CharBitMap*bitmap = _queue[i];


		glLoadIdentity();// vetex can work once

		glBindTexture(GL_TEXTURE_2D, bitmap->texture_id);

		// able alpha blend for the texture who has alpha
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//able opacity
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


		//start to render

		glBegin(GL_QUADS);

		//fix bug of transform of difference window size

		Vec2 windowsize = Director::getInstance()->getWindowSize();

		float xx = -1.0f; //position
		float yy = -1.0f;

		float scaleX = this->getGlobalScale().x; //scale
		float scaleY = this->getGlobalScale().y;

		float imageWidth = bitmap->width / windowsize.x;
		float imageHeight = bitmap->height / windowsize.y;


		// 		for (int ii = 0; ii < i; ii++)
		// 		{
		// 			width += _queue[ii]->width;
		// 		}

		float x, y;
		if (i >= 1)
		{
			width += (_queue[i - 1]->width + _queue[i]->width) / 2.0f;
			width += _fontsize*0.05f;

		}
		else
		{

			width += _queue[i]->width / 2.0f;
		}






		if (_queue[i]->_char <= 0xff)
		{
			height = _queue[i]->height / 2.0f + _fontsize*0.08F;
		}
		else
		{
			height = _fontsize / 2.0f;

		}
		height -= _fontsize *0.08;




		// transform position with inner anchor point
		x = (this->getGlobalPosition().x + width - _rect.x*_anchor.x) / windowsize.x * 2.0f
			+ imageWidth - (0.5)*imageWidth * 2.0f;

		y = (this->getGlobalPosition().y + height-_fontsize*_anchor.y*0.71// - (_anchor.y)*height * 2.0f) 
			)/windowsize.y * 2.0f + imageHeight - (0.5)*imageHeight * 2.0f;

		xx += x;
		yy += y;

		//for different image has different Texcoord
		float _coord2f[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f };


		//	glPushMatrix();


		// transform the vertexs
		glTexCoord2f(_coord2f[0], _coord2f[1]); glVertex2f(-imageWidth*scaleX + xx, -imageHeight*scaleY + yy);
		glTexCoord2f(_coord2f[2], _coord2f[3]); glVertex2f(imageWidth*scaleX + xx, -imageHeight *scaleY + yy);
		glTexCoord2f(_coord2f[4], _coord2f[5]); glVertex2f(imageWidth*scaleX + xx, imageHeight*scaleY + yy);
		glTexCoord2f(_coord2f[6], _coord2f[7]); glVertex2f(-imageWidth*scaleX + xx, imageHeight*scaleY + yy);



		//glPopMatrix();

		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);


		glEnd();
	}
	Node::draw();

}



void Text::updateString()
{
	wchar_t * s = toUnicode(_string.c_str());

	size_t len = wcslen(s);

	for (int i = 0; i < len; i++)
	{
		_queue.push_back(getCharBitMapData(s[i]));

	}


	//deal with  whole string anchor point
	_rect.x = 0;
	_rect.y = _fontsize;


	//calculator the string bitmap width
	for (int i = 0; i < _queue.size(); i++)
	{
		CharBitMap*bitmap = _queue[i];

		float width = 0;
		float x, y;

		width += _queue[i]->width;
		width += _fontsize*0.05f;
		_rect.x += width;

	}
	_rect.x -= _fontsize*0.05f;

}

void Text::setFontSize(int _size)
{
	this->_fontsize = _size;
	this->_is_need_update = true;
}

int Text::getFontSize()const
{
	return  this->_fontsize;
}

void Text::setString(const std::string &_string)
{
	Ref::s_objectcount -= this->_string.size();

	this->_string = _string;
	this->_is_need_update = true;

	Ref::s_objectcount += this->_string.size();

}


const std::string& Text::getString()const
{
	return _string;
}





void Text::clear()
{

	for (int i = 0; i < _queue.size(); i++)
	{
		glDeleteTextures(1, &_queue[i]->texture_id);

		(_queue[i])->release();

	}
	_queue.clear();


}

void Text::setColor(Color3B color)
{
	_color3b = color;

	_is_need_update_color = true;

}


const Color3B& Text::getColor()const
{
	return _color3b;

}

void Text::updateColor()
{


	for (int i = 0; i < _queue.size(); i++)
	{
		CharBitMap* bitmap = _queue[i];

		int height = _queue[i]->height;
		int width = _queue[i]->width;
		auto data = _queue[i]->data;
		//update the bitmap RGB
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				//R G B 
				data[(4 * i + (height - j - 1) * width * 4)] = _color3b.r;  //R
				data[(4 * i + (height - j - 1) * width * 4) + 1] = _color3b.g; // G
				data[(4 * i + (height - j - 1) * width * 4) + 2] = _color3b.b;//B
			}
		}

		glDeleteTextures(1,& bitmap->texture_id);

		glGenTextures(1, &bitmap->texture_id);

		glBindTexture(GL_TEXTURE_2D, bitmap->texture_id);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);




		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap->width, bitmap->height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, bitmap->data);
		//glBindTexture(GL_TEXTURE_2D, bitmap->texture_id);

	}
}


