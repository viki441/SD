#include <iostream>
#include "HashTable.h"
#include <stdexcept>




HashTable::HashTable()
	:size(0), duplAllowed(false)
{
	table.resize(0);
}

HashTable::HashTable(int size, bool duplAllowed)
	:size(size), duplAllowed(duplAllowed)
{
	table.resize(size);
}
void HashTable::insert(int key, int data)
{
	int index = hashFunction(key);

	if (index == -1)
		throw runtime_error("");

	if (duplAllowed)
	{
		table[index].push_back({ key, data });
		return;
	}


	for (auto& pair : table[index])
	{
		if (pair.first == key)
		{
			pair.second = data;
			return;
		}
		
		table[index].push_back({ key, data });
	}
}

bool HashTable::search(int key, int& data)
{
	int index = hashFunction(key);

	for (auto& pair : table[index])
	{
		if (pair.first == key && pair.second == data)
			return true;

		return false;
	}
}

void HashTable::remove(int key)
{
	int index = hashFunction(key);
	table[index].clear();
	table.erase(table.begin() + index);
}


//void insert()

