#include "renderer_interface.h"

namespace MagusEngine
{
	Shader* Renderer_Interface::GetShader()
	{
		return _CurrentShader;
	}

	Material* Renderer_Interface::GetMaterial()
	{
		return _CurrentMaterial;
	}

	Texture* Renderer_Interface::GetTexture()
	{
		return _CurrentTexture;
	}
}