#include "node.h"
#include <iostream>
Node::~Node()
{
	std::cout << "deleted node named " << name << "\n";

	Spatial::~Spatial();
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i] != NULL)
			delete children[i];
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