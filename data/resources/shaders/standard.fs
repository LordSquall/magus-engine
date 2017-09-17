#version 330 core

/* In */
in vec4 v_Color;
in vec2 v_UV;

/* Out */
out vec4 FragColor;

/* Uniforms */
uniform vec4 color;
uniform sampler2D uni_texture;
uniform int uni_textureEnabled;
uniform int uni_renderPassType;


void main()
{	
	vec4 finalColor;
	
	if(uni_renderPassType == 1)
	{
		finalColor = color;
	}
	else
	{
		if(uni_textureEnabled == 1)
		{
			/* sample current texture */
			finalColor = texture2D(uni_texture,v_UV);
		}
		else
		{
			finalColor = color;
		}
	}
	
	FragColor = finalColor;
}