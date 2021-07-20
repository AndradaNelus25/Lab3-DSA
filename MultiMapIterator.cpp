#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	this->current = col.map->head;
	this->count = 0;
	this->size = col.map->size;
}
//Complexity : Theta(1)

TElem MultiMapIterator::getCurrent() const{
	if (!this->valid())
		throw exception();
	return this->col.map->elements[this->current];
}
//Complexity : Theta(1)

bool MultiMapIterator::valid() const {
	if (this->size == 0)
		return false;
	if (this->count != this->size)
		return true;
	if (this->current == -1)
		return false;
	if (this->col.map->next[this->current] == -1)
		return false;
	return true;
}
//Complexity : Theta(1)

void MultiMapIterator::next() {
	if(!this->valid())
		throw exception();
	this->current = this->col.map->next[this->current];
	this->count++;

}
//Complexity : Theta(1)

void MultiMapIterator::first() {
	this->current = this->col.map->head;
	this->count = 0;
	this->size = this->col.map->size;
}
//Complexity : Theta(1)

