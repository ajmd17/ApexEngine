#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "input_enums.h"

#include "../event.h"

#include <functional>
#include <vector>
using std::vector;

namespace apex
{
	class KeyboardEvent : public IEvent
	{
	private:
		std::function<void()> evt;
		int key;
		bool keyUp;
	public:
		KeyboardEvent(int key, std::function<void()> evt, bool keyUp)
		{
			this->key = key;
			this->evt = evt;
			this->keyUp = keyUp;
		}

		int getKey() { return key; }

		bool isKeyUpEvent() { return keyUp; }

		void trigger()
		{
			evt();
		}
	};

	class MouseEvent : public IEvent
	{
	private:
		std::function<void()> evt;
		int btn;
		bool btnUp;
	public:
		MouseEvent(int btn, std::function<void()> evt, bool btnUp)
		{
			this->btn = btn;
			this->evt = evt;
			this->btnUp = btnUp;
		}

		int getButton() { return btn; }

		bool isReleaseEvent() { return btnUp; }

		void trigger()
		{
			evt();
		}
	};

	class InputManager
	{
	private:
		vector<int> keysdown;
		vector<int> btnsdown;

		vector<KeyboardEvent> keyEvents;
		vector<MouseEvent> mouseEvents;

		int width, height, mouseX, mouseY, windowX, windowY;
	public:
		InputManager() { width = 0; height = 0; }

		int getMouseX() { return this->mouseX; }

		int getMouseY() { return this->mouseY; }

		void setMousePos(int x, int y);

		/** Not meant to be set by user, only by engine! */
		void _setMousePos(int x, int y) { this->mouseX = x; this->mouseY = y; }

		int getWindowX() { return this->windowX; }

		int getWindowY() { return this->windowY; }

		/** Not meant to be set by user, only by engine! */
		void _setWindowPos(int x, int y) { this->windowX = x; this->windowY = y; }

		void setWidth(int w) { this->width = w; }

		void setHeight(int h) { this->height = h; }

		const int getWidth() { return width; }

		const int getHeight() { return height; }

		void addKeyboardEvent(KeyboardEvent kbe) { keyEvents.push_back(kbe); }

		void keyDown(int key);

		void keyUp(int key);

		bool isKeyDown(int key);

		bool isKeyUp(int key);

		void addMouseEvent(MouseEvent kbe) { mouseEvents.push_back(kbe); }

		void mouseButtonDown(int btn);

		void mouseButtonReleased(int btn);

		bool isMouseButtonDown(int btn);

		bool isMouseButtonReleased(int btn);
	};
}
#endif
