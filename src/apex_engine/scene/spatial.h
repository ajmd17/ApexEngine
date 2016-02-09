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

namespace apex
{
	class RenderManager;

	class Spatial : public ILoadableObject // A spatial is loadable as a resource
	{
	protected:
		string name;

		Vector3f localTranslation;
		Vector3f localScale;
		Quaternion localRotation;

		Transform globalTransform;
		Matrix4f globalMatrix;

		static const unsigned char	updateParentFlag = 0x01,
			updateTransformFlag = 0x02,
			updateLocalBoundingBoxFlag = 0x04,
			updateGlobalBoundingBoxFlag = 0x08;

		unsigned char updateFlags;
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

			this->updateFlags = 0;

			localTranslation.set(0, 0, 0);
			localScale.set(1, 1, 1);
			localRotation.setToIdentity();
		}

		Spatial(string name)
		{
			this->name = name;
			this->parent = 0;
			this->updateNeeded = false;
			this->attachedToRoot = false;

			this->updateFlags = 0;

			localTranslation.set(0, 0, 0);
			localScale.set(1, 1, 1);
			localRotation.setToIdentity();
		}

		virtual ~Spatial();

		void setName(string name)
		{
			this->name = name;
		}

		string getName() const
		{
			return name;
		}

		void resetLocalTransforms()
		{
			localTranslation.set(0, 0, 0);
			localScale.set(1, 1, 1);
			localRotation.setToIdentity();
			this->setNeedsTransformUpdate();
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
			out.multiply(localRotation);
			if (parent != 0)
			{
				parent->updateGlobalRotation(out);
			}
		}

		Quaternion getUpdatedGlobalRotation()
		{
			tmpGlobalRot.setToIdentity();
			updateGlobalRotation(tmpGlobalRot);
			return tmpGlobalRot;
		}

		void updateGlobalScale(Vector3f &out)
		{
			out.multiply(localScale);
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
			out.add(localTranslation);
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

		bool isAttachedToRoot()
		{
			return this->attachedToRoot;
		}

		virtual void updateParents()
		{
			this->calcAttachedToRoot();
		}

		void updateTransform();

		virtual void update(RenderManager *renderMgr, const float dt);

		// Don't set this manually. Otherwise, bad things will happen.
		void setParent(Spatial *parent)
		{
			this->parent = parent;

			this->setNeedsParentUpdate();
			this->setNeedsTransformUpdate(); // will need to update global transforms

			if (parent == 0)
				updateParents();
		}

		Spatial *getParent() const
		{
			return parent;
		}

		virtual void setNeedsTransformUpdate()
		{
			this->updateFlags |= updateTransformFlag;
		}

		void setNeedsGlobalBoundingBoxUpdate()
		{
			this->updateFlags |= updateGlobalBoundingBoxFlag;
		}

		void setNeedsLocalBoundingBoxUpdate()
		{
			this->updateFlags |= updateLocalBoundingBoxFlag;
		}

		virtual void setNeedsParentUpdate()
		{
			this->updateFlags |= updateParentFlag;
		}

		Vector3f &getLocalTranslation()
		{
			return localTranslation;
		}

		void setLocalTranslation(Vector3f vec)
		{
			localTranslation.set(vec);
			this->setNeedsTransformUpdate();
		}

		Vector3f &getLocalScale()
		{
			return localScale;
		}

		void setLocalScale(Vector3f vec)
		{
			localScale.set(vec);
			this->setNeedsTransformUpdate();
		}

		Quaternion &getLocalRotation()
		{
			return localRotation;
		}

		void setLocalRotation(Quaternion rot)
		{
			localRotation.set(rot);
			this->setNeedsTransformUpdate();
		}
	protected:
		void calcAttachedToRoot();

	};
}
#endif