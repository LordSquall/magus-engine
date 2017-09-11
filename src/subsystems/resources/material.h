#ifndef _MATERIAL_H_
#define _MATERIAL_H_

/* System Includes */
#include <string>

/* Local Project Include */
#include "color.h"

namespace MagusEngine
{
	class Material
	{
	public:
		Material(int id, const char* name, int colorid);

		/* Getters */
		char*	GetName();
		int		GetId();
		Color*  GetColor();
		int		GetColorId();

		
		/* Setters */
		void SetColor(Color* color);

	private:
		int	 _id;
		char _name[50];
		int	_colorid;

		Color* _color;
	};
}

#endif