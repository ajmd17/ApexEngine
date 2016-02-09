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

		float magX, magY, oldMagX, oldMagY;

		Vector3f nextTranslation;

		bool mouseCaptured;

		void centerMouse();

		void mouseClickCallback();

		void altPressCallback();

		void mouseInput(const float dt, int x, int y, int halfWidth, int halfHeight);

		void keyboardInput(const float dt);
	public:
		FPSCamera(InputManager *inputMgr, float fov, float n, float f);

		void updateCameraLogic(const float dt);
	};
}

#endif
