#pragma once

#include "reference.h"

#include <random>
#include <thread>
using namespace std;

template <class T>
class hashtable{
	
private:
	int size;
	int numItems;

	T* hashTable; //The hash table itself
	T* nextTable; //We calculate this on every rehash - maybe on a seperate thread
	
	unsigned int hashFunction(string input, int storeSize){
		 unsigned int hashval = 0;
		 char str = input[0];
		 for(size_t i = 0; i < input.length(); i++){
				  hashval += input[i];
		 }
			return hashval % storeSize;
	};

	bool isAPrime(int num){
		//Check if it's even
		if (num % 2 != 0){
			//Check if it's divisible by anything else
			for(int i = 3; i < num / 2; i += 2){
				if( (num % i) == 0){
					return false;
				}
			}
		}
		else{
			return false;
		}
		return true;
	}; 

	int _nextSize(int start, int next, int max){
	
		if ((start+next) > max){
			if(isAPrime(start+next)){
				return start+next;
			}
			else{
				return _nextSize(next,(start+next), max);
			}
		}
		else
		{
			return _nextSize(next,(start+next), max); 
		}
	};
	int nextSize(){
		return _nextSize(1, 2, size);
	};
	void rehash(){
		int newSize = nextSize();
		nextTable = new T[newSize];
		for(int i = 0; i < size; i++){
			if (hashTable[i] != ""){
				//Through some black magic, this sorts the test data.  Look into it.
				nextTable[hashFunction(hashTable[i], newSize)] = hashTable[i]; 
			}

			}
		
		size = newSize;
		hashTable = nextTable;
		
	}; 

public:
	hashtable<T>(){
		size = 257;
		T table[257];
		hashTable = table;
		numItems = 0;
	};
	hashtable<T>(int _size){
		//Rounds up to the next fibonacci prime
		size = _size;
		int sizeN = nextSize();
		size = sizeN;
		T* table = new T[sizeN];
		hashTable = table;
		numItems = 0;
	};
	T operator[](string key){
		if (contains(key)){
			return hashTable[hashFunction(key,size)];
		}
		else{
			return nullptr;
		}
	};
	T operator[](int iter){
		return hashTable[i];
	}
	void insert(T item){
		int key;
		try{
			key = hashFunction(item.name, size);
		}
		catch(exception e){
			key = hashFunction(item, size);
		}
		while(hashTable[key] != ""){
			//Probing here
			key++;
			if (key > size-1){
				key = 0;
				}
			}
			hashTable[key] = item;
			numItems++;
			//If it's 70% full, we need to rehash
			if((numItems / (float) size) >= 0.7){
				rehash();
			}
			
		};
	//template<class string> void insert(string item){
	//	int key = myHash(item, size);
	//	while(hashTable[key] != ""){
	//		//Probing here
	//		key++;
	//		if (key > size-1){
	//			key = 0;
	//			}
	//		}
	//		hashTable[key] = item;
	//		numItems++;
	//		//If it's 70% full, we need to rehash
	//		if((numItems / (float) size) >= 0.7){
	//			rehash();
	//		}
	//		
	//	};
	void remove(string key){
		hashTable[hashFunction(key, size)] = "";
	};
	bool contains(string key){
		return (hashTable[hashFunction(key, size)] == key);
	};
	void print(){
		cout << "{";
		for (int i = 0; i < size; i++){
			if(hashTable[i] != ""){
				cout << hashTable[i] << ", ";
			}
		}
		cout << "\b\b}" << endl;
	};
	string stats(){
		return "Size: " + to_string(size) + " Load: " + to_string((numItems/(float) size) * 100) + "%";
	};
};
	////Creates an empty hash table
	//template <class T>
	//hashtable::hashtable<T>();
	//
	////Creates a specific sized table
	//template <class T>
	//hashtable::hashtable<T>(int _size);
	//
	////This is collision prone, and should be updated
	//template <class T>
	//unsigned int hashtable::hashFunction(string input, int storeSize);
	//
	////Checks if a number is prime
	//template <class T>
	//bool hashtable::isAPrime(int num);
	//
	////Recursively generates numbers until it's greater than our current size AND prime.
	//template <class T>
	//int hashtable::_nextSize(int start, int next, int max);
	//
	////Recursion handler
	//template <class T>
	//int hashtable::nextSize();
	//
	////Inserts everything from hashTable into nextTable, then changes *hashTable
	//template <class T>
	//void hashtable::rehash();
	//
	//Insert an item into the table
	//template <typename string>
	//void hashtable::insert(string item);

	////Insert an item into the table
	//template <class T>
	//void hashtable::insert(T item);
	//
	////Removes an item from the table
	//template <class T>
	//void hashtable::remove(string key);
	//
	////True if the item is in the table
	//template <class T>
	//bool hashtable::contains(string key);

	//template <class T>
	//T hashtable::operator[](string key);
	//
	////Outputs the hashtable items
	//template <class T>
	//void hashtable::print();

	//template <class T>
	//string hashtable::stats();
