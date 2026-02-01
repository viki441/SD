#pragma once

#include <list>
#include <vector>

using namespace std;


class HashTable
{
public:
	HashTable();
	HashTable(int size, bool duplAllowed);
	
	void insert(int key, int data);
	bool search(int key, int& data);
	void remove(int key);

	void display();


private:
	vector<list<pair<int, int>>> table;
	int size;
	bool duplAllowed;


	int hashFunction(int key)
	{
		return key % size;
	}
};



