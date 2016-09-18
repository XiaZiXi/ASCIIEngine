#pragma once
#include "Event.h"

namespace df {
	const std::string STEP_EVENT = "df::step";
	class EventStep : public Event{
	private:
		int step_count;	//iteration # of game loop
	public:
		//Default constructor
		EventStep();
		//Constructor w/ initial step count
		EventStep(int init_step_count);
		//Set/Get step count
		void setStepCount(int new_step_count);
		int getStepCount() const;
	};
}