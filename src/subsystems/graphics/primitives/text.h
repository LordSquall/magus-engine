#ifndef _TEXT_H_
#define _TEXT_H_

/* System Includes */
#include <string>

/* Local Project Includes */
#include "../drawable.h"

namespace MagusEngine
{
	/*
	Name:  Text
	Type: Class
	Purpose: Represents a Text drawable
	*/
	class Text : public Drawable
	{
	public:
		/*
		Default contstructor
		*/
		Text();

		Text(float x, float y, const char* content);

		/* Drawable Functions */
		void Build(Vertex* vbuffer, int* vbufferLength, unsigned int* ibuffer, int* ibufferLength);

		/* Getters */
		float GetX();
		float GetY();
		const char* GetContent();

		/* Setters */
		void SetX(float x);
		void SetY(float y);
		void SetContent(const char* content);

	private:
		float _x;
		float _y;
		char _content[255];
	};
}

#endif
