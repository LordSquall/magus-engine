#include "resources.h"

namespace MagusEngine
{
	Resources::Resources()
	{
		
	}

	bool Resources::Initialise(unsigned int textureMax, unsigned int shaderMax)
	{
		/* Initialse memory for texture pointers */
		_textures = (Texture**)malloc(sizeof(Texture**) * textureMax);
		_textureMaxCount = textureMax;
		_textureCount = 0;

		/* Initialse memory for shader pointers */
		_shaders = (Shader**)malloc(sizeof(Shader**) * shaderMax);
		_shaderMaxCount = shaderMax;
		_shaderCount = 0;

		return true;
	}


	bool Resources::AddTextureFromFile(const char* name, const char* path)
	{
		/* Full path buffer */
		char fullPathBuffer[255];
		sprintf_s(fullPathBuffer, "%s%s", _rootPath, path);

		/* New texture object */
		Texture* newTexture = new Texture(name);

		/* Open the file */
		std::ifstream file(fullPathBuffer, std::ios::binary);
		if (!file)
		{
			printf("Failure to open bitmap file.\n");
			return false;
		}

		BITMAPFILEHEADER* bmpHeader = nullptr; // Header
		BITMAPINFOHEADER* bmpInfo = nullptr; // Info 

		uint8_t* datBuff[2] = { nullptr, nullptr };

		uint8_t* pixels = nullptr;

		// Allocate byte memory that will hold the two headers
		datBuff[0] = new uint8_t[sizeof(BITMAPFILEHEADER)];
		datBuff[1] = new uint8_t[sizeof(BITMAPINFOHEADER)];

		file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
		file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));

		// Construct the values from the buffers
		bmpHeader = (BITMAPFILEHEADER*)datBuff[0];
		bmpInfo = (BITMAPINFOHEADER*)datBuff[1];

		// Check if the file is an actual BMP file
		if (bmpHeader->bfType != 0x4D42)
		{
			printf("File %s isn't a bitmap file\n", fullPathBuffer);
			return false;
		}

		// Calculate image size
		long imageSize = bmpInfo->biWidth * bmpInfo->biHeight * (bmpInfo->biBitCount / 8);

		// First allocate pixel memory
		pixels = new uint8_t[imageSize];

		// Go to where image data starts, then read in image data
		file.seekg(bmpHeader->bfOffBits);
		file.read((char*)pixels, imageSize);


		uint8_t tmpRGB = 0; // Swap buffer
		for (long i = 0; i < imageSize; i += 3)
		{
			tmpRGB = pixels[i];
			pixels[i] = pixels[i + 2];
			pixels[i + 2] = tmpRGB;
		}


		file.close();

		delete[] datBuff[0];
		delete[] datBuff[1];


		/* Add the resources object */
		_textures[_textureCount] = newTexture;
		_textureCount++;

		return true;
	}

	bool Resources::AddShaderFromFile(const char* name, const char* vertexpath, const char* fragmentPath)
	{
		/* Full path buffer */
		char fullVertexPathBuffer[255];
		char fullFragmentPathBuffer[255];
		sprintf_s(fullVertexPathBuffer, "%s%s", _rootPath, vertexpath);
		sprintf_s(fullFragmentPathBuffer, "%s%s", _rootPath, fragmentPath);

		/* Sortes file size */
		std::streamsize filesize;

		/* New texture object */
		Shader* newShader = new Shader(name);

		/* Open the vertex file */
		std::ifstream vertexFile(fullVertexPathBuffer, std::ios::binary | std::ios::ate);
		if (!vertexFile)
		{
			printf("Failure to open bitmap file.\n");
			return false;
		}

		/* Get file size */
		filesize = vertexFile.tellg();

		/* Reset stream */
		vertexFile.seekg(0);

		/* Allocate memory in shader for source */
		newShader->InitailiseVertexSourceBuffer((unsigned int)filesize - 1);

		/* Read fill contents into the shader source buffer */
		vertexFile.read(newShader->GetVertexSrc(), filesize);

		/* Close file stream */
		vertexFile.close();

		/* Append termination character */
		newShader->GetVertexSrc()[filesize] = '\0';

		/* Open the fragment file */
		std::ifstream fragmentFile(fullFragmentPathBuffer, std::ios::binary);
		if (!fragmentFile)
		{
			printf("Failure to open fragment file.\n");
			return false;
		}

		/* Get file size */
		filesize = fragmentFile.tellg();

		/* Reset stream */
		fragmentFile.seekg(0);

		/* Allocate memory in shader for source */
		newShader->InitailiseFragmentSourceBuffer((unsigned int)filesize + 1);

		/* Read fill contents into the shader source buffer */
		fragmentFile.read(newShader->GetFragmentSrc(), filesize);

		/* Close the file stream */
		fragmentFile.close();

		/* Append termination character */
		newShader->GetFragmentSrc()[filesize] = '\0';

		/* Add the resources object */
		_shaders[_shaderCount] = newShader;
		_shaderCount++;

		return true;
	}

	/* Shader Functions */
	unsigned int Resources::GetShaderCount()
	{
		return _shaderCount;
	}

	Shader* Resources::GetShader(unsigned int index)
	{
		return _shaders[index];
	}

	/* Texture Functions */
	unsigned int Resources::GetTextureCount()
	{
		return _textureCount;
	}

	Texture* Resources::GetTexture(unsigned int index)
	{
		return _textures[index];
	}

	/* Setters */
	void Resources::SetRootPath(const char* path) { strcpy_s(_rootPath, path); }

	/* Getters */
	char* Resources::GetRootPath() { return _rootPath; }
}