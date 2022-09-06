// Tyler Slussar
// CS 361 9:30AM
// main.cpp


#include <iostream>
using namespace std;
#include <cassert>
#include "MultiSet.hpp"

int main() {
	MultiSet m1, m2, m3, m4, m5;
	m1.insert(1, 4);
	m1.insert(2, 6);
	m1.insert(11, 2);
	m1.insert(10, 1);
	m2.insert(7, 2);
	m2.insert(2, 2);
	m2.insert(1, 2);
	m2.insert(9, 5);
	m2.insert(2, 2);
	m3.insert(6, 4);
	m3.insert(1, 4);
	
	if (m1.count(1) != 4) {
		cout << "count of 1 is not 4" << endl;
	}
	if (m1.count(2) != 6) {
		cout << "count of 2 is not 6" << endl;
	}
	if (m2.count(2) != 4) {
		cout << "m2 count of 2 is not 4" << endl;
	}
	m2.removeOne(9);
	if (m2.count(9) != 4) {
		cout << "m2 did not have one 2 removed" << endl;
	}
	m1.removeOne(10);
	if (m2.size() != 12) {
		cout << "m1 did not have one 10 removed" << endl;
	}
	m2.removeAll(2);
	if (m2.size() != 8) {
		cout << "m2 did not have all 2s removed" << endl;
	}
	m1.clear();
	if (m1.size() != 0) {
		cout << "m1 did not clear" << endl;
	}
	cout << m2 << endl;
	m4 = m3 + m2;
	cout << m4 << endl;
	if (m4.size() != 16) {
		cout << "m2 + m3 is incorrect" << endl;
	}
	m5 = m4 - m3;
	cout << m5 << endl;
	if (m5.size() != 8) {
		cout << "m4 - m3 is incorrect";
	}
	return 0; 
}