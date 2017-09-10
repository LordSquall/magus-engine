#include "graphic2d.h"

namespace MagusEngine
{
	Graphic2D::Graphic2D()
	{
		_drawable = 0;
		_renderDataHandle = 0;
	}

	/* Visitable Functions*/
	void Graphic2D::Accept(Visitor* visitor)
	{
		visitor->Visit(this);
	}

	/* Component Functions */
	void Graphic2D::Initialise(){}

	void Graphic2D::Update(){}

	void Graphic2D::Draw(){}

	/* Getters */
	Drawable* Graphic2D::GetDrawable() { return _drawable; }
	unsigned int Graphic2D::GetRenderDataHandle() { return _renderDataHandle; }

	/* Setters */
	void Graphic2D::SetDrawable(Drawable* drawable) { _drawable = drawable; }
	void Graphic2D::SetRenderDataHandle(unsigned int handle) { _renderDataHandle = handle; }
}