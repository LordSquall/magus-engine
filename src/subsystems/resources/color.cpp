#include "color.h"

namespace MagusEngine
{
	Color::Color(const char* name, float r, float g, float b, float a)
	{
		strcpy(_name, name);

		_r = r;
		_g = g;
		_b = b;
		_a = a;
	}

	/* Getters */
	char* Color::GetName() { return _name; }
	float Color::GetR(){ return _r; }
	float Color::GetG(){ return _g; }
	float Color::GetB(){ return _b; }
	float Color::GetA(){ return _a; }
		
	/* Setters */
	void Color::SetR(float r){ _r = r;}
	void Color::SetG(float g){ _g = g;}
	void Color::SetB(float b){ _b = b;}
	void Color::SetA(float a){ _a = a;}

}