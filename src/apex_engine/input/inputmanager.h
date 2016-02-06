#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "input_enums.h"

#include <vector>
using std::vector;

class InputManager
{
private:
	static vector<int> keysdown;
public:
	InputManager() {}

	static void keyDown(int key);

	static void keyUp(int key);
};

#endif