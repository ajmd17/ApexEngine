#ifndef SPATIAL_H
#define SPATIAL_H

// Defines an object in a space. 3D by default. 2D if you ignore the Z value.
// Author: Andrew MacDonald

#include "../math/vector3f.h"
#include "../math/quaternion.h"
#include "../math/matrix4f.h"
#include "../math/transform.h"
#include "../math/boundingbox.h"
#include "../assets/loadableobject.h"

#include <string>
using std::string;

class Spatial : public ILoadableObject // A spatial is loadable as a resource
{
protected:
	string name;

	Vector3f localTranslation;
	Vector3f localScale;
	Quaternion localRotation;

	Transform globalTransform;
	Matrix4f globalMatrix;
private:
	Vector3f tmpGlobalTrans, tmpGlobalScale;
	Quaternion tmpGlobalRot;

	Spatial *parent;

	bool attachedToRoot;
	bool updateNeeded;

	virtual void updateGlobalBoundingBox() = 0;

	virtual void updateLocalBoundingBox() = 0;
public:
	Spatial() 
	{
		this->name = "";
		this->parent = 0;
		this->updateNeeded = false;
		this->attachedToRoot = false;
	}

	Spatial(string name)
	{
		this->name = name;
		this->parent = 0;
		this->updateNeeded = false;
		this->attachedToRoot = false;
	}

	~Spatial() {}

	void setName(string name)
	{
		this->name = name;
	}

	string getName() const
	{
		return name;
	}

	Transform &getGlobalTransform()
	{
		return globalTransform;
	}

	Matrix4f &getGlobalMatrix()
	{
		return globalMatrix;
	}

	void updateGlobalRotation(Quaternion &out)
	{
		out.multStore(localScale);
		if (parent != 0)
		{
			parent->updateGlobalRotation(out);
		}
	}

	Quaternion getUpdatedGlobalRotation ()
	{
		tmpGlobalRot.set(0.0, 0.0, 0.0, 1.0);
		updateGlobalRotation(tmpGlobalRot);
		return tmpGlobalRot;
	}

	void updateGlobalScale(Vector3f &out)
	{
		out.multStore(localScale);
		if (parent != 0)
		{
			parent->updateGlobalScale(out);
		}
	}

	Vector3f getUpdatedGlobalScale()
	{
		tmpGlobalScale.set(1.0, 1.0, 1.0);
		updateGlobalScale(tmpGlobalScale);
		return tmpGlobalScale;
	}

	void updateGlobalTranslation(Vector3f &out)
	{
		out.addStore(localTranslation);
		if (parent != 0)
		{
			parent->updateGlobalTranslation(out);
		}
	}

	Vector3f getUpdatedGlobalTranslation()
	{
		tmpGlobalTrans.set(0.0, 0.0, 0.0);
		updateGlobalTranslation(tmpGlobalTrans);
		return tmpGlobalTrans;
	}

	Vector3f &getGlobalTranslation()
	{
		return globalTransform.getTranslation();
	}

	Vector3f &getGlobalScale()
	{
		return globalTransform.getScale();
	}

	Quaternion &getGlobalRotation()
	{
		return globalTransform.getRotation();
	}

	virtual BoundingBox &getGlobalBoundingBox() = 0;

	virtual BoundingBox &getLocalBoundingBox() = 0;

	bool isAttachedToRoot() const
	{
		return this->attachedToRoot;
	}

	void updateParents()
	{
		this->calcAttachedToRoot();
	}

	void updateTransform()
	{
		Vector3f globalTrans = getUpdatedGlobalTranslation();
		Vector3f globalScale = getUpdatedGlobalScale();
		Quaternion globalRot = getUpdatedGlobalRotation();

		bool hasPhysics = false;

		if (!hasPhysics)
			globalTransform.setTranslation(globalTrans);
		else
		{
			// get physics origin, set physics translation etc
		}

		globalTransform.setRotation(globalRot);
		globalTransform.setScale(globalScale);

		globalMatrix = globalTransform.getMatrix();
	}

	virtual void update()
	{
		if (updateNeeded)
		{
			updateTransform();
			updateParents();
			updateGlobalBoundingBox();
			updateLocalBoundingBox();

			updateNeeded = false;
		}

		//TODO: Update controllers
	}

	// Don't set this manually. Otherwise, bad things will happen.
	void setParent(Spatial *parent)
	{
		this->parent = parent;
		setUpdateNeeded();

		if (parent == 0)
			updateParents();
	}

	Spatial *getParent() const
	{
		return parent;
	}

	virtual void setUpdateNeeded()
	{
		updateNeeded = true;
	}

	Vector3f &getLocalTranslation()
	{
		return localTranslation;
	}

	void setLocalTranslation(Vector3f vec)
	{
		localTranslation.set(vec);
		setUpdateNeeded();
	}

	Vector3f &getLocalScale()
	{
		return localScale;
	}

	void setLocalScale(Vector3f vec)
	{
		localScale.set(vec);
		setUpdateNeeded();
	}

	Quaternion &getLocalRotation()
	{
		return localRotation;
	}

	void setLocalRotation(Quaternion rot)
	{
		localRotation.set(rot);
		setUpdateNeeded();
	}
protected:
	void calcAttachedToRoot()
	{
		const char *ROOT_NAME = "root";
		if (strcmp(this->name.c_str(), ROOT_NAME) == 0)
		{
			attachedToRoot = true;
			return;
		}
		if (parent == 0)
		{
			attachedToRoot = false;
			return;
		}
		else
		{
			Spatial &par = *parent;
			
			while (strcmp(par.getName().c_str(), ROOT_NAME) != 0)
			{
				Spatial *ppar = par.getParent();
				if (ppar != 0)
					par = *ppar;
				else
				{
					attachedToRoot = false;
					return;
				}
			}
		}
		attachedToRoot = true;
	}

};

#endif