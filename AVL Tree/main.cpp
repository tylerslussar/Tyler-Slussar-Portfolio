// main.cpp
// Tyler Slussar 
//CS 361 9:30AM


#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include <cassert>

#define private public
#include "AVLTree.hpp"

int main(int argc, char *argv[]) {
	
	AVLTree<int> t;
	t.insert(2);
	t.insert(3);
	t.insert(8);
	t.insert(9);
	t.insert(4);
	t.insert(7);

	AVLTree<int> p;
	p.insert(5);
	p.insert(7);
	p.insert(13);
	p.insert(2);
	p.insert(1);

	cout << "test insert" << endl;
	assert(t._root->_item == 4);
	assert(t._root->_left->_left->_item == 2);
	assert(t._root->_right->_item == 8);
	assert(t._root->_right->_left->_item == 7);
	assert(t._root->_right->_right->_item == 9);
	assert(t._size == 6);
	assert(t._root->_height == 2);
	assert(t._root->_left->_left->_parent.lock()->_item == 3);
	assert(t._root->_right->_left->_parent.lock()->_item == 8);
	assert(t._root->_parent.lock() == nullptr);
	assert(t._root->_left->_left->_height == 0);
	
	cout << "test preorder" << endl;
	t.printPreorder(); cout << "\n";

	cout << "test inorder" << endl;
	t.printInorder();  cout << "\n";

	cout << "test postorder" << endl;
	t.printPostorder(); cout << "\n";
	

	cout << "test max and min node()" << endl;
	assert(t.minimumNode()->_item == 2);
	assert(t.maximumNode()->_item == 9);
	assert(p.minimumNode()->_item == 1);
	assert(p.maximumNode()->_item == 13);
    cout << t.minimumNode()->_item << endl;
	cout << t.maximumNode()->_item << endl;

	cout << "test find" << endl;
	cout << t.find(7)->_item << endl;
	assert(t.find(20) == nullptr);
	assert(p.find(13)->_item == 13);

	AVLTree<int> d;
	d.insert(7);
	d.insert(11);
	d.insert(15);
	d.insert(14);
	d.insert(16);
	d.insert(17);
	d.insert(19);
	d.insert(21);
	d.insert(22);
	d.insert(18);
	d.insert(20);
	d.insert(35);

	cout << "test nextSmallestNode" << endl;
	cout << "test nextLargestNode" << endl;

	auto nineteen = d.find(19);
	auto sixteen = d.find(16);
	auto threefive = d.find(35);
	auto seventeen = d.find(17);

	d.nextSmallestNode(nineteen);
	d.nextSmallestNode(sixteen);
	d.nextSmallestNode(threefive);

	assert(d.nextSmallestNode(nineteen) == d.find(18));
	assert(d.nextSmallestNode(sixteen) == d.find(15));
	assert(t.nextSmallestNode(t.find(7)) == t.find(4));
	assert(t.nextSmallestNode(t.find(9)) == t.find(8));

	assert(d.nextLargestNode(nineteen) == d.find(20));
	assert(d.nextLargestNode(seventeen) == d.find(18));
	assert(d.nextLargestNode(d.find(18)) == d.find(19));
	


	cout << "test copy" << endl;
	AVLTree<int> s = p;
	assert(s._root->_item == 7);
	assert(s._root->_left->_item == 2);
	assert(s._root->_left->_parent.lock() == s._root);
	assert(s._root->_left->_right->_item == p._root->_left->_right->_item);
	assert(s._root->_left->_right->_parent.lock()->_item == 2);
	assert(s.size() == p.size());


	cout << "test clear" << endl;
	p.clear();
	assert(p._root == nullptr);
	assert(p.size() == 0);

	
	


	return 0;
}