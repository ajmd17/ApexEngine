#include "spatial.h"
#include "node.h"

Spatial::~Spatial()
{
	if (this->parent != NULL)
	{
		Node *n = static_cast<Node*>(parent);
		n->removeSoft(this);
	}
}