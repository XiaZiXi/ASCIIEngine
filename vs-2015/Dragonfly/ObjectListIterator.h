#pragma once
#include "ObjectList.h"
#include "Object.h"
namespace df {
	class ObjectList;
	class ObjectListIterator {
	private:
		ObjectListIterator();		//Must be given list when created
		const ObjectList *p_list;	//Point to ObjList iterating over
		int index;					//Index of current item
	public:
		ObjectListIterator(const ObjectList *p_l);
		//Set iterator to first item in list
		void first();
		//Iterate to next item in list
		void next();
		//Return true if done iterating, else false
		bool isDone();
		//Return current item
		Object *currentObject();
	};
}