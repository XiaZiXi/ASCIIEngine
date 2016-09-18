#include "Object.h"
#include "WorldManager.h"

df::Object::Object(){
	type = "Object";
	position = Vector();
	id = ID++;
	altitude = MAX_ALTITUDE / 2; 
	WorldManager &world_manager = WorldManager::getInstance();
	world_manager.insertObject(this);
	solidness = HARD;
	speed = 0;
	direction = Vector();
}

df::Object::~Object(){
	WorldManager &world_manager = WorldManager::getInstance();
	world_manager.removeObject(this);
}

void df::Object::setId(int new_id)
{
	id = new_id;
}

int df::Object::getId() const
{
	return id;
}

void df::Object::setType(std::string new_type)
{
	type = new_type;
}

std::string df::Object::getType() const
{
	return type;
}

void df::Object::setPosition(Vector new_pos)
{
	position = new_pos;
}

df::Vector df::Object::getPosition() const
{
	return position;
}

void df::Object::setAltitude(int new_alt)
{
	int old_alt = altitude;
	altitude = new_alt;
	//Tell world manager that we have changed altitudes
	WorldManager &world_manager = WorldManager::getInstance();
	world_manager.changeAltitude(old_alt, new_alt, this);
}

int df::Object::getAltitude() const
{
	return altitude;
}

void df::Object::Update()
{
}

int df::Object::eventHandler(const Event * p_e)
{
	return 0;
}

void df::Object::draw()
{
}

void df::Object::setSpeed(float new_speed)
{
	speed = new_speed;
}

float df::Object::getSpeed() const
{
	return speed;
}

void df::Object::setDirection(Vector new_direction)
{
	direction = new_direction;
}

df::Vector df::Object::getDirection() const
{
	return direction;
}

void df::Object::setVelocity(Vector new_velocity)
{
	speed = new_velocity.getMagnitude();
	new_velocity.normalize();
	direction = new_velocity;
}

df::Vector df::Object::getVelocity() const
{
	Vector velocity = direction;
	velocity.scale(speed);
	return velocity;
}

df::Vector df::Object::predictPosition()
{
	Vector new_pos = position + getVelocity();
	return new_pos;
}

bool df::Object::isSolid() const
{
	return (solidness == HARD || solidness == SOFT);
}

int df::Object::setSolidness(Solidness new_solid)
{
	solidness = new_solid;
	return 0;
}

df::Solidness df::Object::getSolidness() const
{
	return solidness;
}