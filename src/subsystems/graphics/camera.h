#ifndef _CAMERA_H_
#define _CAMERA_H_

/* System Includes */
#include <thread>

/* Local Project Includes */
#include "../math/matrix.h"
#include "../math/vector.h"

namespace MagusEngine
{
	class Camera 
	{
	public:
		Camera();

		void Initialise(Vector3f position, Vector3f lookAt);

		Vector3f* GetPosition();
		Vector3f* GetLookAt();
		Matrix4f* GetViewMatrix();

	private:
		Vector3f _position;
		Vector3f _lookAt;
		Matrix4f _viewMatrix;
	};
}

#endif