#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "input_enums.h"

#include <vector>
using std::vector;

namespace apex
{
	class InputManager
	{
	private:
		vector<int> keysdown;

		int width, height;
	public:
		InputManager() {}

		void setWidth(int w) { this->width = w; }

		void setHeight(int h) { this->height = h; }

		int getWidth() { return width; }

		int getHeight() { return height; }

		void keyDown(int key);

		void keyUp(int key);

		bool isKeyDown(int key);
	};
}
#endif