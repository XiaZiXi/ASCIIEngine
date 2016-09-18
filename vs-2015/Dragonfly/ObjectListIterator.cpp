#include "ObjectListIterator.h"

df::ObjectListIterator::ObjectListIterator(const ObjectList * p_l)
{
	p_list = p_l;
	first();
}

void df::ObjectListIterator::first()
{
	index = 0;
}

void df::ObjectListIterator::next()
{
	if (index < p_list->count)
		index++;
}

bool df::ObjectListIterator::isDone()
{
	return (index == p_list->count);
}

df::Object * df::ObjectListIterator::currentObject()
{
	return p_list->p_object[index];
}