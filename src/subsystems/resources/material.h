#ifndef _MATERIAL_H_
#define _MATERIAL_H_

/* System Includes */
#include <string>

/* Local Project Include */
#include "color.h"
#include "texture.h"

namespace MagusEngine
{
	class Material
	{
	public:
		Material(const char* name);

		/* Getters */
		char*		GetName();
		Color*		GetColor();
		Texture*	GetTexture();

		
		/* Setters */
		void SetColor(Color* color);
		void SetTexture(Texture* texture);

	private:
		char _name[50];
		int	_colorid;
		int	_textureid;

		Color* _color;
		Texture* _texture;
	};
}

#endif