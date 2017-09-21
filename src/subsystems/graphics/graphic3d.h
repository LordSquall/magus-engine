#ifndef _GRAPHIC_3D_H_
#define _GRAPHIC_3D_H_

/* System Includes */

/* Local Project Includes */
#include "../scenemanagement/component.h"
#include "../scenemanagement/visitor.h"
#include "../scenemanagement/visitable.h"
#include "drawable.h"
#include "../resources/material.h"

namespace MagusEngine
{
	class Graphic3D : public Component
	{
	public:
		Graphic3D();

		/* Visitable Functions*/
		void Accept(Visitor* visitor);

		/* Component Functions */
		void Initialise();
		void Update();
		void Draw();

		/* Getters */
		Drawable* GetDrawable();
		VBO_Structure* GetDataHandle();

		/* Setters */
		void SetDrawable(Drawable* drawable);

	public:
		bool updateRequired;

	private:
		Drawable* _drawable;

		VBO_Structure _rendererDataHandle;

	};
}

#endif