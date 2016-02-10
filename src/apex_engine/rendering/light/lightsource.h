#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

// Abstract class for anything that may emit light in the scene
// Author: Andrew MacDonald

#include "../../math/vector4f.h"

namespace apex
{
	class Shader;

	class LightSource
	{
	public:
		virtual void bindLight(int index, Shader &shader) = 0;
	protected:
		Vector4f color;
	public:
		const Vector4f &getColor() { return color; }

		void setColor(const Vector4f &color) { this->color.set(color); }
	};
}
#endif