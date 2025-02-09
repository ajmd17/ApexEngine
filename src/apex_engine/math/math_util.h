#ifndef MATHUTIL_H
#define MATHUTIL_H

namespace apex
{
	class MathUtil
	{
	public:
		const static float PI;

		static float toDegrees(const float rad)
		{
			return rad * 180.0f / PI;
		}

		static float toRadians(const float deg)
		{
			return deg * PI / 180.0f;
		}

		static float clamp(const float val, const float min, const float max)
		{
			if (val > max)
				return max;
			else if (val < min)
				return min;
			return val;
		}

		static float lerp(const float from, const float to, const float amt)
		{
			return from + amt * (to - from);
		}

		static float min(const float a, const float b)
		{
			if (a < b)
				return a;
			else
				return b;
		}

		static float max(const float a, const float b)
		{
			if (a > b)
				return a;
			else
				return b;
		}
	};
}
#endif