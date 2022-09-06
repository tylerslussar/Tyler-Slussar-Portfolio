// 
// DList.cpp
// Tyler Slussar
// CS 361 9:30AM


#include "DList.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

DList::DList() {
	
	// constructor 
	_head = nullptr;
	_tail = nullptr;
	_size = 0;
}

void DList::append(const ItemType &x) {
	
	// nothing in the list 
	if (_size == 0) {
		_head = _tail = std::make_shared<DListNode>(x);
	}
	// adds the item as a new pointer to the end
	else {
		_tail->_next = std::make_shared<DListNode>(x, _tail);
		_tail = _tail->_next;
	}

	_size++;
}

void DList::insert(long position, const ItemType& x) {
	
	// handles negative indices 
	if (position < 0) {
		if (position >= _size) {
			position = 0;
		}
		else {
			position += _size;
		}
	}
	// nothing in the list or the position to insert is beyond the bounds
	if ((_size == 0) or (position >= _size)) {
		append(x);
		return;
	}
	// inserting at position 0
	else if (position == 0) {
		auto oldHead = _head;
		_head = std::make_shared<DListNode>(x, nullptr, _head);
		oldHead->_prev = _head;
	}
	// inserting anywhere in between
	else {
		auto afterNode = _find(position);
		auto prevNode = afterNode->_prev.lock();
		auto newNode = std::make_shared<DListNode>(x, prevNode, afterNode);
		prevNode->_next = newNode;
		afterNode->_prev = newNode;
	}
	_size++;
}

std::shared_ptr<DListNode> DList::_find(long position) const {
	
	// returns nullptr if position is not in the bounds
	if ((position < 0) and (_size < -position) or (position >= _size)) {
		return nullptr;
	}
	// handles negative indices
	if (position < 0) {
		auto node = _tail;
		for (int i = 0; i > position + 1; i--) {
			node = node->_prev.lock();
		}
		return node;
	}
	// handles positive indices
	else {
		auto node = _head;
		for (int i = 0; i < position; i++) {
			node = node->_next;
		}
		return node;

	}
}

DList::DList(const DList &source) {
	
	// copy constructor
	_copy(source);
}

void DList::_copy(const DList &source) {

	std::shared_ptr<DListNode> sourceNode, node;
	sourceNode = source._head;
	// makes the node = head and sourceNode to the next node
	if (sourceNode) {
		node = _head = std::make_shared<DListNode>(sourceNode->_item);
		sourceNode = sourceNode->_next;
	}
	
	else {
		_head.reset();
		_tail.reset();
	}
	// loops through to make a copy as long as there are nodes available
	while (sourceNode != nullptr) {
		node->_next = std::make_shared<DListNode>(sourceNode->_item);
		node->_next->_prev = node;
		node = _tail = node->_next;
		sourceNode = sourceNode->_next;
		
	}
	_size = source._size;
}

DList& DList::operator=(const DList& source) {
	
	// assignment operator
	if (this != &source) {
		_head = nullptr;
		_tail = nullptr;
		_copy(source);
	}
	return *this;
}

ItemType DList::operator[](long position) const {
	
	// find nodes and returns it 
	auto node = _find(position);
	return node->_item;
}

ItemType& DList::operator[](long position) {
	
	// find nodes and returns it 
	auto node = _find(position);
	return node->_item;
}

void DList::clear() {

	// resets head and tail which will clear nodes in between
	_head.reset();
	_tail.reset();
	_size = 0;
}

ItemType DList::pop(long position) {

	// deletes in the position passed in
	return _delete(position);
}

void DList::remove(ItemType x) {

	auto node = _head;

	// loops through DList until item is found
	while ((node != nullptr) and (node->_item != x)){
		node = node->_next;
	}
	auto prevNode = node->_prev.lock();
	auto afterNode = node->_next;

	// assigns nodes to the correct placement
	if (prevNode != nullptr) {
		prevNode->_next = node->_next;
	}
	else {
		_head = node->_next;
	}
	if (afterNode != nullptr) {
		afterNode->_prev = node->_prev.lock();
	}
	else {
		_tail = node->_prev.lock();
	}
	// decreases the size after item is found and the pointer point to their new
	// correct location
	_size -= 1;
}

size_t DList::index(ItemType x, size_t start) const {
	
	
	auto position = start;
	auto node = _find(start);

	// loops through while adding to position
	while ((node) and (node->_item != x)) {
		node = node->_next;
		position += 1;
	}
	// if not found 
	if (node == nullptr) {
		return -1;
	}
	return position;
}

int DList::count(ItemType x) const {
	
	int total = 0;
	std::shared_ptr<DListNode> node;

	node = _head;

	// loops through and every time the item is found it adds to the total
	for (int i = 0; i < _size; i++) {
		if (node->_item == x) {
			total += 1;
		}
		node = node->_next;
	}
	return total;
}

void DList::extend(const DList otherList) {

	// grabs the length of the otherList
	int length = otherList.length();
	auto node = otherList._head;
	// loops through only the number of times length equals
	// appends those values to the DList
	for (int i = 0; i < length; i++) {
		append(node->_item);
		node = node->_next;
	}
}

ItemType DList::_delete(long position) {
	ItemType removedValue;
	// handles negative indices
	if (position < 0) {
		position += _size;
	}
	// removes head
	if (position == 0) {
		removedValue = _head->_item;
		_head = _head->_next;

		if (_head == nullptr) {
			_tail = nullptr;
		}
		else {
			_head->_prev.lock() = nullptr;
		}
	}
	// removes tail or positions out of bounds
	else if (position >= _size - 1) {
		
		removedValue = _tail->_item;
		_tail = _tail->_prev.lock();
		
		if (_tail != nullptr) {
			_tail->_next = nullptr;
		}
		else {
			_head = nullptr;
		}
	}
	// removes any in between value
	else {
		auto node = _find(position);
		removedValue = node->_item;
		auto prevNode = node->_prev.lock();
		auto nextNode = node->_next;
		prevNode->_next = nextNode;
		nextNode->_prev = prevNode;
	}
	_size -= 1;
	return removedValue;
	
}