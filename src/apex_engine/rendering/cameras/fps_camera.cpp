#include "fps_camera.h"

#include "../../input/inputmanager.h"
#include "../../util/logutil.h"

#include <functional>

namespace apex
{
	void FPSCamera::centerMouse()
	{
		inputMgr->setMousePos(inputMgr->getWindowX() + width / 2,
							  inputMgr->getWindowY() + height / 2);
	}

	void FPSCamera::mouseClickCallback()
	{
		this->centerMouse();
		this->mouseCaptured = true;
	}

	void FPSCamera::altPressCallback()
	{
		this->centerMouse();
		this->mouseCaptured = !this->mouseCaptured;
	}

	FPSCamera::FPSCamera(InputManager *inputMgr, float fov, float n, float f) : PerspectiveCamera(fov, 512, 512, n, f)
	{
		this->inputMgr = inputMgr;

		// register callbacks
		MouseEvent m_e (Left, std::bind(&FPSCamera::mouseClickCallback, this), false);
		inputMgr->addMouseEvent(m_e);

		KeyboardEvent k_e(LeftAlt, std::bind(&FPSCamera::altPressCallback, this), false);
		inputMgr->addKeyboardEvent(k_e);
	}

	void FPSCamera::updateCameraLogic(const float dt)
	{
		this->width = inputMgr->getWidth();
		this->height = inputMgr->getHeight();

		this->mouseInput(dt, inputMgr->getMouseX(), inputMgr->getMouseY(), inputMgr->getWindowX() + width / 2, inputMgr->getWindowY() + height / 2);
		this->keyboardInput(dt);
	}

	void FPSCamera::mouseInput(const float dt, int x, int y, int halfWidth, int halfHeight)
	{
        const float sensitivity = 5.0f;
        const float smoothing = 15.5f; // the lower the value, the smoother it will be

		if (mouseCaptured)
		{
			magX = static_cast<float>(x) - halfWidth;
			magY = static_cast<float>(y) - halfHeight;

			magX = MathUtil::lerp(oldMagX, magX, MathUtil::clamp(smoothing*dt, 0.0f, 1.0f));
			magY = MathUtil::lerp(oldMagY, magY, MathUtil::clamp(smoothing*dt, 0.0f, 1.0f));

			oldMagX = magX; oldMagY = magY;

			dirCrossY.set(direction);
			dirCrossY.cross(Vector3f::UnitY);

			this->rotate(Vector3f::UnitY, magX*dt*sensitivity);
			this->rotate(dirCrossY, magY*dt*sensitivity);

			if (direction.y > 0.97f || direction.y < -0.97f) 
			{ 
				// negate and rerotate 
				magY *= -1.0f;
				this->rotate(dirCrossY, magY*dt*sensitivity);
			}



			inputMgr->setMousePos(halfWidth, halfHeight);
		}
	}

	void FPSCamera::keyboardInput(const float dt)
	{
        const float speed = dt*6.0f;

		if (inputMgr->isKeyDown(apex::KeyboardKey::W))
		{
			nextTranslation.x += direction.x * speed;
			nextTranslation.y += direction.y * speed;
			nextTranslation.z += direction.z * speed;
		}
		else if (inputMgr->isKeyDown(apex::KeyboardKey::S))
		{
			nextTranslation.x -= direction.x * speed;
			nextTranslation.y -= direction.y * speed;
			nextTranslation.z -= direction.z * speed;
		}

		if (inputMgr->isKeyDown(apex::KeyboardKey::A))
		{
			nextTranslation.x += sin(MathUtil::toRadians(yaw + 90.0f)) * speed;
			nextTranslation.z -= cos(MathUtil::toRadians(yaw + 90.0f)) * speed;
		}
		else if (inputMgr->isKeyDown(apex::KeyboardKey::D))
		{
			nextTranslation.x += sin(MathUtil::toRadians(yaw - 90.0f)) * speed;
			nextTranslation.z -= cos(MathUtil::toRadians(yaw - 90.0f)) * speed;
		}

		this->translation.lerp(nextTranslation, MathUtil::clamp(8.0f*dt, 0.0f, 1.0f));
	}
}
