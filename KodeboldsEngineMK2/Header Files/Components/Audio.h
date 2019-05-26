#include "Sound.h"

struct Audio
{
	Sound* mSound;
	bool active = true;
	bool loop = false;
	float volume;
	float pitch;
	float pan;
};