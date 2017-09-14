#include "graphic2d.h"

namespace MagusEngine
{
	Graphic2D::Graphic2D()
	{
		_drawable = 0;
		_hwRenderDataHandle = VBO_Structure();
		_swRenderDataHandle = VBO_Structure();
	}

	/* Visitable Functions*/
	void Graphic2D::Accept(Visitor* visitor)
	{
		visitor->PreVisit(this);

		_drawable->PreDraw(visitor);

		visitor->Visit(this);

		_drawable->Accept(visitor);

		visitor->PostVisit(this);

		_drawable->PostDraw(visitor);
	}

	/* Component Functions */
	void Graphic2D::Initialise(){}

	void Graphic2D::Update(){}

	void Graphic2D::Draw(){}

	/* Getters */
	Drawable* Graphic2D::GetDrawable() { return _drawable; }
	VBO_Structure* Graphic2D::GetHWRenderDataHandle() { return &_hwRenderDataHandle; }
	VBO_Structure* Graphic2D::GetSWRenderDataHandle() { return &_swRenderDataHandle; }

	/* Setters */
	void Graphic2D::SetDrawable(Drawable* drawable) { _drawable = drawable; }
}