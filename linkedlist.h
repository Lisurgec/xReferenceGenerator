#pragma once

#include "node.h"

class linkedList{
	public:
		node* head;

		linkedList();
		~linkedList();
		node* find(int data);
		void add(int added);
		void remove(int data);
		void insert(node* newNode, int pos);
		void print();
};