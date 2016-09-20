#pragma once
#include <string>

#include "Manager.h"
#include "Sprite.h"

void discardCR(std::string &str);
//Peek next line
std::string peekLine(std::ifstream * p_file);

namespace df {
	const int MAX_SPRITES = 1000;
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
		int sprite_count;

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
	};
}