#ifndef _GRAPHIC_2D_H_
#define _GRAPHIC_2D_H_

/* System Includes */

/* Local Project Include */
#include "../scenemanagement/component.h"
#include "../scenemanagement/visitor.h"
#include "../scenemanagement/visitable.h"
#include "drawable.h"

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
		unsigned int GetRenderDataHandle();

		/* Setters */
		void SetDrawable(Drawable* drawable);
		void SetRenderDataHandle(unsigned int handle);

	private:
		Drawable* _drawable;

		unsigned int _renderDataHandle;

	};
}

#endif