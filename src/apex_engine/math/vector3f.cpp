#include "vector3f.h"
#include "matrix_util.h"

namespace apex
{
	const Vector3f Vector3f::Zero(0.0);
	const Vector3f Vector3f::One(1.0);
	const Vector3f Vector3f::UnitX(1.0, 0.0, 0.0);
	const Vector3f Vector3f::UnitY(0.0, 1.0, 0.0);
	const Vector3f Vector3f::UnitZ(0.0, 0.0, 1.0);

	Vector3f &Vector3f::rotate(const Vector3f &axis, float angle)
	{
		MatrixUtil::setToRotation(tmpRot, axis, angle);
		transform(tmpRot);
		return *this;
	}
}