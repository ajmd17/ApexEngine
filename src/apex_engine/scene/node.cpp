#include "node.h"

int Node::node_count = 0;

Node::~Node()
{
	Spatial::~Spatial(); 
	
	for (size_t i = children.size(); i > 0; i--) 
	{
		delete children[i-1];
	}
}

BoundingBox &Node::getGlobalBoundingBox()
{
	if (!globalBoundingBoxCreated)
	{
		updateGlobalBoundingBox();
		globalBoundingBoxCreated = true;
	}

	if (this->updateFlags & Spatial::updateGlobalBoundingBoxFlag)
	{
		updateGlobalBoundingBox();
		this->updateFlags &= ~Spatial::updateGlobalBoundingBoxFlag;
	}

	return globalBoundingBox;
}

BoundingBox &Node::getLocalBoundingBox()
{
	if (!localBoundingBoxCreated)
	{
		updateLocalBoundingBox();
		localBoundingBoxCreated = true;
	}

	if (this->updateFlags & Spatial::updateLocalBoundingBoxFlag)
	{
		updateLocalBoundingBox();
		this->updateFlags &= ~Spatial::updateLocalBoundingBoxFlag;
	}

	return localBoundingBox;
}