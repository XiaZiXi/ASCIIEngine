#include "GameManager.h"
#include "Sandbox.h"
using namespace df;
Sandbox & Sandbox::getInstance()
{
	static Sandbox instance;
	return instance;
}

void Sandbox::startup()
{
	if (!GameManager::getInstance().startUp()) {

	}
}

void Sandbox::reset()
{

}

void Sandbox::stop()
{
}
