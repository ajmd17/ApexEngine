#include "fps_camera.h"

#include "../../input/inputmanager.h"

namespace apex
{
	FPSCamera::FPSCamera(InputManager *inputMgr, float fov, float n, float f) : PerspectiveCamera(fov, 512, 512, n, f)
	{
		this->inputMgr = inputMgr;
	}

	void FPSCamera::updateCameraLogic()
	{
		// TODO
		this->width = inputMgr->getWidth();
		this->height = inputMgr->getHeight();

		if (inputMgr->isKeyDown(apex::KeyboardKey::W))
		{
			this->translation.x += direction.x * 0.1f;
			this->translation.y += direction.y * 0.1f;
			this->translation.z += direction.z * 0.1f;
		}
		else if (inputMgr->isKeyDown(apex::KeyboardKey::S))
		{
			this->translation.x -= direction.x * 0.1f;
			this->translation.y -= direction.y * 0.1f;
			this->translation.z -= direction.z * 0.1f;
		}

		if (inputMgr->isKeyDown(apex::KeyboardKey::A))
		{
			this->translation.x += sin(MathUtil::toRadians(yaw + 90.0f)) * 0.1f;
			this->translation.z -= cos(MathUtil::toRadians(yaw + 90.0f)) * 0.1f;
		}
		else if (inputMgr->isKeyDown(apex::KeyboardKey::D))
		{
			this->translation.x += sin(MathUtil::toRadians(yaw - 90.0f)) * 0.1f;
			this->translation.z -= cos(MathUtil::toRadians(yaw - 90.0f)) * 0.1f;
		}
	}
}