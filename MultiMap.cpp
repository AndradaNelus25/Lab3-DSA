#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
	this->map = new SLLA;
	this->map->capacity = 10;
	this->map->elements = new TElem[this->map->capacity];
	this->map->next = new int[this->map->capacity];
	this->map->head = -1;
	for (int i = 1; i < this->map->capacity-1 ; i++) {
		this->map->next[i] = i + 1;
	}
	this->map->next[this->map->capacity-1] = -1;
	this->map->firstEmpty = 1;
	this->map->size = 0;
}
//Complexity : Theta(capacity)


void MultiMap::add(TKey c, TValue v) {
	if (this->map->firstEmpty == -1) {
		resize();
	}

	int newPos = this->map->firstEmpty;
	TElem elem = TElem{ c,v };

	this->map->elements[newPos] = elem;
	this->map->firstEmpty = this->map->next[this->map->firstEmpty];
	this->map->next[newPos] = this->map->head;
	this->map->head = newPos;
	//printMap();
	this->map->size++;
}
	
//Complexity : Best case: Theta(1) , Worst case: Theta(capacity), Overall complexity : O(capacity) 


bool MultiMap::remove(TKey c, TValue v) {
	int current = this->map->head;
	int previous = -1;
	int count = 0;

	
	while (count <= this->map->size && current != -1 && (this->map->elements[current].first != c || this->map->elements[current].second != v)) {
		//cout << this->map->elements[current].first << endl;
		//cout << this->map->elements[current].second << endl;
		previous = current;
		current = this->map->next[current];
	}

	if (current != -1) {
		if (current != this->map->head) {
			this->map->next[previous] = this->map->next[current];
			this->map->next[current] = this->map->firstEmpty;
			this->map->firstEmpty = current;
		}
		else {
			this->map->head = this->map->next[this->map->head];
			this->map->next[current] = this->map->firstEmpty;
			this->map->firstEmpty = current;
		}
		this->map->size--;
		return true;
	}
	else {
		return false;
	}
}
//Complexity : theta(capacity)


vector<TValue> MultiMap::search(TKey c) const {
	
	vector<TValue> elems;
	int current = this->map->head;
	int count = 0;
	while (count != this->map->size && current != -1) {
		//cout << "This is the position " << current << " and this is the key found: " << this->map->elements[current].first << endl;
		if (this->map->elements[current].first == c) {
			elems.push_back(this->map->elements[current].second);
		}
		current = this->map->next[current];
		count++;
	}
	
	return elems;

}
//Complexity : Best case: Theta(1) , Worst case: Theta(capacity), Overall complexity : O(capacity)


int MultiMap::size() const {
	
	return this->map->size;
}
//Complexity : Theta(1)


bool MultiMap::isEmpty() const {
	if (this->map->size == 0) {
		return true;
	}
	return false;
}
//Complexity : Theta(1)


MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}
//Complexity : Theta(1)



void MultiMap::resize() {
	TElem* elems = new TElem[this->map->capacity*2];
	int* newNext = new int[this->map->capacity * 2];

	for (int i = 0; i < this->map->capacity; i++) {
		elems[i] = this->map->elements[i];
		newNext[i] = this->map->next[i];
	}

	for (int i = this->map->capacity; i < this->map->capacity*2-1; i++) {
		newNext[i] = i + 1;
	}
	newNext[this->map->capacity*2-1] = -1;

	//delete[] this->map->elements;
	this->map->elements = elems;
	//delete[] this->map->next;
	this->map->next = newNext;
	this->map->firstEmpty = this->map->capacity+1;
	this->map->capacity = this->map->capacity * 2;
}
//Complexity : Theta(capacity)

void MultiMap::printMap()
{
	int current = this->map->head;
	while (current != -1) {
		//cout << "Position : " << current << " and element : " << this->map->elements[current].first << " " << this->map->elements[current].second << endl;
		current = this->map->next[current];

	}
}
//Complexity : Theta(capacity)


MultiMap::~MultiMap() {
	delete this->map;
}
//Complexity : theta(1)


