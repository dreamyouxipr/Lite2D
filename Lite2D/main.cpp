/*


#include <iostream>  //输入输出流 
#include <stdio.h> 
#include <string>
#include <math.h>

#include "conio.h"
#include <stdlib.h>
#include"time.h"
#include<functional>
#include "vector"
 
#include "glut.h"
#include "glfw3.h"
#include <thread>


#include <chrono>
#include <iostream>

#include "windows.h"
//#include "glfw3native.h"

#include "base/Ref.h"

using namespace std;
using namespace std::chrono;





class Sprite
{

private:
	GLuint texture_id = 0;
	double x = 0, dep = 0;
public:
	Sprite(const string&file)
	{
		initWithFile(file);
		x = rand() % 100 / 100.0;
		log("%f", x);
		dep = rand() % 100 / 1000.0;



	}
	
	void initWithFile(const string &file)
	{
		texture_id = loadTexture(file);
		if (texture_id == 0)system("pause");
	}

	void render()
	{


		glBindTexture(GL_TEXTURE_2D, texture_id);

		glBegin(GL_QUADS);


		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5 + x, 0);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5 + x, 0);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5 + x, 0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5 + x, 0);

		glEnd();

		x += 0.01;
		if (x > 1.5)x = -1.5;



	}

protected:
	GLuint loadTexture(const string &file)
	{
		GLint width, height, total_bytes;
		GLubyte* pixels = 0;
		GLuint   texture_ID = 0;


		FILE* pFile = fopen(file.c_str(), "rb");
		if (pFile == 0)
			return 0;


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
			return 0;
		}


		if (fread(pixels, total_bytes, 1, pFile) <= 0)
		{
			free(pixels);
			fclose(pFile);
			return 0;
		}

		{
			GLint max;
			glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);

			{
				const GLint new_width = 256;
				const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
				GLint new_line_bytes, new_total_bytes;
				GLubyte* new_pixels = 0;

				// 计算每行需要的字节数和总字节数
				new_line_bytes = new_width * 3;
				while (new_line_bytes % 4 != 0)
					++new_line_bytes;
				new_total_bytes = new_line_bytes * new_height;

				// 分配内存
				new_pixels = (GLubyte*)malloc(new_total_bytes);

				// 进行像素缩放
				gluScaleImage(GL_RGB,
					width, height, GL_UNSIGNED_BYTE, pixels,
					new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

		
				free(pixels);
				pixels = new_pixels;
				width = new_width;
				height = new_height;


			}
		}
		cout << width;
		// 分配一个新的纹理编号
		glGenTextures(1, &texture_ID);
		if (texture_ID == 0)
		{
			free(pixels);
			fclose(pFile);
			return 0;
		}

		// 绑定新的纹理，载入纹理并设置纹理参数
	
		glBindTexture(GL_TEXTURE_2D, texture_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
			GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, texture_ID);



		free(pixels);
		return texture_ID;


	}





};













GLFWwindow* window;

bool running = true;



void update(double deltaTime)

{
	log("%f", deltaTime);

}


float scale_ = 0.0;



GLuint texGround;

GLuint texGround1;


std::vector<Sprite*> sp_queue;


void render()
{
 
	glClear(GL_COLOR_BUFFER_BIT);

	int len = sp_queue.size();

	for (int i = 0; i < len; i++)
	{
		sp_queue[i]->render();

	}
	glfwSwapBuffers(window);

}


void GLFW_error(int error, const char* description)
{
	cout << description << endl;
}






class A :public Ref
{



};
int main2()
{

	Ref* x = new A;





//	x->release();

	//cout << typeid(*x).name() << endl;
	Ref::printTrack();


//	cout << x->getReferenceCount();

	system("pause");
	return 0;

}




int main1(int argc, char **argv)
{






	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_RED_BITS, 5);
	glfwWindowHint(GLFW_GREEN_BITS, 6);
	glfwWindowHint(GLFW_BLUE_BITS, 5);
	glfwWindowHint(GLFW_ALPHA_BITS, 0);
	glfwWindowHint(GLFW_DEPTH_BITS, 16);
	glfwWindowHint(GLFW_STENCIL_BITS, 0);










	glfwSetErrorCallback(GLFW_error);



	if (glfwInit() == false)
	{
		cout << "ERROR INIT" << endl;

	}



	window = (glfwCreateWindow(600, 600, "GLView", 0, 0));



	glfwMakeContextCurrent(window);

 

	double perFrameTime = 1 / 60.0;

	glEnable(GL_TEXTURE_2D);



	for (int i = 0; i < 100; i++)
	{
		sp_queue.push_back(new Sprite("1.bmp"));

	}

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;
	LARGE_INTEGER perFrame;


	LARGE_INTEGER renderLast;//render time
	LARGE_INTEGER renderNow; //render time

	

	QueryPerformanceFrequency(&nFreq);
	perFrame.QuadPart = (LONGLONG)(1.0 / 60 * nFreq.QuadPart);

	QueryPerformanceCounter(&nLast);

	while (1)
	{

		QueryPerformanceCounter(&nNow);
		if (nNow.QuadPart - nLast.QuadPart > perFrame.QuadPart)
		{
			QueryPerformanceCounter(&renderLast);
			render();//render
			QueryPerformanceCounter(&renderNow);

			glfwPollEvents();

			double fps = (double)(nNow.QuadPart - nLast.QuadPart) / (double)nFreq.QuadPart;
			cout << "FPS:"<<1.0 / fps <<"    ";


			 fps= (double)(renderNow.QuadPart - renderLast.QuadPart) / (double)nFreq.QuadPart ;
			cout <<  fps *1000<< endl;

			nLast.QuadPart = nNow.QuadPart;
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::microseconds(0));
		}
	}



	glfwTerminate();

	return 0;
}





#include "base\Application.h"

int main()
{

	Application app;

	return app.run();


}


*/
