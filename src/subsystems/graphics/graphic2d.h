#ifndef _GRAPHIC_2D_H_
#define _GRAPHIC_2D_H_

/* System Includes */

/* Local Project Include */
#include "../scenemanagement/component.h"
#include "../scenemanagement/visitor.h"
#include "../scenemanagement/visitable.h"
#include "drawable.h"
#include "../resources/material.h"

namespace MagusEngine
{
	class Graphic2D : public Component
	{
	public:
		Graphic2D();

		/* Visitable Functions*/
		void Accept(Visitor* visitor);

		/* Component Functions */
		void Initialise();
		void Update();
		void Draw();

		/* Getters */
		Drawable* GetDrawable();
		VBO_Structure* GetFillDataHandle();
		VBO_Structure* GetStrokeDataHandle();

		/* Setters */
		void SetDrawable(Drawable* drawable);

	public:
		bool updateRequired;
	
	private:
		Drawable* _drawable;

		VBO_Structure _fillRendererDataHandle;
		VBO_Structure _strokeRendererDataHandle;

	};
}

#endif