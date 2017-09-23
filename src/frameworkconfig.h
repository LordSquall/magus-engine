#ifndef _FRAMEWORKCONFIG_H_
#define _FRAMEWORKCONFIG_H_

namespace MagusEngine
{	
	typedef struct FrameworkConfig
	{
		char configfilePath[255];
		char title[25];
		int width;
		int height;
		bool fullscreen;

		unsigned int sr_vbo_memorylimit;
		unsigned int sr_ibo_memorylimit;
		unsigned int sr_vbo_limit;
		unsigned int sr_ibo_limit;

		bool softwareRendererEnabled;
		bool hardwareRendererEnabled;
		bool gpuBlend;

	}FrameworkConfig;
}

#endif