#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include "../../scene/components/controller.h"

#include <memory>
using std::shared_ptr;

#include "skeleton.h"

namespace apex
{
	class AnimationController : public Controller
	{
	public:
		AnimationController(shared_ptr<Skeleton> skeleton) 
		{ 
			//TODO: constructor
		}

		void init()
		{
		}

		void update(const float dt) 
		{
		}

		void removed()
		{
		}
	};
}

#endif