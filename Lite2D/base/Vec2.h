#ifndef __VEC2__
#define __VEC2__

#include "../Macros.h"



class DLL Vec2
{
public:
	float x, y;
	Vec2();
	Vec2(float x, float y);

	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator-() const;
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator*(const Vec2& rhs) const;
	Vec2 operator*(const float xy) const;

	Vec2 operator/(const Vec2 other);
	Vec2 operator/(const float other);

	bool operator==(float xy);

	void div(float x, float y);
	void mult(float x, float y);
	void add(float x, float y);
	void sub(float x, float y);

	void div(float xy);
	void mult(float xy);
	void add(float xy);
	void sub(float xy);


	void div(const Vec2&other );
	void sub(const Vec2&other);	
	void mult(const Vec2&other);	
	void add(const Vec2&other);

};










#endif


