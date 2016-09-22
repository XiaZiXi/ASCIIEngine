#pragma once
#include "Manager.h"
#include "ObjectList.h"
#include "Box.h"
namespace df {
	const int MAX_ALTITUDE = 4;
	class WorldManager : public Manager {
	private:
		WorldManager();
		WorldManager(WorldManager const&);
		void operator=(WorldManager const&);

		ObjectList updates;		//All objects in world to update
		ObjectList deletions;	//All objects in world to delete
		ObjectList altitudes[MAX_ALTITUDE+1];

		Box boundary;			//World boundary
		Box view;				//Player view of game world
		Vector view_slack;			//View slack before view moves
		Object *p_view_following; //Object view is following
	public:
		static WorldManager &getInstance();
		//Startup game world. Init everything to empty.
		//Returns 0
		int startUp();
		//Shut down game world and delete all game world objects
		void shutDown();

		//Add object to the world. Return 0 if ok, else -1;
		int insertObject(Object *p_o);
		//Remove object from the world. Return 0 if ok, else -1;
		int removeObject(Object *p_o);
		//Move object in world
		int moveObject(Object * p_o, Vector new_pos);
		//Is there a collision at this point
		ObjectList isCollision(const Object *p_o, Vector where);
		//Change object altitude
		int changeAltitude(int old_alt, int new_alt, Object *p_o);
		//Returns list of all objects in world
		ObjectList getAllObjects(bool inactive=false) const;
		//Returns list of all objects in world with matching type
		ObjectList objectsOfType(std::string type) const;
		//Get/set boundary of world
		void setBoundary(Box new_boundary);
		Box getBoundary() const;
		//Set/get player view of game world
		void setView(Box new_view);
		Box getView() const;
		//Set view to center window on position view_pos
		//View edge will not go beyond world boundary
		void setViewPosition(Vector new_view_pos);
		//Set view to center window on Object
		//Set to NULL to stop following
		//If p_new_view_following not legit, return -1, else 0
		int setViewFollowing(Object *p_new_view_following);
		//Updates world
		//Deletes objects marked for deletion
		void update();
		//Draws all objects in world
		void draw();
		//Indicate object is to be deleted at end of current game loop
		//Return 0 if ok, else -1
		int markForDelete(Object *p_o);

	};
}