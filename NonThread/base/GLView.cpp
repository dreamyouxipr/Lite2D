#include"GLView.h"


#include <thread>
#include "Director.h"


#include <iostream>

#include "windows.h"

#include "../2d/Sprite.h"


using namespace std;


 

GLView::GLView()
{




}

void GLView::init()
{
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_RED_BITS, 5);
	glfwWindowHint(GLFW_GREEN_BITS, 6);
	glfwWindowHint(GLFW_BLUE_BITS, 5);
	glfwWindowHint(GLFW_ALPHA_BITS, 0);
	glfwWindowHint(GLFW_DEPTH_BITS, 16);
	glfwWindowHint(GLFW_STENCIL_BITS, 0);


 
	glfwSetErrorCallback(GLView::GLFW_error);


	if (glfwInit() == false)
	{
		cout << "ERROR INIT" << endl;

	}


	window = (glfwCreateWindow(_windowSize.x
		, _windowSize.y, _name.c_str(), 0, 0));


	glfwMakeContextCurrent(window);


	
	double perFrameTime = 1 / 60.0;

	glEnable(GL_TEXTURE_2D);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //指定混合函数 

}




void  GLView::GLFW_error(int error, const char* what)
{
	cout << what << endl;
}


GLView*GLView::create(const std::string name, float width, float height)
{
	GLView* ins = new GLView;

	ins->setWindowSize(Vec2(width, height));
	ins->setWindowsName(name);


	ins->init();



	return ins;
}


float GLView::getWindowX()const
{
	return _windowSize.x;
}

float GLView::getWindowY()const
{
	return _windowSize.y;
}

const Vec2& GLView::getWindowSize()const
{
	return _windowSize;
}

void GLView::setWindowsName(const std::string name)
{
	_name = name;
}

void GLView::setWindowSize(const Vec2 &size)
{
	_windowSize = size;
}


void GLView::renderDisplayStatus()
{

	auto dir = Director::getInstance();

	char str[100];
	glColor3f(1.0f, 1.0f, 1.0f);

	//show  pfs
	sprintf(str, "%.1f/%.1f", dir->getFPS(), 1.0f / dir->getRenderTime());
	int n = strlen(str);
	glRasterPos3f(-1, -0.865, 0.0);
	for (int i = 0; i < n; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *(str + i));



	// show the sprite no of scene
	sprintf(str, "%d", Ref::s_objectcount);
	 n = strlen(str);
	glRasterPos3f(-1, -0.92, 0.0);
	for (int i = 0; i < n; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *(str + i));


	


	//show render time
	sprintf(str, "%f", dir->getRenderTime());
	str[7] = '\0';
	n = strlen(str);
	glRasterPos3f(-1, -0.975, 0.0);
	for (int i = 0; i < n; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *(str + i));


}






void GLView::render()
{

	glClear(GL_COLOR_BUFFER_BIT);


	/*glColor3f(0, 0, 0);

	glBegin(GL_QUADS);

	glVertex2f(0.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);

	glEnd();
	*/
	//	sp->retain();















}

void GLView::swapBuffers()
{
	glfwSwapBuffers(window);

}

void GLView::pollEvents()
{
	glfwPollEvents();

}

void GLView::printHardWareInfo()
{
	log("[GLView]:OpenGL Version:%s", glGetString(GL_VERSION));
	log("[GLView]:OpenGL GPU:%s\n", glGetString(GL_RENDERER)); 
}







