#ifndef _TEXT_H_
#define _TEXT_H_

/* System Includes */
#include <string>

/* Local Project Includes */
#include "../drawable.h"
#include "../../resources/font.h"

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
		void Build(Vertex* vbuffer, unsigned int* ibuffer, VBO_Structure* fillData, VBO_Structure* strokeData);
		void PreDraw(Visitor* visitor);
		void PostDraw(Visitor* visitor);

		/* Visitable Functions */
		void Accept(Visitor* visitor);

		/* Getters */
		float GetX();
		float GetY();
		char* GetContent();
		Font* GetFont();

		/* Setters */
		void SetX(float x);
		void SetY(float y);
		void SetContent(const char* content);
		void SetFont(Font* font);

	private:
		float _x;
		float _y;
		char _content[255];

		Font* _font;
	};
}

#endif
