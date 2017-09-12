#include "resources.h"

namespace MagusEngine
{
	Resources::Resources()
	{
		
	}

	bool Resources::Initialise(unsigned int textureMax, unsigned int shaderMax, unsigned int colorMax, unsigned int materialMax, unsigned int fontMax)
	{
		/* Initialse memory for texture pointers */
		_textures = (Texture**)malloc(sizeof(Texture**) * textureMax);
		_textureMaxCount = textureMax;
		_textureCount = 0;

		/* Initialse memory for shader pointers */
		_shaders = (Shader**)malloc(sizeof(Shader**) * shaderMax);
		_shaderMaxCount = shaderMax;
		_shaderCount = 0;

		/* Initialse memory for color pointers */
		_colors = (Color**)malloc(sizeof(Color**) * colorMax);
		_colorMaxCount = colorMax;
		_colorCount = 0;

		/* Initialse memory for material pointers */
		_materials = (Material**)malloc(sizeof(Material**) * colorMax);
		_materialMaxCount = colorMax;
		_materialCount = 0;

		/* Initialse memory for font pointers */
		_fonts = (Font**)malloc(sizeof(Font**) * fontMax);
		_fontMaxCount = fontMax;
		_fontCount = 0;

		return true;
	}

	bool Resources::AddTextureFromFile(const char* name, const char* path)
	{
		Texture* newTexture = 0;
		const char* extension = GetFileExt(path);

		if(strcmp(extension, "bmp") == 0)
		{
			newTexture = LoadBmp(name, path);
		}
		else if(strcmp(extension, "png") == 0)
		{
			newTexture = LoadPng(name, path);
		}

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
		std::ifstream fragmentFile(fullFragmentPathBuffer, std::ios::binary | std::ios::ate);
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

	bool Resources::AddFontFromFile(const char* name, const char* path)
	{
		/* Full path buffer */
		char fullPathBuffer[255];
		sprintf_s(fullPathBuffer, "%s%s", _rootPath, path);

		char* tokstate = 0;		
		char* tokpairstate = 0;

		
		Font* newFont = new Font(0, name);

		//FILE* fp;
		//char buffer[255];

		//fp = fopen(fullPathBuffer, "r");

		///* Read and parse the first 4 lines */
		///* info information */
		//fgets(buffer, 255, (FILE*)fp);
		//printf("%s\n", buffer);
		//char *p = strtok_s(buffer, " ", &tokstate);
		//
		///* ignore the first token as it's a label */
		//p = strtok_s(buffer, " ", &tokstate);
		//while(p != NULL) {
		//	printf("%s\n", p);

		//	char* pair = strtok_s(p, "=", &tokpairstate);
		//	while(pair != NULL) {
		//		printf("%s\n", pair);
		//		pair = strtok_s(NULL, "=", &tokpairstate);
		//	}


		//	/* Get value pair */
		//	p = strtok_s(NULL, " ", &tokstate);
		//}
		//
		///* common information */
		//fgets(buffer, 255, (FILE*)fp);
		//printf("%s\n", buffer);

		//
		///* page information */
		//fgets(buffer, 255, (FILE*)fp);
		//printf("%s\n", buffer);

		//
		///* char count information */
		//fgets(buffer, 255, (FILE*)fp);
		//printf("%s\n", buffer);

		//

		///* chars information */
		//printf("%s\n", buffer);

		//fclose(fp);


		/* Add the resources object */
		_fonts[_fontCount] = newFont;
		_fontCount++;

		return true;
	}

	bool Resources::AddColor(int id, const char* name, float r, float g, float b, float a)
	{
		_colors[_colorCount] = new Color(id, name, r, g, b, a);
		_colorCount++;
		return true;
	}

	bool Resources::AddMaterial(Material* material)
	{
		_materials[_materialCount] = material;
		_materialCount++;

		/* resolve color */
		material->SetColor(GetColor(material->GetColorId()));
		
		/* resolve texture */
		material->SetTexture(GetTexture(material->GetTextureId()));

		return true;
	}

	Texture* Resources::LoadBmp(const char* name, const char* path)
	{
		/* Full path buffer */
		char fullPathBuffer[255];
		sprintf_s(fullPathBuffer, "%s%s", _rootPath, path);

		/* Open the file */
		std::ifstream file(fullPathBuffer, std::ios::binary);
		if (!file)
		{
			printf("Failure to open bitmap file.\n");
			return false;
		}

		BITMAPFILEHEADER* bmpHeader = nullptr; // Header
		BITMAPINFOHEADER* bmpInfo = nullptr; // Info 

		Byte* datBuff[2] = { nullptr, nullptr };

		Byte* pixels = nullptr;

		// Allocate byte memory that will hold the two headers
		datBuff[0] = new Byte[sizeof(BITMAPFILEHEADER)];
		datBuff[1] = new Byte[sizeof(BITMAPINFOHEADER)];

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
		pixels = new Byte[imageSize];

		// Go to where image data starts, then read in image data
		file.seekg(bmpHeader->bfOffBits);
		file.read((char*)pixels, imageSize);


		Byte tmpRGB = 0; // Swap buffer
		for (long i = 0; i < imageSize; i += 3)
		{
			tmpRGB = pixels[i];
			pixels[i] = pixels[i + 2];
			pixels[i + 2] = tmpRGB;
		}


		file.close();

		/* New texture object */
		Texture* newTexture = new Texture(name, bmpInfo->biWidth, bmpInfo->biHeight);

		/* Intialise texture memory */
		newTexture->Initialise(imageSize);

		/* Load pixels in to texture object */
		newTexture->LoadPixelData(pixels, imageSize);

		delete[] datBuff[0];
		delete[] datBuff[1];

		return newTexture;
	}

	Texture* Resources::LoadPng(const char* name, const char* path)
	{
		/* Full path buffer */
		char fullPathBuffer[255];
		sprintf_s(fullPathBuffer, "%s%s", _rootPath, path);

		unsigned int error;
		unsigned width, height;
		unsigned char* pixels = nullptr;

		error = lodepng_decode32_file(&pixels, &width, &height, fullPathBuffer);

		/* Calculate image size */
		long imageSize = width * height * 4;

		/* New texture object */
		Texture* newTexture = new Texture(name, width, height);

		/* Intialise texture memory */
		newTexture->Initialise(imageSize);

		/* Load pixels in to texture object */
		newTexture->LoadPixelData((Byte*)pixels, imageSize);

		return newTexture;
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

	/* Color Functions */
	unsigned int Resources::GetColorCount()
	{
		return _colorCount;
	}

	Color* Resources::GetColor(unsigned int index)
	{
		return _colors[index];
	}


	/* Material Functions */
	unsigned int Resources::GetMaterialCount()
	{
		return _materialCount;
	}

	Material* Resources::GetMaterial(unsigned int index)
	{
		return _materials[index];
	}

	/* Font Functions */
	unsigned int Resources::GetFontCount()
	{
		return _fontCount;
	}

	Font* Resources::GetFont(unsigned int index)
	{
		return _fonts[index];
	}

	/* Setters */
	void Resources::SetRootPath(const char* path) { strcpy_s(_rootPath, path); }

	/* Getters */
	char* Resources::GetRootPath() { return _rootPath; }
}