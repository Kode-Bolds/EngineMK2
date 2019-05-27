#include "Sound.h"
#include <string>

struct Audio
{
	std::wstring filename;
	bool active = false;
	bool loop = false;
	float volume;
	float pitch;
	float pan;
};