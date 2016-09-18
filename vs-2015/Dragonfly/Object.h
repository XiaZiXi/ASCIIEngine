#pragma once
#include <string>

#include "Vector.h"
#include "Event.h"

static int ID = 0;

namespace df {
	enum Solidness {
		HARD,		//Causes collision and impedes
		SOFT,		//Causes collision but doesn't impede
		SPECTRAL	//No collisions are made
	};
	class Object {
	private:
		int id;
		int altitude;
		std::string type;
		Vector position;
		Vector direction;
		float speed;
		Solidness solidness;
	public:
		//Construct object. Set default params and add to
		//game world (WorldManager)
		Object();
		//Destroy object
		//Remove from game world
		virtual ~Object();

		//Set/Get obj id
		void setId(int new_id);
		int getId() const;

		//Set/Get type of obj
		void setType(std::string new_type);
		std::string getType() const;

		//Set/Get position of obj
		void setPosition(Vector new_pos);
		Vector getPosition() const;

		//Set/Get altitude
		void setAltitude(int new_alt);
		int getAltitude() const;

		//Set/Get Speed
		void setSpeed(float new_speed);
		float getSpeed() const;

		//Set/Get Direction
		void setDirection(Vector new_direction);
		df::Vector getDirection() const;

		//Set/Get Velocity
		void setVelocity(Vector new_velocity);
		df::Vector getVelocity() const;
		
		//Predict object position based on speed and direction
		df::Vector predictPosition();
		
		//is this object solid
		bool isSolid() const;

		//set/get solidness
		int setSolidness(Solidness new_solid);
		Solidness getSolidness() const;

		//Update object
		void Update();
		//Handle event. Returns 0 if nothing happened, else 1
		virtual int eventHandler(const Event *p_e);
		//Draw object
		virtual void draw();
	};
}