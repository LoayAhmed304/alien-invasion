#pragma once
#include "Node.h"
using namespace std;
template< class T>
class Stack
{
private:
	Node<T>* topPtr;
public:
	Stack()
	{
		topPtr = nullptr;
	}
	bool isEmpty()
	{
		return topPtr == nullptr;
	}
	bool push(const T& Item)
	{
		Node<T>* Ptr = new Node<T>(Item);
		Ptr->setNext(topPtr);
		topPtr = Ptr;
		return true;
	}
	bool pop()
	{
		if (!topPtr)
			return false;
		else
		{
			Node<T>* Ptr = topPtr;
			topPtr = topPtr->getNext();
			delete Ptr;
			return true;
		}
	}
	T peek() 
	{
		if (!topPtr)
		{
			return T();
		}
		else
			return topPtr->getItem();
	}
};