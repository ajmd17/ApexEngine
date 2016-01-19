#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vector3f.h"
#include "matrix4f.h"
#include "quaternion.h"
#include "matrix_util.h"

class Transform
{
private:
	bool matrixUpdateNeeded;

	Vector3f translation;
	Quaternion rotation;
	Vector3f scale;
	Matrix4f matrix, transMat, rotMat, scaleMat, rotScaleTrans;

	void updateMatrix()
	{
		MatrixUtil::setToTranslation(transMat, translation);
		MatrixUtil::setToRotation(rotMat, rotation);
		MatrixUtil::setToScaling(scaleMat, scale);

		rotScaleTrans.set(rotMat);
		rotScaleTrans.multStore(scaleMat);
		rotScaleTrans.multStore(transMat);

		this->matrix = rotScaleTrans;
	}

public:
	Transform() {}

	Transform(Transform &other) 
	{
		this->translation = other.translation;
		this->rotation = other.rotation;
		this->scale = other.scale;
	}

	Transform(Vector3f &translation, Quaternion &rotation, Vector3f &scale)
	{
		this->setTranslation(translation);
		this->setRotation(rotation);
		this->setScale(scale);
	}

	Matrix4f &getMatrix()
	{
		if (matrixUpdateNeeded)
		{
			updateMatrix();
			matrixUpdateNeeded = false;
		}
		return this->matrix;
	}

	Vector3f &getTranslation()
	{
		return translation;
	}

	void setTranslation(Vector3f &translation)
	{
		this->translation.set(translation);
		matrixUpdateNeeded = true;
	}

	Quaternion &getRotation()
	{
		return rotation;
	}

	void setRotation(Quaternion &rotation)
	{
		this->rotation.set(rotation);
		matrixUpdateNeeded = true;
	}

	Vector3f &getScale()
	{
		return scale;
	}

	void setScale(Vector3f &scale)
	{
		this->scale.set(scale);
		matrixUpdateNeeded = true;
	}
};

#endif
