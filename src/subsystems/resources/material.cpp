#include "material.h"

namespace MagusEngine
{
	Material::Material()
	{
		strcpy_s(_name, "UNKNOWN");

		_color1 = 0;
		_color2 = 0;
		_texture = 0;
	}

	Material::Material(const char* name)
	{
		strcpy_s(_name, name);

		_color1 = 0;
		_color2 = 0;
		_texture = 0;
	}


	Material::Material(Material* other)
	{
		strcpy_s(_name, other->GetName());

		_color1 = other->GetColor1();
		_color2 = other->GetColor2();
		_texture = other->GetTexture();
	}

	/* Getters */
	char*		Material::GetName() { return _name; }
	Color*		Material::GetColor1() { return _color1; }
	Color*		Material::GetColor2() { return _color2; }
	Texture*	Material::GetTexture() { return _texture; }
		
	/* Setters */
	void Material::SetColor1(Color* color) { _color1 = color; }
	void Material::SetColor2(Color* color) { _color2 = color; }
	void Material::SetTexture(Texture* texture) { _texture = texture; }

}