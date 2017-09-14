#ifndef _COLOR_H_
#define _COLOR_H_

/* System Includes */
#include <string>

/* Local Project Include */
#include "color.h"

namespace MagusEngine
{
	class Color
	{
	public:
		Color(const char* name, float r, float g, float b, float a);

		/* Getters */
		char* GetName();
		float GetR();
		float GetG();
		float GetB();
		float GetA();
		
		/* Setters */
		void SetR(float r);
		void SetG(float g);
		void SetB(float b);
		void SetA(float a);

	private:
		float _r;
		float _g;
		float _b;
		float _a;

		char _name[25];
	};
}

#endif