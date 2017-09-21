#include "camera.h"

namespace MagusEngine
{
	Camera::Camera() { }

	void Camera::Initialise(Vector3f position, Vector3f lookAt)
	{
		_position = position;
		_lookAt = lookAt;
		
		_viewMatrix.BuildIdentity();
		//_viewMatrix.BuildLookAt(_position, _lookAt, Vector3f(0.0, 1.0, 0.0));
		//_viewMatrix.BuildTranslation(&_position);
	}

	Vector3f* Camera::GetLookAt()
	{
		return &_lookAt;
	}

	Vector3f* Camera::GetPosition()
	{
		return &_position;
	}

	Matrix4f* Camera::GetViewMatrix() { return &_viewMatrix; }
}