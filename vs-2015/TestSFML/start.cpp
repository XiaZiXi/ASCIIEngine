#include <iostream>
#include <SFML/Graphics.hpp>
int main()
{
	sf::Font font;
	if (font.loadFromFile("df-font.ttf") == false) {
		std::cout << "Failed to load 'df-font.ttf'." << std::endl;
		return -1;
	}
	sf::Text text;
	text.setFont(font);
	text.setString("Hello, World!");
	text.setCharacterSize(32);
	text.setFillColor(sf::Color::Green);
	//text.setColor(sf::Color::Green);
	text.setStyle(sf::Text::Bold);
	text.setPosition(96, 134);
	int window_horizontal = 1024;
	int window_vertical = 768;
	sf::RenderWindow *p_window = new sf::RenderWindow(sf::VideoMode(window_horizontal, window_vertical), "Title - Dragonfly!",
		sf::Style::Titlebar);

	if (!p_window) {
		std::cout << "Error! Unable to allocate RenderWindow." << std::endl;
		return -1;
	}

	p_window->setMouseCursorVisible(false);
	p_window->setVerticalSyncEnabled(true);

	while (1) {
		p_window->clear();
		p_window->draw(text);
		p_window->display();

		//See if window closed
		sf::Event event;
		while (p_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				p_window->close();
			delete p_window;
			return 0;
		}
	}

	return 0;
}