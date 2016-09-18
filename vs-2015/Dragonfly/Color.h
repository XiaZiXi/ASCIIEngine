#pragma once
namespace df {
	enum Color {
		UNDEFINED_COLOR = -1,
		BLACK = 0,
		RED = 1,
		GREEN = 2,
		YELLOW = 3,
		BLUE = 4,
		MAGENTA = 5,
		CYAN = 6,
		WHITE = 7,
	};
	const Color COLOR_DEFAULT = WHITE;
	/*class Color {
		const int COLOR_DEFAULT = WHITE;
		const int UNDEFINED_COLOR = -1;
		const int BLACK = 0;
		const int RED = 1;
		const int GREEN = 2;
		const int YELLOW = 3;
		const int BLUE = 4;
		const int MAGENTA = 5;
		const int CYAN = 6;
		const int WHITE = 7;
	private:
		Color();
		sf::Color sf_color;
	public:
		Color(int _r, int _g, int _b);
		Color(int _r, int _g, int _b, int _a);
	}; */
}