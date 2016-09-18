#pragma once
#include "Event.h"

namespace df {
	const std::string OUT_EVENT = "df::Out";

	class EventOut : public Event {
	public:
		EventOut();
	};
}