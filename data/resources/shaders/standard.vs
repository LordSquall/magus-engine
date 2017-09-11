#version 330 core

layout (location = 0) in vec2 aPos;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main()
{
	// Calculate the position of the vertex against the world, view, and projection matrices.
	//gl_Position = worldMatrix * vec4(aPos.x, aPos.y, 0.0f, 1.0f);
	//gl_Position = viewMatrix * gl_Position;
	//gl_Position = projectionMatrix * gl_Position;
	
	gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f) * modelMatrix * projectionMatrix;
}