#ifndef ANIMATION_TRACK_H
#define ANIMATION_TRACK_H

#include <vector>
using std::vector;

#include <memory>
using std::shared_ptr;

#include "../../math/vector3f.h"
#include "../../math/quaternion.h"

#include "keyframe.h"

namespace apex
{
	class Bone;

	class AnimationTrack
	{
	private:
		shared_ptr<Bone> bone;
		vector<Keyframe> frames;

		Vector3f tempVec;
		Quaternion tempRot;
		Keyframe tempFrame;
	public:
		AnimationTrack(shared_ptr<Bone> bone)
		{
			this->bone = bone;
		}

		void setBone(shared_ptr<Bone> bone)
		{
			this->bone = bone;
		}

		shared_ptr<Bone> getBone()
		{
			return this->bone;
		}

		const float getTrackLength()
		{
			return frames[frames.size() - 1].getTime();
		}

		void addFrame(Keyframe frame)
		{
			frames.push_back(frame);
		}

		Keyframe &getPoseAt(float time, Keyframe &outFrame)
		{
			int first = 0, second = -1;

			Keyframe currentFrame, nextFrame;
			
			int n = frames.size() - 1;
			for (int i = 0; i < n; i++)
			{
				if (time >= frames[i].getTime() && time <= frames[i + 1].getTime())
				{
					first = i;
					second = i + 1;
				}
			}
			currentFrame = frames[first];

			tempVec.set(currentFrame.getTranslation());
			tempRot.set(currentFrame.getRotation());

			if (second > first)
			{
				nextFrame = frames[second];

				float fraction = (time - currentFrame.getTime()) / (nextFrame.getTime() - currentFrame.getTime());
				tempVec.lerp(nextFrame.getTranslation(), fraction);
				Quaternion nextRot(nextFrame.getRotation());
				tempRot.slerp(nextRot, fraction);
			}

			outFrame.setTime(time);
			outFrame.setTranslation(tempVec);
			outFrame.setRotation(tempRot);

			return outFrame;
		}
	};
}

#endif