#include "material.h"

namespace MagusEngine
{
	Material::Material(int id, const char* name, int colorid)
	{
		_id = id;

		strcpy_s(_name, name);

		_colorid = colorid;
	}

	/* Getters */
	char* Material::GetName() { return _name; }
	int   Material::GetId() { return _id; }
	int	  Material::GetColorId() { return _colorid; }
	Color* Material::GetColor() { return _color; }
		
	/* Setters */
	void Material::SetColor(Color* color) { _color = color; }

}