#include "Color.h"

df::CustomColor::CustomColor(int _r, int _g, int _b)
{
	sf_color = sf::Color(_r, _g, _b, 255);
}

df::CustomColor::CustomColor(int _r, int _g, int _b, int _a)
{
	sf_color = sf::Color(_r, _g, _b, _a);
}
