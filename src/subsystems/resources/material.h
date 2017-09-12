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
		Material(int id, const char* name, int colorid, int textureid);

		/* Getters */
		char*		GetName();
		int			GetId();
		Color*		GetColor();
		int			GetColorId();
		Texture*	GetTexture();
		int			GetTextureId();

		
		/* Setters */
		void SetColor(Color* color);
		void SetTexture(Texture* texture);

	private:
		int	 _id;
		char _name[50];
		int	_colorid;
		int	_textureid;

		Color* _color;
		Texture* _texture;
	};
}

#endif