#include "node.h"
#include "../util/logutil.h"

namespace apex
{
	int Node::node_count = 0;

	Node::Node() : Spatial()
	{
		this->setName("node_" + to_str(++node_count));
	}

	Node::Node(string name) : Spatial(name)
	{
	}

	Node::~Node()
	{
		engine_log << "Deleting node: " << getName() << "\n";

		int ch_size = children.size();

		for (size_t i = ch_size; i > 0; i--)
		{
			this->removeAt(i - 1);
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
		/*if (!localBoundingBoxCreated)
		{
			updateLocalBoundingBox();
			localBoundingBoxCreated = true;
		}

		if (this->updateFlags & Spatial::updateLocalBoundingBoxFlag)
		{
			updateLocalBoundingBox();
			this->updateFlags &= ~Spatial::updateLocalBoundingBoxFlag;
		}

		return localBoundingBox;*/

		return getGlobalBoundingBox();
	}
}
