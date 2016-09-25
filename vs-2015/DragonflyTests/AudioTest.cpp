#include "AudioTest.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "Music.h"

void AudioTest::loadSoundTest()
{
	df::ResourceManager &rm = df::ResourceManager::getInstance();
	assertOK(rm.loadSound("sounds/explode.wav", "explode"), "loadSound()", "Loading sound that exists");
	assertERROR(rm.loadSound("sounds/boom.wav", "boom"), "loadSound()", "Loading sound that does not exist");
	//TODO: test for full sound array
}

void AudioTest::unloadSoundTest()
{
	df::ResourceManager &rm = df::ResourceManager::getInstance();
	assertOK(rm.unloadSound("explode"), "unloadSound()", "Unloading sound that exists");
	assertERROR(rm.unloadSound("boom"), "unloadSound()", "Unloading sound that does not exist");
}

void AudioTest::getSoundTest()
{
	df::ResourceManager &rm = df::ResourceManager::getInstance();
	Sound *a = rm.getSound("explode");
	bool isNull = (a == NULL);
	assertFalse(isNull, "getSound(), isNull", "Get loaded in sound");
	Sound *b = rm.getSound("fire");
	isNull = (b == NULL);
	assertTrue(isNull, "getSound(), isNull", "Get not yet loaded in sound");
}

void AudioTest::loadMusicTest()
{
	df::ResourceManager &rm = df::ResourceManager::getInstance();
	assertOK(rm.loadMusic("sounds/start-music.wav", "start-music"), "loadMusic()", "Loading music that exists");
	assertERROR(rm.loadMusic("sounds/boom.wav", "boom"), "loadMusic()", "Loading sound that does not exist");
	//TODO: test for full music array
}

void AudioTest::unloadMusicTest()
{
	df::ResourceManager &rm = df::ResourceManager::getInstance();
	assertOK(rm.unloadMusic("start-music"), "unloadMusic()", "Unloading music that exists");
	assertERROR(rm.unloadMusic("boom"), "unloadMusic()", "Unloading music that does not exist");
}

void AudioTest::getMusicTest()
{
	df::ResourceManager &rm = df::ResourceManager::getInstance();
	Music *a = rm.getMusic("start-music");
	bool isNull = (a == NULL);
	assertFalse(isNull, "getMusic(), isNull", "Get loaded in music");
	Music *b = rm.getMusic("fire");
	isNull = (b == NULL);
	assertTrue(isNull, "getSound(), isNull", "Get not yet loaded in sound");
}

AudioTest::AudioTest()
{
	setup("AudioTest");
}

void AudioTest::run()
{
	Test::run();
	loadSoundTest();
	getSoundTest();
	unloadSoundTest();
	loadMusicTest();
	getMusicTest();
	unloadMusicTest();
	printResults();
}
