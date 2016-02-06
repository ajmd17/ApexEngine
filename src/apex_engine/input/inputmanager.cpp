#include "inputmanager.h"

#include "../util/logutil.h"

vector<int> InputManager::keysdown;

void InputManager::keyDown(int key)
{
	engine_log << "Key down: " << key << "\n";
	for (int i = 0; i < keysdown.size(); i++)
	{
		if (keysdown[i] == key)
			return;
	}
	keysdown.push_back(key);
}

void InputManager::keyUp(int key)
{
	engine_log << "Key up: " << key << "\n";
	for (int i = 0; i < keysdown.size(); i++)
	{
		if (keysdown[i] == key)
		{
			keysdown.erase(keysdown.begin() + i);
			return;
		}
	}
}