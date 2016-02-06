#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include "perspective_camera.h"
#include "../../math/matrix_util.h"
#include "../../math/vector3f.h"

namespace apex
{
	class InputManager;

	class FPSCamera : public PerspectiveCamera
	{
	private:
		InputManager *inputMgr;

		Vector3f dirCrossY;

		float magX, magY;

		bool mouseCaptured;

		void centerMouse();

		void mouseClickCallback();

		void altPressCallback();

		void mouseInput(int x, int y, int halfWidth, int halfHeight);

		void keyboardInput();
	public:
		FPSCamera(InputManager *inputMgr, float fov, float n, float f);

		void updateCameraLogic();
	};
}

#endif