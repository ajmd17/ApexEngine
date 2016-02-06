#ifndef GAME_H
#define GAME_H

// Abstract game class. This is essentially your application
// Author: Andrew MacDonald

#include "../scene/scene.h"
#include "../rendering/rendermanager.h"
#include "../rendering/camera.h"
#include "../assets/assetmanager.h"
#include "../input/inputmanager.h"

namespace apex
{
	class Game
	{
	private:
	protected:
		Scene *scene;

		RenderManager *renderMgr;
		AssetManager *assetMgr;
		InputManager *inputMgr;

		Camera *camera;
	public:
		Game()
		{
			scene = new Scene();

			renderMgr = new RenderManager();
			assetMgr = new AssetManager();
			inputMgr = new InputManager();
		}

		~Game()
		{
			delete inputMgr;
			delete assetMgr;
			delete scene;
			delete renderMgr;
		}

		void update()
		{
			if (this->camera != NULL)
			{
				this->camera->update();
			}

			this->scene->getRootNode()->update(this->renderMgr);
			this->logic();
		}

		void render()
		{
			if (this->renderMgr != NULL)
			{
				this->renderMgr->getEngine()->viewport(0, 0, this->camera->getWidth(), this->camera->getHeight());
				this->renderMgr->getEngine()->clear(true, true, false);
				this->renderMgr->render(*camera);
			}
			else
				throw std::runtime_error("RenderManager should not be null");
		}

		virtual void init() = 0;

		virtual void logic() = 0;

		virtual void exit() = 0;

		Scene *getScene()
		{
			return scene;
		}

		AssetManager *getAssetManager()
		{
			return assetMgr;
		}

		RenderManager *getRenderManager()
		{
			return renderMgr;
		}

		InputManager *getInputManager()
		{
			return inputMgr;
		}
	};
}
#endif