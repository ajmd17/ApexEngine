#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "../../math/vector3f.h"
#include "../../math/quaternion.h"
#include "../../math/math_util.h"

namespace apex
{
	class Keyframe
	{
	private:
		float time;

		Vector3f translation, tempVec;
		Quaternion rotation, tempRot;
	public:
		Keyframe() {}

		Keyframe(float time, Vector3f translation, Quaternion rotation)
		{
			this->time = time;

			this->translation.set(translation);
			this->rotation.set(rotation);
		}

		Keyframe(float time, Vector3f translation, Vector3f axis, float angleRad)
		{
			this->time = time;

			this->translation.set(translation);

			tempVec.set(axis); tempVec.multiply(-1.0f); // negate
			this->rotation.setFromAxisRad(tempVec, angleRad);
		}

		Quaternion getRotation() const
		{
			return rotation;
		}

		void setRotation(const Quaternion &rotation)
		{
			this->rotation.set(rotation);
		}

		Vector3f getTranslation() const
		{
			return translation;
		}

		void setTranslation(const Vector3f &translation)
		{
			this->translation.set(translation);
		}

		float getTime() const { return time; }

		void setTime(float time) { this->time = time; }

		Keyframe &blend(const Keyframe &to, float amt, Keyframe &outFrame)
		{
			tempVec.set(translation);
			tempVec.lerp(to.getTranslation(), amt);
			tempRot.set(rotation);
			tempRot.slerp(to.getRotation(), amt);

			outFrame = Keyframe(MathUtil::lerp(time, to.getTime(), amt), tempVec, tempRot);
			return outFrame;
		}
	};
}

#endif