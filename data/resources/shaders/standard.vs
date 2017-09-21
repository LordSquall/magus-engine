#version 330 core

/* Attributes */

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec4 aUVExtrude;

/* Varying */
out vec3 v_FragPosition;
out vec4 v_Color;
out vec3 v_Normal;
out vec2 v_UV;

/* Uniforms */

uniform mat4 model;
uniform mat4 mvp;

#define extrude vec2(aUVExtrude.x, aUVExtrude.y)
#define uv 		vec2(aUVExtrude.z, aUVExtrude.w)

void main()
{	
	/* Pass varying parameters */
	v_FragPosition =  vec3(model * vec4(aPos.xyz, 1.0));
	v_Color = aColor;
	v_Normal = aNormal;
	v_UV = aUVExtrude.zw;
	
	gl_Position = vec4(vec2(aPos.x, aPos.y) + (extrude * 5.0f), 0.0f, 1.0f) * mvp;
}