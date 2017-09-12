#include "material.h"

namespace MagusEngine
{
	Material::Material(int id, const char* name, int colorid, int textureid)
	{
		_id = id;

		strcpy_s(_name, name);

		_colorid = colorid;
		_textureid = textureid;
	}

	/* Getters */
	char*		Material::GetName() { return _name; }
	int			Material::GetId() { return _id; }
	int			Material::GetColorId() { return _colorid; }
	Color*		Material::GetColor() { return _color; }
	int			Material::GetTextureId() { return _textureid; }
	Texture*	Material::GetTexture() { return _texture; }
		
	/* Setters */
	void Material::SetColor(Color* color) { _color = color; }
	void Material::SetTexture(Texture* texture) { _texture = texture; }

}