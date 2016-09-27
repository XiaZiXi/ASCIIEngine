#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Color.h"
#include "Manager.h"
#include "Vector.h"
#include "Frame.h"

const std::string WINDOW_HORIZONTAL_PIXELS_TOKEN = "window_horizontal_pixels";
const std::string WINDOW_VERTICAL_PIXELS_TOKEN = "window_vertical_pixels";
const std::string WINDOW_HORIZONTAL_CHARS_TOKEN = "window_horizontal_chars";
const std::string WINDOW_VERTICAL_CHARS_TOKEN = "window_vertical_chars";
const std::string WINDOW_BACKGROUND_COLOR_TOKEN = "window_background_color";
const std::string WINDOW_STYLE_TOKEN = "window_style";
const std::string WINDOW_TITLE_TOKEN = "window_title";
const std::string SHOW_MOUSE_TOKEN = "show_mouse";
const std::string HEADLESS_MODE_TOKEN = "headless";
const std::string FONT_FILE_STRING_TOKEN = "font_file";

//Helper methods
//Compute character height
float charHeight();
//Compute character width
float charWidth();
//Convert ASCII spaces (x,y) to window pixels (x,y)
df::Vector spacesToPixels(df::Vector spaces);
//Convert ASCII spaces (x,y) to window pixels (x,y)
df::Vector pixelsToSpaces(df::Vector pixels);

namespace df {

	enum Justification {
		LEFT_JUSTIFIED,
		CENTER_JUSTIFIED,
		RIGHT_JUSTIFIED
	};

	const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
	const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
	const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
	const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
	const int WINDOW_STYLE_DEFAULT = sf::Style::Default;
	const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
	const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
	const std::string FONT_FILE_DEFAULT = "df-font.ttf";

	class GraphicsManager : public Manager {
	private:
		GraphicsManager();
		GraphicsManager(GraphicsManager const&);
		void operator=(GraphicsManager const&);
		//Font used for ASCII graphics
		sf::Font font;
		//Pointer to SFML window
		sf::RenderWindow *p_window;
		int window_horizontal_pixels;
		int window_vertical_pixels;
		int window_horizontal_chars;
		int window_vertical_chars;
		int window_style;
		std::string window_title;
		std::string font_file_label;
		bool isHeadless;
		bool showMouse;
		sf::Color window_background_color;

		int parseConfig();

	public:
		static GraphicsManager &getInstance();
		//Open graphics window ready for text-based display
		int startUp();
		//Close graphics window
		void shutDown();
		//Draw a character at screen location (x, y) with color
		//Return 0 if ok, else -1
		int drawCh(Vector world_pos, char ch, Color color) const;
		//Draw string at screen location (x, y) with color
		//Justified LEFT, CENTER, or RIGHT
		//Return 0 if ok, else -1
		int drawString(Vector world_pos, std::string str, Justification just, Color color) const;
		//Draw frame at window location (x, y) with color
		//If centered true, then center frame at (x,y)
		//Return 0 if ok, else -1
		int drawFrame(Vector world_pos, Frame frame, bool centered, Color color, char transparent) const;
		//Return window's horizontal maximum in chars
		int getHorizontal() const;
		//Return window's vertical maximum in chars
		int getVertical() const;
		//Return window's horizontal maximum in pixels
		int getHorizontalPixels() const;
		//Return window's vertical maximum in pixels
		int getVerticalPixels() const;
		//Set default background color. Return true if ok, else false
		bool setBackgroundColor(Color new_color);
		//Render current display buffer
		//Return 0 if ok, else -1
		int swapBuffers();
		//Return pointer to SFML drawing window
		sf::RenderWindow *getWindow() const;
	};
}