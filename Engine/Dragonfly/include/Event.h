#pragma once
#include <string>
namespace df {
	const std::string UNDEFINED_EVENT = "df::undefined";
	class Event {
	private:
		std::string event_type;
	public:
		//Base event
		Event();
		//Destructor
		virtual ~Event();
		//Set/Get type of event
		void setType(std::string new_type);
		std::string getType() const;
	};
}