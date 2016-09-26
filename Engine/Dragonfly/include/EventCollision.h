#pragma once
#include "Event.h"
#include "Object.h"

namespace df {
	const std::string COLLISION_EVENT = "df::Collision";
	class EventCollision : public Event {
	private:
		Vector pos;
		Object *p_obj1;
		Object *p_obj2;
	public:
		//Collision with p1 and p2 as NULL and pos as 0,0
		EventCollision();
		//Collision with p1 and p2 and pos where both collided
		EventCollision(Object *p_o1, Object *p_o2, Vector p);
		//Get/set obj 1
		void setObject1(Object *p_o1);
		Object * getObject1() const;
		//Get/set obj 2
		void setObject2(Object *p_o1);
		Object * getObject2() const;
		//Get/set position of collision
		void setPosition(Vector new_pos);
		Vector getPosition() const;
	};
}