#ifndef _INPUT_H_
#define _INPUT_H_

namespace MagusEngine
{
	class Input
	{
	public:
		Input();
		
		void Initialise();

		void KeyDown(unsigned int);
		void KeyUp(unsigned int);

		bool IsKeyDown(unsigned int);

	private:
		bool m_keys[256];
	};
}

#endif