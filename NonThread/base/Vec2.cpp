#include"Vec2.h"

Vec2::Vec2() :x(0.0f), y(0.0f)
{

}

Vec2::Vec2(float x, float y)
{
	this->x = x;
	this->y = y;

}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(this->x + rhs.x, this->y + rhs.y);
}

Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const Vec2& rhs) const
{
	return Vec2{ this->x*rhs.x, this->y * rhs.y };
}

Vec2  Vec2::operator/(const Vec2 other)
{

	return Vec2(this->x/other.x,this->y/other.y);
}


Vec2  Vec2::operator/(float other)
{
 
	return Vec2(this->x/other,this->y/other);
}


bool Vec2::operator==(float xy)
{
	return (this->x == xy&&this->y == xy);

}






Vec2 Vec2::operator*(const float xy) const
{
	return Vec2{ this->x*xy, this->y * xy};
}



void Vec2::div(float x, float y)
{
	this->x = this->x / x;
	this->y = this->y / y;
}


void Vec2::add(float x, float y)
{
	this->x = this->x + x;
	this->y = this->y + y;
}


void Vec2::mult(float x, float y)
{
	this->x *= x;
	this->y *= y;
}


void Vec2::sub(float xy)
{
	this->x -= x;
	this->y -= y;
}

void Vec2::div(float xy)
{
	this->x /= xy;
	this->y /= xy;
}


void Vec2::add(float xy)
{
	this->x += xy;
	this->y += xy;
}


void Vec2::mult(float xy)
{
	this->x *= xy;
	this->y *= xy;
}














void Vec2::div(const Vec2 &other)
{
	this->x /= other.x;
	this->y /= other.y;
}


void Vec2::add(const Vec2 &other)
{
	this->x += other.x;
	this->y += other.y;
}


void Vec2::mult(const Vec2 &other)
{
	this->x *= other.x;
	this->y *= other.y;
}


void Vec2::sub(const Vec2 &other)
{
	this->x -= other.x;
	this->y -= other.y;
}
