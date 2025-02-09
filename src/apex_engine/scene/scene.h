#ifndef SCENE_H
#define SCENE_H

// There will be a single "Scene" class in your game.
// It will be used to manipulate the environment around the player,
// as well as add items to the scene node.
// Author: Andrew MacDonald

#include "spatial.h"
#include "node.h"

#include "../rendering/environment.h"

namespace apex
{
	class Scene
	{
	private:
		Environment *environment;
		Node *rootNode;
	public:
		Scene()
		{
			rootNode = new Node("root");
			environment = new Environment();
		}

		~Scene()
		{
			delete environment;
			delete rootNode;
		}

		Node *getRootNode() const
		{
			return rootNode;
		}

		Environment *getEnvironment() const
		{
			return environment;
		}
	};
}
#endif