#include "ObjectList.h"

df::ObjectList::ObjectList()
{
	count = 0;
}

int df::ObjectList::insert(Object * p_o)
{
	if (count == MAX_OBJECTS) 
		return -1;
	else {
		p_object[count] = p_o;
		count++;
		return 0;
	}
}

int df::ObjectList::remove(Object * p_o)
{
	for (int i = 0; i < count; i++) {
		if (p_object[i] == p_o) { //if we found it
			for (int j = i; j < count - 1; j++) {
				p_object[j] = p_object[j + 1];
			}
			p_object[count] = NULL;
			count--;
			return 0;
		}
	}
	return -1;
}

void df::ObjectList::clear()
{
	count = 0;
}

int df::ObjectList::getCount() const
{
	return count;
}

bool df::ObjectList::isEmpty()
{
	return (count == 0);
}

bool df::ObjectList::isFull()
{
	return (count == MAX_OBJECTS);
}

df::ObjectList df::ObjectList::operator+(ObjectList list)
{
	ObjectList big_list = *this;
	ObjectListIterator li(&list);
	for (li.first(); !li.isDone(); li.next()) {
		Object *p_o = li.currentObject();
		big_list.insert(p_o);
	}
	return big_list;
}