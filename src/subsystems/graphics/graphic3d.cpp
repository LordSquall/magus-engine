#include "graphic3d.h"

namespace MagusEngine
{
	Graphic3D::Graphic3D()
	{
		_drawable = 0;
		_rendererDataHandle = VBO_Structure();

		updateRequired = false;
	}

	/* Visitable Functions*/
	void Graphic3D::Accept(Visitor* visitor)
	{
		visitor->PreVisit(this);

		_drawable->PreDraw(visitor);

		visitor->Visit(this);

		_drawable->Accept(visitor);

		visitor->PostVisit(this);

		_drawable->PostDraw(visitor);
	}

	/* Component Functions */
	void Graphic3D::Initialise() {}

	void Graphic3D::Update() {}

	void Graphic3D::Draw() {}

	/* Getters */
	Drawable* Graphic3D::GetDrawable() { return _drawable; }
	VBO_Structure* Graphic3D::GetDataHandle() { return &_rendererDataHandle; }

	/* Setters */
	void Graphic3D::SetDrawable(Drawable* drawable) { _drawable = drawable; }
}