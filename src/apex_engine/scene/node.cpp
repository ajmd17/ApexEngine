#include "node.h"

Node::~Node()
{
	Spatial::~Spatial();
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i] != NULL)
			delete children[i];
	}
}