#ifndef BONE_H
#define BONE_H

#include "../../math/quaternion.h"
#include "../../math/vector3f.h"
#include "../../math/matrix4f.h"
#include "../../scene/node.h"

#include "keyframe.h"

namespace apex
{
	class Bone : public Node
	{
	protected:
		Matrix4f tmpMatrix, boneMatrix, rotMatrix;
		Vector3f modelPos, axis, bindTrans, bindAxis, invBindPos, tmpMpos, globalBoneTrans;
		Quaternion modelRot, bindRot, invBindRot, poseRot, tmpRot, globalBoneRot;
	private:
		Keyframe currentPose;

		void calculateBindingTranslation(Vector3f &outv)
		{
			Bone *parentBone;
			if (parent && (parentBone = dynamic_cast<Bone*>(parent)))
			{
				outv.set(this->getBindTranslation());
				parentBone->getModelRotation().multiply(outv);
				outv.add(parentBone->getModelTranslation());
			}
			else
				outv.set(this->getBindTranslation());
		}
	public:
		Bone(string name) : Node(name)
		{
		}

		Keyframe &getCurrentPose() { return currentPose; }

		void setBindRotation(Quaternion bindRot) { this->bindRot.set(bindRot); }

		Quaternion getBindRotation() { return bindRot; }

		Quaternion getPoseRotation() { return poseRot; }

		Quaternion getInverseBindRotation() { return invBindRot; }

		Quaternion getModelRotation() { return modelRot; }

		Quaternion calculateBindingRotation()
		{
			Bone *parentBone;
			if (parent && (parentBone = dynamic_cast<Bone*>(parent)))
			{
				this->modelRot.set(parentBone->modelRot);
				this->modelRot.multiply(bindRot);
				
			}
			else
				this->modelRot.set(bindRot);

			for (size_t i = 0; i < children.size(); i++)
			{
				shared_ptr<Bone> childBone = std::dynamic_pointer_cast<Bone>(children[i]);
				if (childBone)
				{
					childBone->calculateBindingRotation();
				}
			}

			return modelRot;
		}

		void setBindTranslation(Vector3f bindTrans) { this->bindTrans.set(bindTrans); }

		Vector3f getBindTranslation() { return bindTrans; }

		Vector3f getInverseBindTranslation() { return invBindPos; }

		Vector3f getModelTranslation() { return modelPos; }

		Vector3f calculateBindingTranslation()
		{
			Vector3f outv;
			calculateBindingTranslation(outv);
			modelPos.set(outv);
			for (size_t i = 0; i < children.size(); i++)
			{
				shared_ptr<Bone> childBone = std::dynamic_pointer_cast<Bone>(children[i]);
				if (childBone)
				{
					childBone->calculateBindingTranslation();
				}
			}
			
			return modelPos;
		}

		void setToBindingPose()
		{
			this->localRotation.setToIdentity();
			this->localTranslation.set(this->bindTrans);
			this->poseRot.set(bindRot);
			this->updateTransform();
		}

		void storeBindingPose()
		{
			this->invBindPos.set(modelPos); this->invBindPos.multiply(-1.0f);
			this->invBindRot.set(modelRot); this->invBindRot.invert();

			this->localRotation.setToIdentity();
			this->localTranslation.set(0.0f);
		}

		void applyPose(Keyframe &pose)
		{
			this->currentPose = pose;
			this->setLocalTranslation(pose.getTranslation());
			poseRot.set(pose.getRotation());

			this->updateTransform();
		}

		void clearPose()
		{
			poseRot.setToIdentity();
			this->updateTransform();
		}

		void update(RenderManager *renderMgr, const float dt)
		{
			// do nothing
		}

		Matrix4f getBoneMatrix()
		{
			return boneMatrix;
		}

		virtual Vector3f &getGlobalTranslation()
		{
			return globalBoneTrans;
		}

		virtual Quaternion &getGlobalRotation()
		{
			return globalBoneRot;
		}

		void updateTransform()
		{
			tmpMpos.set(modelPos);
			tmpMpos.multiply(-1.0f);
			MatrixUtil::setToTranslation(rotMatrix, tmpMpos);

			tmpRot.set(modelRot);
			tmpRot.multiply(poseRot);
			tmpRot.multiply(localRotation);
			tmpRot.multiply(invBindRot);

			MatrixUtil::setToRotation(tmpMatrix, tmpRot);
			rotMatrix.multiply(tmpMatrix);

			tmpMpos.multiply(-1.0f);
			MatrixUtil::setToTranslation(tmpMatrix, tmpMpos);
			rotMatrix.multiply(tmpMatrix);
			MatrixUtil::setToTranslation(tmpMatrix, localTranslation);
			rotMatrix.multiply(tmpMatrix);
			boneMatrix.set(rotMatrix);

			Bone *parentBone;
			if (parent && dynamic_cast<Bone*>(parent))
			{
				boneMatrix.multiply(parentBone->boneMatrix);
			}
			
			for (size_t i = 0; i < children.size(); i++)
			{
				children[i]->updateTransform();
			}
		}
	};
}

#endif