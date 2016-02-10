#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "lightsource.h"

#include <cstring>
using std::string;

namespace apex
{
	const string A_LIGHT_NAME = "Env_AmbientLight", A_LIGHT_COLOR = "color";
	class AmbientLight : public LightSource
	{
	public:
	private:

		string tmpUniform0;
	public:
		AmbientLight();

		AmbientLight(const Vector4f &color);

		virtual void bindLight(int index, Shader &shader);
	};
}

#endif