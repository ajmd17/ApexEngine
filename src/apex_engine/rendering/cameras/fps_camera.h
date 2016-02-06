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
	public:
		FPSCamera(InputManager *inputMgr, float fov, float n, float f);

		void updateCameraLogic();
	};
}

#endif