//
//  DListNode.hpp
//  DListPyAPI
//
//  Created by David M Reed on 5/16/21.
//

#ifndef DListNode_h
#define DListNode_h

#ifdef DEBUG
#include <iostream>
#endif

#include <memory>

typedef int ItemType;

class DListNode {
    friend class DList;

public:
    DListNode(ItemType item, std::shared_ptr<DListNode> prev = nullptr, std::shared_ptr<DListNode> next = nullptr);

#ifdef DEBUG
    // ~DListNode() { std::cerr << "deallocate DListNode " << _item << std::endl; }
#endif

private:
    ItemType _item;
    std::shared_ptr<DListNode> _next;
    std::weak_ptr<DListNode> _prev;
};

inline DListNode::DListNode(ItemType item, std::shared_ptr<DListNode> prev, std::shared_ptr<DListNode> next) {
    _item = item;
    _prev = prev;
    _next = next;
}

#endif /* DListNode_h */