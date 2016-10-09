#include "LogManager.h"
#include "GraphicsManager.h"
#include "utility.h"

df::GraphicsManager::GraphicsManager() {
	setType("GraphicsManager");
	window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
	window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
	window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
	window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
	window_background_color = WINDOW_BACKGROUND_COLOR_DEFAULT;
	window_style = WINDOW_STYLE_DEFAULT;
	window_title = WINDOW_TITLE_DEFAULT;
	isHeadless = false;
	showMouse = false;
	font_file_label = FONT_FILE_DEFAULT;
}

int df::GraphicsManager::parseConfig()
{
	std::ifstream file(CONFIG_FILE);
	std::string line;
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			if (line.substr(0, 1) == COMMENT_TOKEN)
				continue;
			line = line.substr(0, line.length() - 1);
			int horizontal_chars = parseLineInt(&line, WINDOW_HORIZONTAL_CHARS_TOKEN.c_str());
			if (horizontal_chars != -1)
				window_horizontal_chars = horizontal_chars;
			int vertical_chars = parseLineInt(&line, WINDOW_VERTICAL_CHARS_TOKEN.c_str());
			if (vertical_chars != -1)
				window_vertical_chars = vertical_chars;
			int horizontal_pixels = parseLineInt(&line, WINDOW_HORIZONTAL_PIXELS_TOKEN.c_str());
			if (horizontal_pixels != -1)
				window_horizontal_pixels = horizontal_pixels;
			int vertical_pixels = parseLineInt(&line, WINDOW_VERTICAL_PIXELS_TOKEN.c_str());
			if (vertical_pixels != -1)
				window_vertical_pixels = vertical_pixels;
			std::string background_color = parseLineStr(&line, WINDOW_BACKGROUND_COLOR_TOKEN.c_str());
			if (background_color != "") {
				Color c;
				if (background_color == "red") c = Color::RED;
				else if (background_color == "yellow") c = Color::YELLOW;
				else if (background_color == "magenta") c = Color::MAGENTA;
				else if (background_color == "green") c = Color::GREEN;
				else if (background_color == "cyan") c = Color::CYAN;
				else if (background_color == "black") c = Color::BLACK;
				else if (background_color == "blue") c = Color::BLUE;
				else if (background_color == "white") c = Color::WHITE;
				else c = COLOR_DEFAULT;
				setBackgroundColor(c);
			}
			std::string style = parseLineStr(&line, WINDOW_STYLE_TOKEN.c_str());
			if (style != "") {
				if (style == "default")
					window_style = sf::Style::Default;
				else if (style == "fullscreen")
					window_style = sf::Style::Fullscreen;
			}
			std::string title = parseLineStr(&line, WINDOW_TITLE_TOKEN.c_str());
			if (title != "") 
				window_title = title;
			std::string show_mouse = parseLineStr(&line, SHOW_MOUSE_TOKEN.c_str());
			if (show_mouse != "") 
				showMouse = (show_mouse == "true") ? true : false;
			std::string headless_mode = parseLineStr(&line, HEADLESS_MODE_TOKEN.c_str());
			if (headless_mode != "") 
				isHeadless = (headless_mode == "true") ? true : false;
			std::string font_file = parseLineStr(&line, FONT_FILE_STRING_TOKEN.c_str());
			if (font_file != "")
				font_file_label = font_file;
		}
		file.close();
		return 0;
	}
	return -1;
}

df::GraphicsManager & df::GraphicsManager::getInstance()
{
	static GraphicsManager instance;
	return instance;
}

int df::GraphicsManager::startUp()
{
	parseConfig();
	LogManager &lm = LogManager::getInstance();
	//if window is already created, do nothing
	//or if the setting is set to headless
	if (p_window != NULL || isHeadless) {
		return 0;
	}

	p_window = new sf::RenderWindow(sf::VideoMode(window_horizontal_pixels, window_vertical_pixels), 
		window_title,
		window_style);

	if (!p_window) {
		std::cout << "Error! Unable to allocate RenderWindow." << std::endl;
		return -1;
	}

	p_window->setMouseCursorVisible(showMouse);
	p_window->setVerticalSyncEnabled(true);

	if (font.loadFromFile(font_file_label) == false) {
		std::cout << "Failed to load 'df-font.ttf'." << std::endl;
		return -1;
	}
	p_window->clear(window_background_color);
	lm.writeLog("GraphicsManager::startUp(): Started successfully!");
	Manager::startUp();
	return 0;
}

void df::GraphicsManager::shutDown()
{
	//See if window closed
	sf::Event event;
	if (p_window == NULL)
		return;
	delete p_window;
}

int df::GraphicsManager::drawCh(Vector world_pos, char ch, Color color) const
{
	LogManager &lm = LogManager::getInstance();
	if (p_window == NULL) {
		lm.writeLog("GraphicsManager::drawCh(): p_window is NULL!");
		return -1;
	}
	Vector view_pos = worldToView(world_pos);
	Vector pixel_pos = spacesToPixels(world_pos);
	static sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
	rectangle.setFillColor(window_background_color);
	rectangle.setPosition(pixel_pos.getX() - charWidth() / 10,
		pixel_pos.getY() + charHeight() / 5);
	p_window->draw(rectangle);

	static sf::Text text("", font);
	text.setString(ch);
	text.setStyle(sf::Text::Bold);

	if (charWidth() < charHeight())
		text.setCharacterSize((unsigned int)charWidth() * 2);
	else
		text.setCharacterSize((unsigned int)charHeight() * 2);

	switch (color) {
	case YELLOW:
		text.setFillColor(sf::Color::Yellow);
		break;
	case RED:
		text.setFillColor(sf::Color::Red);
		break;
	case BLUE:
		text.setFillColor(sf::Color::Blue);
		break;
	case GREEN:
		text.setFillColor(sf::Color::Green);
		break;
	case MAGENTA:
		text.setFillColor(sf::Color::Magenta);
		break;
	case CYAN:
		text.setFillColor(sf::Color::Cyan);
		break;
	case WHITE:
		text.setFillColor(sf::Color::White);
		break;
	case BLACK:
		text.setFillColor(sf::Color::Black);
		break;
	default:
		text.setFillColor(sf::Color::White);
		break;
	}

	text.setPosition(pixel_pos.getX(), pixel_pos.getY());

	p_window->draw(text);

	return 0;
}

int df::GraphicsManager::drawString(Vector world_pos, std::string str, Justification just, Color color) const
{
	Vector starting_pos = world_pos;
	switch (just)
	{
	case df::LEFT_JUSTIFIED:
		break;
	case df::CENTER_JUSTIFIED:
		starting_pos.setX(world_pos.getX() - str.size() / 2);
		break;
	case df::RIGHT_JUSTIFIED:
		starting_pos.setX(world_pos.getX() - str.size());
		break;
	}

	for (int i = 0; i < (int)str.size(); i++) {
		Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
		drawCh(temp_pos, str[i], color);
	}

	return 0;
}

int df::GraphicsManager::drawFrame(Vector world_pos, Frame frame, bool centered, Color color, char transparent) const
{
	if (frame.getString() == "")
		return -1;

	int x_offset = 0;
	int y_offset = 0;
	if (centered) {
		x_offset = frame.getWidth() / 2;
		y_offset = frame.getHeight() / 2;
	}

	//Frame data stored in string
	std::string str = frame.getString();

	//Draw row by row, character by character
	for (int y = 0; y < frame.getHeight(); y++) {
		for (int x = 0; x < frame.getWidth(); x++) {
			if (transparent == NULL || (str[y*frame.getWidth() + x] != transparent)) {
				Vector temp_pos(world_pos.getX() - x_offset + x,
					world_pos.getY() - y_offset + y);
				drawCh(temp_pos, str[y*frame.getWidth() + x], color);
			}
		}
	}
	return 0;
}

int df::GraphicsManager::getHorizontal() const
{
	return window_horizontal_chars;
}

int df::GraphicsManager::getVertical() const
{
	return window_vertical_chars;
}

int df::GraphicsManager::getHorizontalPixels() const
{
	return window_horizontal_pixels;
}

int df::GraphicsManager::getVerticalPixels() const
{
	return window_vertical_pixels;
}

bool df::GraphicsManager::setBackgroundColor(Color new_color)
{
	sf::Color color;
	switch (new_color)
	{
	case YELLOW:
		color = sf::Color::Yellow;
		break;
	case RED:
		color = sf::Color::Red;
		break;
	case BLUE:
		color = sf::Color::Blue;
		break;
	case GREEN:
		color = sf::Color::Green;
		break;
	case MAGENTA:
		color = sf::Color::Magenta;
		break;
	case CYAN:
		color = sf::Color::Cyan;
		break;
	case WHITE:
		color = sf::Color::White;
		break;
	case BLACK:
		color = sf::Color::Black;
		break;
	default:
		//invalid color
		color = WINDOW_BACKGROUND_COLOR_DEFAULT;
		return false;
	}
	window_background_color = color;
	return true;
}

int df::GraphicsManager::swapBuffers()
{
	if (p_window == NULL)
		return -1;
	p_window->display();
	p_window->clear(window_background_color);
	return 0;
}

sf::RenderWindow * df::GraphicsManager::getWindow() const
{
	return p_window;
}


//Compute character height
float charHeight() {
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
	return (float)graphics_manager.getVerticalPixels() /
		(float)graphics_manager.getVertical();
}

//Compute character width
float charWidth() {
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
	return (float)graphics_manager.getHorizontalPixels() /
		(float)graphics_manager.getHorizontal();
}

//Convert ASCII spaces (x,y) to window pixels (x,y)
df::Vector spacesToPixels(df::Vector spaces) {
	return df::Vector(spaces.getX() * charWidth(),
		spaces.getY() * charHeight());
}

//Convert window pixels (x,y) to ASCII spaces (x,y)
df::Vector pixelsToSpaces(df::Vector pixels) {
	return df::Vector(pixels.getX() / charWidth(),
		pixels.getY() / charHeight());
}