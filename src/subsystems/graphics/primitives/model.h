#ifndef _MODEL_H_
#define _MODEL_H_

/* System Includes */

/* Local Project Includes */
#include "../drawable.h"
#include "../../resources/mesh.h"

namespace MagusEngine
{
	/*
	Name:  Model
	Type: Class
	Purpose: Represents a 3D Model
	*/
	class Model : public Drawable
	{
	public:
		/*
		Default contstructor
		*/
		Model();

		Model(Mesh* mesh);

		/* Drawable Functions */
		void Build(Vertex* vbuffer, unsigned int* ibuffer, VBO_Structure* fillData, VBO_Structure* strokeData);
		void PreDraw(Visitor* visitor);
		void PostDraw(Visitor* visitor);

		/* Visitable Functions */
		void Accept(Visitor* visitor);

		/* Getters */
		Mesh* GetMesh();

		/* Setters */
		void SetMesh(Mesh* mesh);

	private:
		Mesh* _mesh;
	};
}

#endif
