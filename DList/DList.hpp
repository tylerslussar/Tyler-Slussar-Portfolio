//
//  DList.hpp
//  DListPyAPI
//
//  Created by David M Reed on 5/16/21.
//

#ifndef DList_hpp
#define DList_hpp

#include "DListNode.hpp"

class DList {

public:
    /// constructor
    DList();

    /// copy constructor
    DList(const DList& source);

    /// assignment operator
    DList& operator=(const DList& source);

    /// returns the number of items in the list
    size_t length() const { return _size; }

    /// item at index specified by position
    /// @param position index of item to return
    /// @return item at index specified by position
    ItemType operator[](long position) const;

    /// reference to item at index specified by position
    /// @param position index of item to return
    /// @return reference to item at index specified by position
    ItemType& operator[](long position);

    /// removes all elements from the list
    void clear();

    /// adds the value x onto the end of the list
    /// @param x value to add to the end of the list
    void append(const ItemType& x);

    /// inserts x at the index (negative or non-negative) at the specified poition; note if
    /// position is beyond the end, it adds to the end of the list or if position is beyond
    /// the beginning it inserts at the beginning
    /// @param position index to insert at
    /// @param x value to insert at specified position
    void insert(long position, const ItemType& x);

    /// remove and return element at index specified by position
    /// @param position index of element to remove
    ItemType pop(long position = -1);

    /// removes element from the list
    /// @param x element to remove
    void remove(ItemType x);

    /// returns non-negative index of x starting at index start
    /// @param x value to find the index of
    /// @return non-negative index of x or -1 if not found
    size_t index(ItemType x, size_t start = 0) const;

    /// returns number of copies of x in the list
    /// @param x value to count
    /// @return number of copies of x in the list
    int count(ItemType x) const;

    /// adds each element of otherList onto this list
    /// @param otherList list to add the elements of
    void extend(const DList otherList);

private:

    /// helper function for copy constructor and operator=
    /// @param source existing DList to make a copy of its nodes for and store in this
    void _copy(const DList& source);

    /// returns node at specified index
    /// @param position index from -length() to length()
    /// @return node at specified position or nullptr if position is out of range
    std::shared_ptr<DListNode> _find(long position) const;

    /// remove and return the element at the specified index
    /// if index is invalid, it does nothing
    /// @param position index of element to remove
    ItemType _delete(long position);

    // pointers to the head, and tail nodes
    std::shared_ptr<DListNode> _head, _tail;

    // number of items in the list
    long _size;
};

#endif /* DList_hpp */