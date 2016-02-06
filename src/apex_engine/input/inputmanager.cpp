#include "inputmanager.h"

#include "../util/logutil.h"
#include "../rendering/rendermanager.h"

namespace apex
{
	void InputManager::setMousePos(int x, int y)
	{
		RenderManager::getEngine()->setMousePosition(x, y);
	}

	void InputManager::keyDown(int key)
	{
		for (int i = 0; i < keyEvents.size(); i++)
		{
			if (keyEvents[i].getKey() == key && !keyEvents[i].isKeyUpEvent())
			{
				keyEvents[i].trigger();
			}
		}

		for (int i = 0; i < keysdown.size(); i++)
		{
			if (keysdown[i] == key)
				return;
		}
		keysdown.push_back(key);
	}

	void InputManager::keyUp(int key)
	{
		for (int i = 0; i < keyEvents.size(); i++)
		{
			if (keyEvents[i].getKey() == key && keyEvents[i].isKeyUpEvent())
			{
				keyEvents[i].trigger();
			}
		}

		for (int i = 0; i < keysdown.size(); i++)
		{
			if (keysdown[i] == key)
			{
				keysdown.erase(keysdown.begin() + i);
				return;
			}
		}
	}

	bool InputManager::isKeyDown(int key)
	{
		for (int i = 0; i < keysdown.size(); i++)
		{
			if (keysdown[i] == key)
			{
				return true;
			}
		}
		return false;
	}

	bool InputManager::isKeyUp(int key)
	{
		return !isKeyDown(key);
	}

	void InputManager::mouseButtonDown(int btn)
	{
		for (int i = 0; i < mouseEvents.size(); i++)
		{
			if (mouseEvents[i].getButton() == btn && !mouseEvents[i].isReleaseEvent())
			{
				mouseEvents[i].trigger();
			}
		}

		for (int i = 0; i < btnsdown.size(); i++)
		{
			if (btnsdown[i] == btn)
				return;
		}
		btnsdown.push_back(btn);
	}

	void InputManager::mouseButtonReleased(int btn)
	{
		for (int i = 0; i < mouseEvents.size(); i++)
		{
			if (mouseEvents[i].getButton() == btn && mouseEvents[i].isReleaseEvent())
			{
				mouseEvents[i].trigger();
			}
		}

		for (int i = 0; i < btnsdown.size(); i++)
		{
			if (btnsdown[i] == btn)
			{
				btnsdown.erase(btnsdown.begin() + i);
				return;
			}
		}
	}

	bool InputManager::isMouseButtonDown(int btn)
	{
		for (int i = 0; i < btnsdown.size(); i++)
		{
			if (btnsdown[i] == btn)
			{
				return true;
			}
		}
		return false;
	}

	bool InputManager::isMouseButtonReleased(int btn)
	{
		return !isMouseButtonDown(btn);
	}
}