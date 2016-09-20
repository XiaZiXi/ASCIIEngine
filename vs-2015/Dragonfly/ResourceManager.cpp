#include <iostream>
#include <fstream>
#include <string>

#include "ResourceManager.h"
#include "LogManager.h"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

df::ResourceManager::ResourceManager() {
	setType("ResourceManager");
}

df::ResourceManager & df::ResourceManager::getInstance()
{
	static ResourceManager instance;
	return instance;
}

int df::ResourceManager::startUp()
{
	sprite_count = 0;
	Manager::startUp();
	return 0;
}

void df::ResourceManager::shutDown()
{
	for (int i = 0; i < sprite_count; i++) {
		delete p_sprite[i];
	}
	//delete[] &p_sprite;
	Manager::shutDown();
}

int df::ResourceManager::loadSprite(std::string filename, std::string label)
{
	LogManager &lm = LogManager::getInstance();
	ifstream file(filename);
	string line;
	int line_count = 0;

	if (file.is_open()) {
		//read header
		int frame_ct = readLineInt(&file, &line_count, FRAMES_TOKEN.c_str());
		if (frame_ct == -1) {
			//log it
			return -1;
		}
		Sprite *s = new Sprite(frame_ct);
		int frame_width = readLineInt(&file, &line_count, WIDTH_TOKEN.c_str());
		int frame_height = readLineInt(&file, &line_count, HEIGHT_TOKEN.c_str());
		string frame_color = readLineStr(&file, &line_count, COLOR_TOKEN.c_str());
		if (frame_color == "") {
			lm.writeLog("ResourceManager::loadSprite(): Unable to read sprite color. Setting to default: White");
			s->setColor(COLOR_DEFAULT);
		}
		else {
			Color c;
			if (frame_color == "red") c = Color::RED;
			else if (frame_color == "yellow") c = Color::YELLOW;
			else if (frame_color == "yellow") c = Color::MAGENTA;
			else if (frame_color == "yellow") c = Color::GREEN;
			else if (frame_color == "yellow") c = Color::CYAN;
			else if (frame_color == "yellow") c = Color::BLACK;
			else if (frame_color == "yellow") c = Color::BLUE;
			else if (frame_color == "yellow") c = Color::WHITE;
			else c = COLOR_DEFAULT;
			s->setColor(c);
		}
		if (frame_width == -1 || frame_height == -1) {
			lm.writeLog("ResourceManager::loadSprite(): Unable to read sprite width and/or height.");
			return -1;
		}
		else {
			s->setHeight(frame_height);
			s->setWidth(frame_width);
		}
		while (file.good()) {
			//Peeky looky at the next line and see if it's eof
			//Otherwise continue adding frames
			if (peekLine(&file) == END_SPRITE_TOKEN)
				break;
			Frame f = readFrame(&file, &line_count, END_FRAME_TOKEN.c_str(), frame_width, frame_height);
			s->addFrame(f);
		}
		file.close();
		s->setLabel(label);
	}

	lm.writeLog("ResourceManager::loadSprite(): Unable to open file %s", filename.c_str());

	return -1;
}

int df::ResourceManager::unloadSprite(std::string label)
{
	for (int i = 0; i < sprite_count; i++) {
		if (p_sprite[i]->getLabel() == label) {
			delete p_sprite[i];
			p_sprite[i] = p_sprite[sprite_count - 1];
			sprite_count--;
			return 0;
		}
	}
	return -1;
}

df::Sprite * df::ResourceManager::getSprite(std::string label) const
{
	for (int i = 0; i < sprite_count; i++) {
		if (p_sprite[i]->getLabel() == label)
			return p_sprite[i];
	}
	return NULL;
}

int df::ResourceManager::readLineInt(ifstream *p_file, int *p_line_num, const char *tag) {
	LogManager &lm = LogManager::getInstance();
	string line;
	if (!p_file->good()) {
		lm.writeLog("ResourceManager::loadSprite(): Error line %d reading %s.", *(p_line_num), tag);
		return -1;
	}
	getline(*(p_file), line);
	if (!line.compare(0, strlen(tag), tag))
		return -1;
	int number = atoi(line.substr(strlen(tag)+1).c_str());
	*(p_line_num)++;
	return number;
}

std::string df::ResourceManager::readLineStr(ifstream *p_file, int *p_line_num, const char *tag) {
	LogManager &lm = LogManager::getInstance();
	string line, ret;
	if (!p_file->good()) {
		lm.writeLog("ResourceManager::loadSprite(): Error line %d reading %s.", *(p_line_num), tag);
		return "";
	}
	getline(*(p_file), line);
	if (!line.compare(0, strlen(tag), tag))
		return "";
	ret = line.substr(strlen(tag) + 1);
	*(p_line_num)++;
	return ret;
}

df::Frame df::ResourceManager::readFrame(ifstream *p_file, int *p_line_num, const char *tag, int width, int height) {
	LogManager &lm = LogManager::getInstance();
	string line, frame_str;
	for (int i = 0; i < height; i++) {
		if (!p_file->good()) {
			lm.writeLog("ResourceManager::loadSprite(): Error line %d reading %s.", *(p_line_num), tag);
			return Frame();
		}
		getline(*(p_file), line);
		if (strlen(line.c_str()) != width) {
			lm.writeLog("ResourceManager::loadSprite(): Error line %d reading %s. Line width %d, expected %d", 
				*(p_line_num), tag, strlen(line.c_str()), width);
			return Frame();
		}
		frame_str += line;
		*(p_line_num)++;
	}

	if (!p_file->good()) {
		lm.writeLog("ResourceManager::loadSprite(): Error line %d reading %s.", *(p_line_num), tag);
		return Frame();
	}
	getline(*(p_file), line);
	if (line != END_FRAME_TOKEN) {
		lm.writeLog("ResourceManager::loadSprite(): Error line %d reading %s. Line height %d, expected %d", 
			*(p_line_num), tag, *(p_line_num), height);
		return Frame();
	}
	Frame frame(width, height, frame_str);
	*(p_line_num)++;
	return frame;
}

void discardCR(std::string &str) {
	if (str.size() > 0 && str[str.size() - 1] == '\r')
		str.erase(str.size() - 1);
}

//Peek next line
std::string peekLine(std::ifstream * p_file)
{
	string s;
	std::streampos sp = p_file->tellg();
	getline(*(p_file), s);
	p_file->seekg(sp);
	return s;
}