#pragma once
#include "Test.h"

class AudioTest : public Test {
private:
	void loadSoundTest();
	void unloadSoundTest();
	void getSoundTest();
	void loadMusicTest();
	void unloadMusicTest();
	void getMusicTest();
public:
	AudioTest();
	void run();
};