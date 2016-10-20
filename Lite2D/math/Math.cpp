#include "Math.h"
#include <thread>

bool Math::isInRect(const Vec2& leftBottom, const Vec2& rightUpper, const Vec2& point)
{
	return leftBottom.x <= point.x && rightUpper.x >= point.x && // compare x
		leftBottom.y <= point.y && rightUpper.y >= point.y; // compare y
}

bool Math::isInRect(const Vec2& leftBottomA, const Vec2& rightUpperA, const Vec2& leftBottomB, const Vec2& rightUpperB)
{
	return leftBottomA.x <= leftBottomB.x && leftBottomA.y <= leftBottomB.y && // left bottom compare
		rightUpperA.x >= rightUpperB.x && rightUpperA.y >= rightUpperB.y; // right upper compare
}

bool Math::isInUI(const Vec2& position, const Vec2& size, const Vec2& anchor, const Vec2& globalPoint)
{
	Vec2 leftBottom(position.x - size.x*anchor.x, position.y - size.y*anchor.y);
	auto rightUpper = size + leftBottom;
	return isInRect(leftBottom, rightUpper, globalPoint);
}

 
float Math::sin(const float& angle)
{
	static const int scale = 200;
	static const int maxAngle = 360 * scale;
	static const int arraySize = maxAngle / 4;
	static float _sin[arraySize] = { 0 };
	// init sin
	if (!_sin[1])
	{
		if (auto prf = fopen("sin.dat", "rb"))
		{
			fread(&_sin, sizeof(float), arraySize, prf);
			fclose(prf);
		}
		else
		{
			const auto step = 3.1415926535898 / (arraySize * 2);
			auto radian = .0;
			for (int i = 0; i < arraySize; ++i, radian += step)
			{
				_sin[i] = static_cast<float>(std::sin(radian));
			}
			auto t = std::thread([=]
			{
			// write into file
			if (FILE *pwf = fopen("sin.dat", "wb"))
			{
				fwrite(_sin, sizeof(float), arraySize, pwf);
				fclose(pwf);
			}
			});

			t.detach();

		}
	}

	auto realAngle = angle*scale;
	if (realAngle >= maxAngle || realAngle < 0)
	{
		realAngle = int(realAngle + (realAngle >= 0 ? 0.5 : -0.5)) % maxAngle;
		if (realAngle < 0)
			realAngle += 360;
	}

	int index = int(realAngle);
	switch (index / arraySize)
	{
	case 0:
		return _sin[index];
	case 1:
		if (index == arraySize)
			return 1;
		return _sin[2 * arraySize - index];
	case 2:
		return -_sin[index - 2 * arraySize];
	case 3:
		if (index == 3 * arraySize)
			return -1;
		return -_sin[maxAngle - index];
	}
	return 0;
}

float Math::cos(const float& angle)
{
	return sin(angle + 90);
}