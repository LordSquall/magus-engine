#version 330 core

/* Attributes */

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

/* Varying */
out vec2  v_UV;

/* Uniforms */

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main()
{	
	/* Pass varying parameters */
	v_UV = aUV;
	
	gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f) * modelMatrix * projectionMatrix;
}