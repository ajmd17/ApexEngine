#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "lightsource.h"

#include <cstring>
using std::string;

namespace apex
{
	class AmbientLight : public LightSource
	{
	public:
		static const string A_LIGHT_NAME, A_LIGHT_COLOR;
	private:

		string tmpUniform0;
	public:
		AmbientLight();

		AmbientLight(const Vector4f &color);

		virtual void bindLight(int index, Shader &shader);
	};
}

#endif