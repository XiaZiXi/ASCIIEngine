#include "Object.h"
#include "WorldManager.h"
#include "GraphicsManager.h"

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

	p_sprite = NULL;
	sprite_index = 0;
	sprite_slowdown = 0;
	sprite_slowdown_count = 0;
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

void df::Object::setSpriteIndex(int new_sprite_index)
{
	sprite_index = new_sprite_index;
}

int df::Object::getSpriteIndex() const
{
	return sprite_index;
}

void df::Object::setTransparency(char transparent)
{
	sprite_transparency = transparent;
}

char df::Object::getTransparency() const
{
	return sprite_transparency;
}

void df::Object::setSpriteSlowdown(int new_sprite_slowdown)
{
	sprite_slowdown = new_sprite_slowdown;
}

int df::Object::getSpriteSlowdown() const
{
	return sprite_slowdown;
}

void df::Object::setSpriteSlowdownCount(int new_sprite_slowdown_count)
{
	sprite_slowdown_count = new_sprite_slowdown_count;
}

int df::Object::getSpriteSlowdownCount() const
{
	return sprite_slowdown_count;
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
	if (p_sprite == NULL)
		return;
	int index = getSpriteIndex();
	GraphicsManager::getInstance().drawFrame(position, p_sprite->getFrame(index),
		sprite_center, p_sprite->getColor());

	if (getSpriteSlowdown() == 0)
		return;

	int count = getSpriteSlowdownCount();
	count++;

	if (count >= getSpriteSlowdownCount()) {
		count = 0;
		index++;
		if (index >= p_sprite->getFrameCount())
			index = 0;
	}
	setSpriteSlowdownCount(count);
	setSpriteIndex(index);
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

void df::Object::setSprite(Sprite * p_new_sprite, bool set_box)
{
	p_sprite = p_new_sprite;
}

df::Sprite * df::Object::getSprite() const
{
	return p_sprite;
}

void df::Object::setCentered(bool centered)
{
	sprite_center = centered;
}

bool df::Object::isCentered() const
{
	return sprite_center;
}
