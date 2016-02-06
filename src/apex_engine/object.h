#ifndef OBJECT_H
#define OBJECT_H

// Interface for anything that could be considered an object in the engine.
// Author: Andrew MacDonald

namespace apex
{
	class IObject
	{
	public:
		virtual ~IObject() {}
	};
}
#endif