#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "animationtrack.h"
#include "keyframe.h"

namespace apex
{
	class Animation
	{
	private:
		Keyframe tempFrame0, tempFrame1;
	protected:
		string name;
		vector<AnimationTrack> tracks;
	public:
		Animation(string name)
		{
			this->name = name;
		}

		string getName() { return this->name; }

		AnimationTrack &getTrack(int i)
		{
			return tracks.at(i);
		}

		void addTrack(AnimationTrack anim)
		{
			tracks.push_back(anim);
		}

		float getTrackLength()
		{
			return tracks[tracks.size() - 1].getTrackLength();
		}

		void apply(float time)
		{
			for (size_t i = 0; i < tracks.size(); i++)
			{
				AnimationTrack &track = tracks[i];

				track.getBone()->clearPose();
				track.getBone()->applyPose(track.getPoseAt(time, tempFrame0));
			}
		}

		void applyBlend(float time, const Animation &toBlendTo, float blendAmt)
		{
			for (size_t i = 0; i < tracks.size(); i++)
			{
				AnimationTrack &track = tracks[i];

				if (blendAmt <= 0.001f)
					track.getBone()->clearPose();

				track.getBone()->applyPose(track.getBone()->getCurrentPose().blend(track.getPoseAt(time, tempFrame0), 
											MathUtil::clamp(blendAmt, 0.0f, 1.0f), tempFrame1));
			}
		}
	};
}

#endif