// HashTable.cpp : Defines the entry point for the console application.
//

/* program to construct hash table using open addressing */
#include <ostream>
#include <stdio.h>
#include <stdlib.h>

class HashEntry {
private:
	int key;
	int value;
public:
	HashEntry(int key, int value) {
		this->key = key;
		this->value = value;
	}

	int getKey() {
		return key;
	}

	int getValue() {
		return value;
	}

	void setValue(int value) {
		this->value = value;
	}
};

class DeletedEntry : public HashEntry {
private:
	static DeletedEntry *entry;
	DeletedEntry() :
		HashEntry(-1, -1) {
	}
public:
	static DeletedEntry *getUniqueDeletedEntry() {
		if (entry == NULL)
			entry = new DeletedEntry();
		return entry;
	}
};

DeletedEntry *DeletedEntry::entry = NULL;


const int TABLE_SIZE = 128;

class HashMap {
private:
	int size;
	HashEntry **table;
public:
	HashMap(int size = TABLE_SIZE) : size(size) 
	{
		table = new HashEntry*[size];
		for (int i = 0; i < size; i++)
			table[i] = NULL;
	}

	int get(int key) 
	{
		int hash = (key % size);
		int initialHash = -1;
		while (hash != initialHash && 
				(table[hash] == DeletedEntry::getUniqueDeletedEntry() || 
				 table[hash] != NULL && 
				 table[hash]->getKey() != key
				)
			  ) 
		{
			if (initialHash == -1)
				initialHash = hash;
			hash = (hash + 1) % size;
		}
		if (table[hash] == NULL || hash == initialHash)
			return -1;
		else
			return table[hash]->getValue();
	}

	void put(int key, int value) {
		int hash = (key % size);
		int initialHash = -1;
		int indexOfDeletedEntry = -1;
		while (hash != initialHash && (table[hash]
			== DeletedEntry::getUniqueDeletedEntry() || table[hash] != NULL
			&& table[hash]->getKey() != key)) 
		{
			if (initialHash == -1)
				initialHash = hash;
			if (table[hash] == DeletedEntry::getUniqueDeletedEntry())
				indexOfDeletedEntry = hash;
			hash = (hash + 1) % size;
		}
		if ((table[hash] == NULL || hash == initialHash) && indexOfDeletedEntry
			!= -1)
			table[indexOfDeletedEntry] = new HashEntry(key, value);
		else if (initialHash != hash)
			if (table[hash] != DeletedEntry::getUniqueDeletedEntry()
				&& table[hash] != NULL && table[hash]->getKey() == key)
				table[hash]->setValue(value);
			else
				table[hash] = new HashEntry(key, value);
	}

	void remove(int key) {
		int hash = (key % size);
		int initialHash = -1;
		while (hash != initialHash && (table[hash]
			== DeletedEntry::getUniqueDeletedEntry() || table[hash] != NULL
			&& table[hash]->getKey() != key)) {
			if (initialHash == -1)
				initialHash = hash;
			hash = (hash + 1) % size;
		}
		if (hash != initialHash && table[hash] != NULL) {
			delete table[hash];
			table[hash] = DeletedEntry::getUniqueDeletedEntry();
		}
	}

	~HashMap() {
		for (int i = 0; i < size; i++)
			if (table[i] != NULL && table[i]
				!= DeletedEntry::getUniqueDeletedEntry())
				delete table[i];
		delete[] table;
	}
};

int main()
{
	printf("Hello World!\n");

	HashMap oHashMap;

	oHashMap.put(5, 546);

    return 0;
}

