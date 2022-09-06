//
//  MultiSet.hpp
//  ClassArray
//
//  Created by David M Reed on 4/24/21.
//

#ifndef MultiSet_hpp
#define MultiSet_hpp

//--------------------------------------------------------------------

#include <iostream>

/// maximum number of elements that can be in the MultiSet
const int MAX_ITEMS = 20;

//--------------------------------------------------------------------

struct ItemCount {
    ItemCount(int value = 0, int countOfValue = 0) {
        item = value;
        count = countOfValue;
    }

    int item;
    int count = 0;
};

// comparision operators just compare the item
inline bool operator<(const ItemCount& lhs, const ItemCount& rhs) {
    return lhs.item < rhs.item;
}

inline bool operator<=(const ItemCount& lhs, const ItemCount& rhs) {
    return lhs.item <= rhs.item;
}

inline bool operator>(const ItemCount& lhs, const ItemCount& rhs) {
    return lhs.item > rhs.item;
}

inline bool operator>=(const ItemCount& lhs, const ItemCount& rhs) {
    return lhs.item >= rhs.item;
}

inline bool operator==(const ItemCount& lhs, const ItemCount& rhs) {
    return lhs.item == rhs.item;
}

inline bool operator!=(const ItemCount& lhs, const ItemCount& rhs) {
    return lhs.item != rhs.item;
}

//--------------------------------------------------------------------

/// set class that can hold multiple occurrences of an item
class MultiSet {

    friend MultiSet operator+(const MultiSet& lhs, const MultiSet& rhs);
    friend MultiSet operator-(const MultiSet& lhs, const MultiSet& rhs);
    friend std::ostream& operator<<(std::ostream& os, const MultiSet& ms);

public:
    MultiSet();

    /// insert x into the set
    /// @param x value to insert
    /// @param count number of copies of x to insert
    void insert(int x, int count = 1);

    /// remove one occurrence of x from the set
    /// @param x element to remove
    void removeOne(int x);

    /// remove all occurrences of x from the set
    /// @param x element to remove
    void removeAll(int x);

    /// remove all elements from the set
    void clear();

    /// return count of x in the set/list
    /// @param x value to count
    int count(int x) const;

    /// return total number of items in the MultiSet (duplicates count as separate items)
    int size() const { return _size; }

private:
    // total number of values (including duplicates) in the MultiSet
    int _size;
    // the number of unique values in the MultiSet
    int _arraySize;
    ItemCount _items[MAX_ITEMS];
};

/// returns union of two multisets
/// @param lhs set to union
/// @parah rhs other set to union
MultiSet operator+(const MultiSet& lhs, const MultiSet& rhs);

/// returns set difference of two multisets
/// for example, {10, 10, 10, 12, 16, 16}
///  - {5, 10, 16, 16, 16} 
/// would produce {10, 10, 12}
/// @param lhs left hand operand for - (elements to start with)
/// @param rhs right hand operand for - (elements to subract)
MultiSet operator-(const MultiSet& lhs, const MultiSet& rhs);

/// outputs elements as {1, 2, 2, 4} if set contained one 1, two 2, and one 4
/// @param os stream to output to
/// @param ms the MultiSet to output
std::ostream& operator<<(std::ostream& os, const MultiSet& ms);

#endif /* MultiSet_hpp */