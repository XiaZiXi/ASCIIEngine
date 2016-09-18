#pragma once
const int MAX_OBJECTS = 5000;
#include "Object.h"
#include "ObjectListIterator.h"

namespace df {
	class ObjectListIterator;
	class ObjectList {
	private:
		int count;						//Count of objects in list
		Object *p_object[MAX_OBJECTS];	//Array of pointers to objects
	public:
		friend class ObjectListIterator;
		//default constructor
		ObjectList();
		//Insert object pointer in list
		//Return 0 if ok, else -1
		int insert(Object *p_o);
		//Remove object pointer from list
		//Return 0 if found, else -1
		int remove(Object *p_o);
		//Clear list (setting count to 0)
		void clear();
		//Return current count of objs in list
		int getCount() const;
		//Return true if list is empty, else false;
		bool isEmpty();
		//Return true if list if full, else false;
		bool isFull();

		ObjectList operator+(ObjectList list);
	};
}