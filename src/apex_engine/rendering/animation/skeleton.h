#ifndef SKELETON_H
#define SKELETON_H

#include <vector>
using std::vector;

#include <memory>
using std::shared_ptr;

#include <string>
using std::string;

#include "bone.h"
#include "animation.h"
#include "../../assets/loadableobject.h"

namespace apex
{
	class Skeleton : public ILoadableObject
	{
	private:
		vector<shared_ptr<Bone>> bones;
		vector<Animation> animations;
	public:
		Skeleton() {}

		void addAnimation(Animation anim)
		{
			animations.push_back(anim);
		}

		bool getAnimation(string name, Animation &outAnim)
		{
			for (size_t i = 0; i < animations.size(); i++)
			{
				if (str_eql(animations[i].getName(), name))
				{
					outAnim = animations[i];
					return true;
				}
			}

			return false;
		}

		Animation &getAnimation(int i)
		{
			return animations.at(i);
		}

		size_t getNumAnimations()
		{
			return animations.size();
		}

		void addBone(shared_ptr<Bone> bone)
		{
			bones.push_back(bone);
		}

		shared_ptr<Bone> getBone(const string &name)
		{
			for (size_t i = 0; i < bones.size(); i++)
			{
				if (str_eql(bones[i]->getName(), name))
					return bones[i];
			}

			return 0;
		}

		shared_ptr<Bone> getBone(int i)
		{
			return bones.at(i);
		}

		size_t getNumBones()
		{
			return bones.size();
		}
	};
}

#endif