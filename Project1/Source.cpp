#include <iostream>
#include "Header.h"
#include "Hash_t.h"
#include <typeinfo>
#include <string>
#include <stdio.h> 

unsigned long HashFunc(string key) {
	unsigned long hash = 2139077667;

	for (int i = 0; i < key.length(); i++)
		hash = 11 * hash + key[i] % 7;

	return hash;
}

void main() {
	/*Table<int, int> a(5);
	a.Add(0, 11);
	a.Add(1, 14);
	a.Add(2, 12);
	a.Add(3, 15);
	int t = a.Find(2);
	
	SortTable<int, int> st(a);
	*/

	HashTable<string, int> T(HashFunc, 10);
	T.Add("one", 3);
	T.Add("two", 4);
	T.Add("three", 6);
	cout << "\n" << T.Find("two") << endl;
	T.Delete("two");
	cout << "\n" << T.Find("three") << endl;


	system("pause");
}