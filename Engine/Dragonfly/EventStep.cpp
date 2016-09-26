#include "EventStep.h"

df::EventStep::EventStep()
{
	step_count = 0;
	setType(STEP_EVENT);
}

df::EventStep::EventStep(int init_step_count)
{
	step_count = init_step_count;
	setType(STEP_EVENT);
}

void df::EventStep::setStepCount(int new_step_count)
{
	step_count = new_step_count;
}

int df::EventStep::getStepCount() const
{
	return step_count;
}
