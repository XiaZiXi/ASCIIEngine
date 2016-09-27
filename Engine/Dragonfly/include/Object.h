#pragma once
#include <string>

#include "Vector.h"
#include "Event.h"
#include "Sprite.h"
#include "Box.h"

static int ID = 0;

namespace df {
	const int MAX_OBJ_EVENTS = 100;
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
		bool hasGravity;
		Solidness solidness;

		Sprite *p_sprite;
		bool sprite_center;
		int sprite_index;
		int sprite_slowdown;
		int sprite_slowdown_count;

		char sprite_transparency;

		Box box;

		int event_count;
		std::string event_name[MAX_OBJ_EVENTS];

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

		//Set object sprite to new one
		//If set_box is true, set bounding box to size of sprite
		//Set sprite index to 0
		void setSprite(Sprite *p_new_sprite, bool set_box = true);
		//Return pointer to sprite associated with this object
		df::Sprite *getSprite() const;

		//Set sprite to be centered at Object position
		void setCentered(bool centered = true);
		//Indicates if sprite is centered at object position
		bool isCentered() const;

		//Set index of current sprite frame to be displayed
		void setSpriteIndex(int new_sprite_index);
		//Get index of current sprite frame to be displayed
		int getSpriteIndex() const;

		//Set sprite transparency (0 = none)
		void setTransparency(char transparent = ' ');
		//Get sprite transparency (0 = none)
		char getTransparency() const;

		//Slows down sprite animations
		//Sprite slowdown is in multiples of GameManager frame time
		void setSpriteSlowdown(int new_sprite_slowdown);
		int getSpriteSlowdown() const;
		void setSpriteSlowdownCount(int new_sprite_slowdown_count);
		int getSpriteSlowdownCount() const;

		void setBox(Box new_box);
		Box getBox() const;

		//Register for interest in event
		//Keeps track of manager and event
		//Returns 0 if ok, else -1
		int registerInterest(std::string event_type);
		//Unregister for interest in event
		//Return 0 if ok, else -1
		int unregisterInterest(std::string event_type);

		//Update object
		void Update();
		//Handle event. Returns 0 if nothing happened, else 1
		virtual int eventHandler(const Event *p_e);
		//Draw single sprite frame
		//Drawing accounts for center and slowdown and advances sprite frame
		virtual void draw();
	};
}