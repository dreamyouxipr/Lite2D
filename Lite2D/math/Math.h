#ifndef __LITEMATH__
#define __LITEMATH__

#include "../Macros.h"
#include "../base/Vec2.h"

class DLL Math
{
public:

	/**
	 * @brief convert pix position to gl position
	 */
	static Vec2 convertToGL(const Vec2 &v)
	{
		return Vec2(v.x / 600.0f - 1, v.y / 600.0f - 1);


	}

	static bool isInRect(const Vec2 &leftBottom, const Vec2 &rightUpper, const Vec2 &point);

	static bool isInRect(const Vec2 &leftBottomA, const Vec2 &rightUpperA, const Vec2 &leftBottomB, const Vec2 &rightUpperB);

	static bool isInUI(const Vec2 &position, const Vec2 &size, const Vec2 &anchor, const Vec2 &globalPoint);

	// not pi, just angle
	static float sin(const float &angle);
	static float cos(const float &angle);
};









#endif


