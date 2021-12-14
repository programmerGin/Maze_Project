#pragma once
#include "Node.h"

class LinkedQueue {
	Node* front;
	Node* rear; 

public:

	LinkedQueue() :front(NULL) {}
	~LinkedQueue() { while (!isEmpty())delete dequeue(); }

	bool isEmpty() { return front == NULL; }

	void enqueue(Node* p) {
		if (isEmpty())front = rear = p;//처음 p 는 rear
		else {
			rear->setLink(p);
			rear = p;
		}
	}

	Node* dequeue() {
		if (isEmpty())return NULL;
		Node* p = front;
		front = front->getLink();
		if (front == NULL)rear = NULL;
		return p;
	}

	Node* peek() { return front; }

	void display() {
		printf("[큐 내용]:");
		for (Node* p = front; p != NULL; p = p->getLink())
			p->display();
		printf("\n");
	}

};
class LinkedStack {
	Node* top;
public:
	LinkedStack() { top = NULL; }
	~LinkedStack() { while (!isEmpty()) delete pop(); }
	bool isEmpty() { return top == NULL; }
	void push(Node* p) {
		if (isEmpty()) top = p;
		else {
			p->setLink(top);
			top = p;
		}
	}
	Node* pop() {
		if (isEmpty()) return NULL;
		Node* p = top;//처음 p 는 top
		top = top->getLink();
		return p;
	}
	Node* peek() { return top; }
	void display() {
		printf("[LinkedStack]\n");
		for (Node* p = top; p != NULL; p = p->getLink())
			printf("[%d %d] ", p->row, p->col);
		printf("\n");
	}
};