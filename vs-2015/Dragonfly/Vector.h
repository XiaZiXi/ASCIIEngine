#pragma once

namespace df {
	class Vector {
	private:
		float x;	//Horizontal component
		float y;	//Vertical component
	public:
		//Create a vector with initial coords
		Vector(float init_x, float init_y);
		//Create a vector that starts off (0,0)
		Vector();
		//Get/set horizontal component
		void setX(float new_x);
		float getX() const;
		//Get/set vertical component
		void setY(float new_y);
		float getY() const;
		//Set horz & vert components
		void setXY(float new_x, float new_y);
		//Get magnitude of vector;
		float getMagnitude() const;
		//Normalize vector;
		void normalize();
		//Scale vector
		void scale(float s);
		//Add two vectors, then return the new vector
		Vector operator+(const Vector &other) const;
		Vector operator-(const Vector &other) const;
		Vector operator*(const Vector &other) const;
		bool operator==(const Vector &other) const;
		bool operator!=(const Vector &other) const;
	};
}