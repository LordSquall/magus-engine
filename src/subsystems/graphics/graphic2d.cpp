#include "graphic2d.h"

namespace MagusEngine
{
	Graphic2D::Graphic2D()
	{
		_drawable = 0;
		_fillRendererDataHandle = VBO_Structure();
		_strokeRendererDataHandle = VBO_Structure();

		updateRequired = false;
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

	void Graphic2D::Update()
	{
		
	}

	void Graphic2D::Draw(){}

	/* Getters */
	Drawable* Graphic2D::GetDrawable() { return _drawable; }
	VBO_Structure* Graphic2D::GetFillDataHandle() { return &_fillRendererDataHandle; }
	VBO_Structure* Graphic2D::GetStrokeDataHandle() { return &_strokeRendererDataHandle; }

	/* Setters */
	void Graphic2D::SetDrawable(Drawable* drawable) { _drawable = drawable; }
}