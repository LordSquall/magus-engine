#ifndef _MATERIAL_H_
#define _MATERIAL_H_

/* System Includes */
#include <string.h>

/* Local Project Include */
#include "color.h"
#include "texture.h"

namespace MagusEngine
{
	class Material
	{
	public:

		Material();
		Material(const char* name);
		Material(Material* other);

		/* Getters */
		char*		GetName();
		Color*		GetColor1();
		Color*		GetColor2();
		Texture*	GetTexture();
		bool		GetEnabledFill();
		bool		GetEnabledStroke();

		
		/* Setters */
		void SetColor1(Color* color);
		void SetColor2(Color* color);
		void SetTexture(Texture* texture);
		void SetEnabledFill(bool fill);
		void SetEnabledStroke(bool fill);

	private:
		char _name[50];
		int	_colorid;
		int	_textureid;

		Color* _color1;
		Color* _color2;
		Texture* _texture;
		bool _enableFill;
		bool _enableStroke;
	};
}

#endif