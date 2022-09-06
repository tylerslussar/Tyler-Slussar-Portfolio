// Tyler Slussar
// CS 361 9:30AM
// MultiSet.cpp


#include "MultiSet.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

MultiSet::MultiSet()
{
	// when you call a MultiSet object the size and arraySize are initialized 
	_size = 0;
	_arraySize = 0;
}

void MultiSet::insert(int x, int count) {
	
	// checks to see if there are any values in the multiset
	if ((_arraySize == 0) and (_size == 0)) {
		_items[0] = ItemCount(x, count);
		_arraySize = _arraySize + 1;
		_size = _size + count;


	}

	else {
		// this handles if there is already a item in the multiset
		for (int i = 0; i < _arraySize; i++) {
			if (x == _items[i].item) {
				_items[i].count = _items[i].count + count;
				_size = _size + count;
				break;
			}

			// this handles if the item needs to be placed in the middle of the multiset
			// it handles the shifting of the items
			if (x < _items[i].item) {
				for (int j = _arraySize - 1; j >= i; j--) {
					_items[j + 1].count = _items[j].count;
					_items[j + 1].item = _items[j].item;
				}
				_items[i] = ItemCount(x, count);
				_arraySize = _arraySize + 1;
				_size = _size + count;
				break;
			}
			// this handles if the item is larger than all other values. 
			// it will add it to the end of the multiset
			if (x > _items[_arraySize - 1].item) {
				_items[_arraySize] = ItemCount(x, count);
				_arraySize = _arraySize + 1;
				_size = _size + count;
				break;
			}
		}
		
	}
	
}

void MultiSet::removeOne(int x) {
	// this goes through the multiset until the item is found
	// then removes the item
	for (int i = 0; i <= _arraySize; i++) {
		if (x == _items[i].item) {
			_items[i].count = _items[i].count - 1;
			_size = _size - 1;
			break;
		}
		// if the count of the item is 0, this will shift the items accordingly
		if (_items[i].count == 0) {
			for (int j = i + 1; j < _arraySize; j++) {
				_items[i] = _items[j];
				_arraySize = _arraySize - 1;
			}
		}
	}
}

void MultiSet::removeAll(int x) {
	// this goes through the multiset, removes all the count of the items, shifts, and changes count
	for (int i = 0; i <= _arraySize; i++) {
		if (x == _items[i].item) {
			_size = _size - _items[i].count;
			for (int j = i + 1; j < _arraySize; j++) {
				_items[i] = _items[j];
				i = i + 1;
			}
			break;
		}
	}
	_arraySize = _arraySize - 1;

}

void MultiSet::clear() {
	// sets both values to 0, making the multiset have no valid data
	_size = 0;
	_arraySize = 0;

}

int MultiSet::count(int x) const{
	// searches for the item, obtains the count, if no items in the multiset, returns 0
	for (int i = 0; i <= _arraySize; i++) {
		if (x == _items[i].item) {
			return _items[i].count;
		}
	}
	return 0;
}

MultiSet operator+(const MultiSet& lhs, const MultiSet& rhs) {
	MultiSet addSet;		
	// adds all lhs to the new set
	for (int i = 0; i < lhs._arraySize; i++) {
		addSet._items[i] = lhs._items[i];
		addSet._arraySize = addSet._arraySize + 1;
		addSet._size = addSet._size + lhs._items[i].count;
	}

	// this is all similar to the insert method 
	for (int i = 0; i < rhs._arraySize; i++) {
		if (rhs._items[i].item == addSet._items[i].item) {
			addSet._items[i].count = addSet._items[i].count + rhs._items[i].count;
			addSet._size = addSet._size + rhs._items[i].count;
			
		}

		// this handles if the item needs to be placed in the middle of the multiset
		// it handles the shifting of the items
		if (rhs._items[i].item < addSet._items[i].item) {
			for (int j = addSet._arraySize - 1; j >= i; j--) {
				addSet._items[j + 1].count = addSet._items[j].count;
				addSet._items[j + 1].item = addSet._items[j].item;
			}
			addSet._items[i] = ItemCount(rhs._items[i].item, rhs._items[i].count);
			addSet._arraySize = addSet._arraySize + 1;
			addSet._size = addSet._size + rhs._items[i].count;
		}
		// this handles if the item is larger than all other values. 
		// it will add it to the end of the multiset
		if (rhs._items[i].item > addSet._items[addSet._arraySize - 1].item) {
			addSet._items[addSet._arraySize] = ItemCount(rhs._items[i].item, rhs._items[i].count);
			addSet._arraySize = addSet._arraySize + 1;
			addSet._size = addSet._size + rhs._items[i].count;
		}
	}
	return addSet;
}

MultiSet operator-(const MultiSet& lhs, const MultiSet& rhs) {
	MultiSet subSet;
	int item, count, subSwitch;

	// goes through the rhs and grabs one item
	for (int i = 0; i < rhs._arraySize; i++) {
		item = rhs._items[i].item;
		// will then go through the rhs and subtract if that item is in the lhs
		for (int j = 0; j < lhs._arraySize; j++) {
			if (item == lhs._items[j].item) {
				count = lhs._items[j].count - rhs._items[i].count;
				if (count != 0) {
					subSet.insert(item, count);
				}
				if (count == 0) {
					break;
				}

			}
		}
	}

	// this will check the state of the item
	// this goes through the left and if it is not in the right (determine by state)
	// it will then be added to the new set
	for (int i = 0; i < lhs._arraySize; i++) {
		item = lhs._items[i].item;
		for (int j = 0; j < rhs._arraySize; j++) {
			if (item == rhs._items[j].item) {
				subSwitch = 0;
				break;
			}
			if (item != rhs._items[j].item) {
				subSwitch = 1;
			}
		}
		if (subSwitch == 1) {
			subSet.insert(item, lhs._items[i].count);
		}
	}

	return subSet;
}

std::ostream& operator<<(std::ostream& os, const MultiSet& ms) {
	int count;
	os << "{";
	// grabs the count of the item
	for (int i = 0; i < ms._arraySize; i++){
		count = ms._items[i].count;
		// display the item "count" times
		for (int j = 0; j < count; j++) {
			// if it is the last item and count it will not output a comma and a space
			if ((ms._arraySize - 1 == i) and (j == count - 1)) {
				os << ms._items[i].item;
				break;
			}
			os << ms._items[i].item << ", ";
		}
	
	}
	os << "}";
	
	return os;
}