#version 330 core

/* Attributes */

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec4 aUVExtrude;

/* Varying */
out vec4 v_Color;
out vec2 v_UV;

/* Uniforms */

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

#define extrude vec2(aUVExtrude.x, aUVExtrude.y)
#define uv 		vec2(aUVExtrude.z, aUVExtrude.w)

void main()
{	
	/* Pass varying parameters */
	v_Color = aColor;
	v_UV = aUVExtrude.zw;
	
	gl_Position = vec4(vec2(aPos.x, aPos.y) + (extrude * 5.0f), 0.0f, 1.0f) * modelMatrix * projectionMatrix;
	//gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f) * modelMatrix * projectionMatrix;

}