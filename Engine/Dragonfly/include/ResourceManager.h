#pragma once
#include <string>

#include "Manager.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"

namespace df {
	const int MAX_SPRITES = 1000;
	const int MAX_SOUNDS = 128;
	const int MAX_MUSICS = 128;
	//Delimiters for parsing Sprite files
	const std::string FRAMES_TOKEN = "frames";
	const std::string HEIGHT_TOKEN = "height";
	const std::string WIDTH_TOKEN = "width";
	const std::string COLOR_TOKEN = "color";
	const std::string END_FRAME_TOKEN = "end";
	const std::string END_SPRITE_TOKEN = "eof";

	class ResourceManager : public Manager {
	private:
		ResourceManager();
		ResourceManager(ResourceManager const &);
		void operator=(ResourceManager const &);
		Sprite *p_sprite[MAX_SPRITES];
		Sound sound[MAX_SOUNDS];
		Music music[MAX_MUSICS];
		int sprite_count;
		int sound_count;
		int music_count;

		int readLineInt(std::ifstream *p_file, int *p_line_num, const char *tag);
		std::string readLineStr(std::ifstream *p_file, int *p_line_num, const char *tag);
		Frame readFrame(std::ifstream *p_file, int *p_line_num, const char *tag, int width, int height);
	public:
		static ResourceManager &getInstance();

		//Get ResourceManager ready to manage resources
		int startUp();
		//Shut down, free any allocated sprites
		void shutDown();

		//Load sprite from file
		//Assign indicated label to sprite
		//Return 0 if ok, else -1
		int loadSprite(std::string filename, std::string label);

		//Unload sprite w/ indicated label
		//Return 0 if ok, else -1
		int unloadSprite(std::string label);

		//Find sprite with label
		//Return pointer to it if found, else NULL
		Sprite *getSprite(std::string label) const;

		//Load sound from file
		//Return 0 if ok, else -1
		int loadSound(std::string filename, std::string label);

		//Unload sound w/ indicated label
		//Return 0 if ok, else -1
		int unloadSound(std::string label);

		//Find sound with label
		//Return pointer to it if found, else NULL
		Sound *getSound(std::string label);

		//Load music from file
		//Return 0 if ok, else -1
		int loadMusic(std::string filename, std::string label);

		//Unload music w/ indicated label
		//Return 0 if ok, else -1
		int unloadMusic(std::string label);

		//Find music with label
		//Return pointer to it if found, else NULL
		Music *getMusic(std::string label);
	};
}