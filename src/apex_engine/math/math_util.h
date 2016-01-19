#ifndef MATHUTIL_H
#define MATHUTIL_H

class MathUtil
{
public:
	const static float PI;

	static float toDegrees(float rad)
	{
		return rad * 180.0 / PI;
	}

	static float toRadians(float deg)
	{
		return deg * PI / 180.0;
	}

	static float clamp(float val, float min, float max)
	{
		if (val > max)
			return max;
		else if (val < min)
			return min;
		return val;
	}

	static float lerp(float from, float to, float amt)
	{
		return from + amt * (to - from);
	}

	static float min(float a, float b)
	{
		if (a < b)
			return a;
		else
			return b;
	}

	static float max(float a, float b)
	{
		if (a > b)
			return a;
		else
			return b;
	}
};

#endif