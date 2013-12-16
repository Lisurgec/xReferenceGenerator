#pragma once

class node{
	public: 
		int data;
		node* prev;
		node* next;

		~node();
		node();
		node(int _data);
		void setData(int _data);
		int getData();
		void print();
};