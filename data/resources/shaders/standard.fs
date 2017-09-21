#version 330 core

/* In */
in vec3 v_FragPosition;
in vec4 v_Color;
in vec3 v_Normal;
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

	vec3 lightpos = vec3(1.2f, 1.0f, 2.0f);
	
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
	
	if(uni_renderPassType == 4)
	{
		vec3 lightcolor = vec3(1.0, 1.0, 1.0);
		vec3 lightpos = vec3(0.0, 0.0, 0.0);
		
	    float ambientStrength = 0.5f;
		vec3 ambient = ambientStrength * lightcolor;
		
		vec3 norm = normalize(v_Normal);
		vec3 lightdir = normalize(lightpos - v_FragPosition); 
		
		float diff = max(dot(norm, lightdir), 0.0);
		vec3 diffuse = diff * lightcolor;

		vec3 result = (ambient * diffuse) * color.xyz;
		
		finalColor = vec4(result, 1.0);
	}
	
	FragColor = finalColor;
}