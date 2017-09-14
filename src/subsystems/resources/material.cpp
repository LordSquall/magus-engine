#include "material.h"

namespace MagusEngine
{
	Material::Material(const char* name)
	{
		strcpy_s(_name, name);

		_color = 0;
		_texture = 0;
	}

	/* Getters */
	char*		Material::GetName() { return _name; }
	Color*		Material::GetColor() { return _color; }
	Texture*	Material::GetTexture() { return _texture; }
		
	/* Setters */
	void Material::SetColor(Color* color) { _color = color; }
	void Material::SetTexture(Texture* texture) { _texture = texture; }

}