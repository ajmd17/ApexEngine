#ifndef LOADABLEOBJECT_H
#define LOADABLEOBJECT_H

// An object that may be loaded as a resource.
// Author: Andrew MacDonald

#include "../object.h"

class ILoadableObject : public IObject
{
public:
	virtual ~ILoadableObject() {}
};

#endif