#ifndef NODE_H
#define NODE_H

// A spatial that can have other spatials attached to it.
// A node cannot be rendered.

#include "spatial.h"

#include <vector>
using std::vector;

#include <algorithm>

class Node : public Spatial
{
private:
	BoundingBox localBoundingBox, globalBoundingBox;
	bool localBoundingBoxCreated, globalBoundingBoxCreated;

	vector<Spatial*> children;

	void updateGlobalBoundingBox()
	{
		globalBoundingBox.clear();
		for (int i = 0; i < children.size(); i++)
			globalBoundingBox.extend(children[i]->getGlobalBoundingBox());
	}

	void updateLocalBoundingBox()
	{
		localBoundingBox.clear();
		for (int i = 0; i < children.size(); i++)
			localBoundingBox.extend(children[i]->getLocalBoundingBox());
	}
public:
	Node() : Spatial() {}

	Node(char *name) : Spatial(name) {}

	void update()
	{
		Spatial::update();

		for (int i = 0; i < children.size(); i++)
		{
			children[i]->update();
		}
	}

	void setUpdateNeeded()
	{
		Spatial::setUpdateNeeded();

		for (int i = 0; i < children.size(); i++)
		{
			children[i]->setUpdateNeeded();
		}
	}

	BoundingBox getGlobalBoundingBox()
	{
		if (!globalBoundingBoxCreated)
		{
			updateGlobalBoundingBox();
			globalBoundingBoxCreated = true;
		}
		return globalBoundingBox;
	}

	BoundingBox getLocalBoundingBox()
	{
		if (!localBoundingBoxCreated)
		{
			updateLocalBoundingBox();
			localBoundingBoxCreated = true;
		}
		return localBoundingBox;
	}

	unsigned int size() const
	{
		return children.size();
	}

	template <class SpatialType>
	typename std::enable_if<std::is_base_of<Spatial, SpatialType>::value, SpatialType*>::type
	get(int index)
	{
		if (children.size() > index)
		{
			return (SpatialType*)children[index];
		}
		else
		{
			cout << "Index out of range. Size: " << children.size() << ", Index: " << index << "\n";
		}
		return 0;
	}

	Spatial *get(int index)
	{
		Spatial *res = get<Spatial> (index);
		return res;
	}

	bool contains(Spatial *spatial)
	{
		for (int i = 0; i < children.size(); i++)
		{
			if (children[i] == spatial)
				return true;
		}
		return false;
	}

	void add(Spatial *spatial)
	{
		if (!contains(spatial))
		{
			children.push_back(spatial);
			spatial->setParent(this);
		}
	}

	void remove(Spatial *spatial)
	{
		if (contains(spatial))
		{
			children.erase(std::find(children.begin(), children.end(), spatial));
			spatial->setParent(0);
		}
	}

	void removeAt(int i)
	{
		Spatial *spatial = this->get<Spatial>(i);
		this->remove(spatial);
	}
};

#endif