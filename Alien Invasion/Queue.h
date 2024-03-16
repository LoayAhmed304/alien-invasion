#pragma once
#include "Node.h"
using namespace std;
template< class T>
class Queue
{
private:
	Node<T>* topPtr;
	Node<T>* rearPtr;
public:
	Queue()
	{
		topPtr = nullptr;
		rearPtr = nullptr;
	}
	bool isEmpty()
	{
		return topPtr == nullptr;
	}
	bool push(const T& Item)
	{
		if (!topPtr)
		{
			Node<T>* R = new Node<T>(Item);
			R->setNext(topPtr);
			topPtr = R;
			rearPtr = R;
		}
		else
		{
			Node<T>* R = new Node<T>(Item);
			rearPtr->setNext(R);
			rearPtr = R;
		}
		return true;
	}
	bool pop()
	{
		if (!topPtr)
			return false;
		else
		{
			Node<T>* Ptr = topPtr;
			if (topPtr == rearPtr)
			{
				rearPtr = rearPtr->getNext();
			}
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
	T rear()
	{
		if (!rearPtr)
		{
			return T();
		}
		else
			return rearPtr->getItem();
	}
};