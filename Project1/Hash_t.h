#include <iostream>
#include "Header.h"
#include <list>
#include <string>
#include <vector>

using namespace std;

template<class T>
unsigned long MyHashFunc(T key) {
    unsigned long hash = 2139062143;

    for (int i = 0; i < key; i++)
        hash = 37 * hash + key % 3;

    return hash;
}

template<>
unsigned long MyHashFunc(string key) {
    unsigned long hash = 2139062143;

    for (int i = 0; i < key.length(); i++)
        hash = 37 * hash + key[i] % 3;

    return hash;
}

template<class Key, class Data>
class HashTable : public Table<Key, Data> {

protected:
    int size;
	list<Record<Key, Data>> *dataArray;
	unsigned long (*HashFunc)(Key);

public:
    HashTable<Key, Data>(int _size = 5) : size(_size) {
        this->count = 0;
        this->dataArray = new list<Record<Key, Data>>[_size];
        this->HashFunc = MyHashFunc;
    }

    HashTable<Key, Data>(unsigned long (*hFunc)(Key), int _size = 5) :size(_size), HashFunc(hFunc) {
        this->count = 0;
        this->dataArray = new list<Record<Key, Data>>[_size];
    }

    void Add(Key key, Data data) {
        Record<Key, Data> temp;
        temp.data = data;
        temp.key = key;
        int i = this->HashFunc(key) % this->size;
        this->dataArray[i].push_back(temp);
        this->count++;
    }

    Data Find(Key key) {
        {
            int k = this->HashFunc(key) % this->size;
            Data data;
            bool found = false;

            for (auto& x : this->dataArray[k])
            {
                if (x.key == key)
                {
                    found = true;
                    data = x.data;
                }
            }

            if (found) return data;
            else throw "not found";
        }
    }

    void Delete(Key key) {
        int k = this->HashFunc(key) % this->size;

        for (auto x = this->dataArray[k].begin(); x != this->dataArray[k].end(); x++)
        {
            if (x->key == key)
            {
                this->dataArray[k].erase(x);
                this->count--;
                break;
            }
        }      
    }

    Data operator[](const Key& key) {
        return this->Find(key);
    }
};
