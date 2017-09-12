#version 330 core

/* In */
in vec2 v_UV;

/* Out */
out vec4 FragColor;

/* Uniforms */
uniform vec4 color;
uniform sampler2D uni_texture;


void main()
{
	vec4 finalColor = texture2D(uni_texture,v_UV);
	FragColor = finalColor * color;//mix(finalColor, color, 0.5f);
}