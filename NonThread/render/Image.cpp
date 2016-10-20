#include"Image.h"

#include <iostream>


#include "../3party/png/png.h"
#include "../3party/png/pngconf.h"
#include "../3party/jpeg/jpeglib.h"



Image::Image() :
_data(nullptr)
{

}


ImageType Image::getImageType()const
{
	return _type;
}


const GLubyte *Image::getData()const
{
	return _data;

}


const Vec2 & Image::getRect()const
{
	return _rect;
}


int Image::getSize()const
{
	return size;

}


const std::string& Image::getFileName()const
{

	return this->file;
}



Image::~Image()
{
	if (_data)
	{
		free((void*)_data);
	}
}




void Image::loadWithBmp()
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;

	FILE* pFile = fopen(file.c_str(), "rb");

	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, 54, SEEK_SET);

	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}


	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		ASSERT(false, " alloc error");

	}


	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		ASSERT(false, "read file error");


	}
	GLint new_line_bytes, new_total_bytes;


	static int points[] = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 };


	GLint new_width = width;
	GLint new_height = height;

	//cache real file width and height
	_rect.x = width;
	_rect.y = height;


	for (int i = 0; i < 11; i++)
	{
		if (new_width>points[i] && new_width <= points[1 + i])
		{
			new_width = points[1 + i];
			break;
		}


	}


	for (int i = 0; i < 11; i++)
	{
		if (new_height>points[i] && new_height <= points[1 + i])
		{
			new_height = points[1 + i];
			break;
		}


	}

	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);

		{

			GLubyte* new_pixels = 0;

			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// alloc memeory
			new_pixels = (GLubyte*)malloc(new_total_bytes);

			// scale image to fix 2^n;
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			free(pixels);
			pixels = new_pixels;
			this->width = new_width;
			this->height = new_height;

		}
	}

	_data = pixels;

	size = new_total_bytes;

}



void Image::loadWithPng()
{

	FILE* file = fopen(this->file.c_str(), "rb");

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

	png_infop info_ptr = png_create_info_struct(png_ptr);

	setjmp(png_jmpbuf(png_ptr));


	png_init_io(png_ptr, file);


	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);



	int m_width = png_get_image_width(png_ptr, info_ptr);
	int m_height = png_get_image_height(png_ptr, info_ptr);


	int color_type = png_get_color_type(png_ptr, info_ptr);

	int size = m_height * m_width * 4;

	unsigned char* rgba = (unsigned char*)malloc(size);

	int pos = 0;

	png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < (4 * m_width); j += 4)
		{
			rgba[pos++] = row_pointers[i][j];  //R
			rgba[pos++] = row_pointers[i][j + 1];  //B 
			rgba[pos++] = row_pointers[i][j + 2];    //G
			rgba[pos++] = row_pointers[i][j + 3];  //A
		}
	}
	png_destroy_read_struct(&png_ptr, &info_ptr, 0);

	fclose(file);
	auto _data = rgba;

	this->width = m_width;
	this->height = m_height;
	this->size = size;

	_rect.x = m_width;
	_rect.y = m_height;


	this->_data = rgba;

}


void Image::loadWithJpg()
{

	struct jpeg_decompress_struct cinfo;


	unsigned char *data;

	FILE *file;


	//open the file
	file = fopen(this->file.c_str(), "rb");

	jpeg_error_mgr jerr;



	cinfo.err = jpeg_std_error(&jerr);

	// init 

	jpeg_create_decompress(&cinfo);



	// data src
	jpeg_stdio_src(&cinfo, file);

	//read header
	jpeg_read_header(&cinfo, TRUE);


	jpeg_start_decompress(&cinfo);



	// read jpg info
	int row = cinfo.image_width * cinfo.num_components;

	int width = cinfo.image_width;

	int height = cinfo.image_height;

	// alloc memeory
	data = (unsigned char*)(malloc(row * height));

	unsigned char** row_data = new unsigned char*[height];
	for (int i = 0; i < height; i++)
	{
		row_data[i] = &(data[i*row]);
	}


	//read data

	int rowsRead = 0;

	while (cinfo.output_scanline < cinfo.output_height)
	{
		rowsRead += jpeg_read_scanlines(&cinfo, &row_data[rowsRead],
			cinfo.output_height - rowsRead);
	}


	delete[] row_data;

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	this->width = width;
	this->height = height;
	this->_data = data;
	this->size = row*this->height;

	_rect.x = this->width;
	_rect.y = this->height;

}



void Image::initWithFile(const std::string&file)
{
	this->file = file;

	std::string ext = file.substr(file.size() - 3, 3);
	
	if (ext == "png")
	{
		_type = ImageType::PNG;
		loadWithPng();
	}
	else if (ext == "bmp")
	{
		loadWithBmp();
		_type = ImageType::BMP;
	}
	else if (ext == "jpg")
	{
		loadWithJpg();
		_type = ImageType::JPG;
	}



//	log("%s", ext.c_str());



}
