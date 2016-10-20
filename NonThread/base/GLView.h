#ifndef __GLVIEW__
#define __GLVIEW__

#include "../Macros.h"
#include <string>
#include "Ref.h"
#include "Vec2.h"


#include "../glut.h"
#include "../glfw3.h"
class Director;
 

/**
 * @brief the opengl view
 */
class GLView :public Ref
{
public:
	/**
	 * @brief create a GLView and autorelease
	 */


	static GLView*create(const std::string name, float width=800.0f, float height=600.0f);

	void pollEvents();


	void setWindowSize(const Vec2 &size);
	float getWindowX()const;
	float getWindowY()const;
	const Vec2&getWindowSize()const;

	void setWindowsName(const std::string name);
	void swapBuffers();
 
 

   /**
    * @brief print the gpu gl info
    */
	static void printHardWareInfo();


	virtual ~GLView(){};
private:
	std::string _name;
	GLFWwindow*window = nullptr;

	Vec2 _windowSize;
	GLView();

	void init();
	static void GLFW_error(int error, const char* what);

	friend class Director;

	void render();

   /**
    * @brief render the display status include fps and render time
    */


	void renderDisplayStatus();

private:
	
};











#endif


