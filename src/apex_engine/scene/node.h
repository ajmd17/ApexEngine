#ifndef NODE_H
#define NODE_H

// A spatial that can have other spatials attached to it.
// A node cannot be rendered.
// Author: Andrew MacDonald

#include "spatial.h"

#include <vector>
using std::vector;

#include <algorithm>

#include "../util/strutil.h"
#include "../util/logutil.h"

#include <memory>
using std::shared_ptr;

namespace apex
{
	class Node : public Spatial
	{
	private:
		static int node_count;

		BoundingBox localBoundingBox, globalBoundingBox;
		bool localBoundingBoxCreated, globalBoundingBoxCreated;

		void updateGlobalBoundingBox()
		{
			globalBoundingBox.clear();
			for (size_t i = 0; i < children.size(); i++)
				globalBoundingBox.extend(children[i]->getGlobalBoundingBox());
		}

		void updateLocalBoundingBox()
		{
			localBoundingBox.clear();
			for (size_t i = 0; i < children.size(); i++)
				localBoundingBox.extend(children[i]->getLocalBoundingBox());
		}
	public:
		Node();

		Node(string name);

		~Node();

		vector<shared_ptr<Spatial>> children;

		void update(RenderManager *renderMgr)
		{
			Spatial::update(renderMgr);

			for (size_t i = 0; i < children.size(); i++)
			{
				children[i]->update(renderMgr);
			}
		}

		void setNeedsTransformUpdate()
		{
			Spatial::setNeedsTransformUpdate();

			for (size_t i = 0; i < children.size(); i++)
			{
				children[i]->setNeedsTransformUpdate();
			}
		}

		void setNeedsParentUpdate()
		{
			Spatial::setNeedsParentUpdate();

			for (size_t i = 0; i < children.size(); i++)
			{
				children[i]->setNeedsParentUpdate();
			}
		}

		BoundingBox &getGlobalBoundingBox();

		BoundingBox &getLocalBoundingBox();

		unsigned int size() const
		{
			return children.size();
		}

		template <class SpatialType>
		typename std::enable_if<std::is_base_of<Spatial, SpatialType>::value, shared_ptr<SpatialType>>::type
			getAt(size_t index)
		{
			if (children.size() > index)
			{
				return std::dynamic_pointer_cast<SpatialType>(children[index]);
			}
			else
			{
				throw std::out_of_range("Out of range.");
			}
			return 0;
		}

		template <class SpatialType>
		typename std::enable_if<std::is_base_of<Spatial, SpatialType>::value, shared_ptr<SpatialType>>::type
			getByName(const char *name)
		{
			for (size_t i = 0; i < children.size(); i++)
			{
				shared_ptr<Spatial> child_at = children[i];
				if (child_at != 0)
				{
					if (strcmp(child_at->getName().c_str(), name) == 0)
						return std::dynamic_pointer_cast<SpatialType>(child_at);
				}
				else
					// The object is null. Probably deleted before being removed from the node.
					// Erase from the list.
					children.erase(children.begin() + i);
			}
			return 0;
		}

		shared_ptr<Spatial> getByName(const char *name)
		{
			return getByName<Spatial>(name);
		}

		bool contains(shared_ptr<Spatial> spatial)
		{
			for (size_t i = 0; i < children.size(); i++)
			{
				if (children[i] == spatial)
					return true;
			}
			return false;
		}

		void add(shared_ptr<Spatial> spatial)
		{
			if (!contains(spatial))
			{
				children.push_back(spatial);
				spatial->setParent(this);
			}
		}

		void remove(shared_ptr<Spatial> spatial)
		{
			for (size_t i = 0; i < children.size(); i++)
			{
				if (children[i] == spatial)
				{
					spatial->setParent(0);
					children.erase(children.begin() + i);
				}
			}
		}

		void removeSoft(shared_ptr<Spatial> spatial)
		{
			for (size_t i = 0; i < children.size(); i++)
			{
				if (children[i] == spatial)
				{
					children.erase(children.begin() + i);
				}
			}
		}

		void removeAt(int i)
		{
			if (i < size())
			{
				children[i]->setParent(0);
				children.erase(children.begin() + i);
			}
			else
				throw std::out_of_range("Out of range.");
		}
	};
}
#endif