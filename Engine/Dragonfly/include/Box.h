#pragma once
#include "Vector.h"
namespace df {
	class Box {
	private:
		Vector corner;
		float vertical;
		float horizontal;
	public:
		Box();
		Box(Vector init_corner, float init_horizontal,
			float init_vertical);
		//Get/set corner of box
		void setCorner(Vector new_corner);
		Vector getCorner() const;
		//Get/set horizontal of box
		void setHorizontal(float new_horiz);
		float getHorizontal() const;
		//Get/set vertical of box
		void setVertical(float new_vert);
		float getVertical() const;
		bool operator==(const Box &other) const;
		bool operator!=(const Box &other) const;
	};
}