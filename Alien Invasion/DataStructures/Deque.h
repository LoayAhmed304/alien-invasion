#pragma once

#include "dequeNode.h"
#include "QueueADT.h"

#include <iostream>
using namespace std;

template < typename T>
class Deque : public QueueADT<T>
{
private:
	dequeNode<T>* backPtr;
	dequeNode<T>* frontPtr;
public:
	Deque();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool enqueueFront(const T& newEntry);
	bool dequeueFront(T& FrontEntry);
	bool dequeue(T& RearEntry);
	bool peek(T& FrontEntry) const;
	bool peekRear(T& RearEntry) const;
	void printAll() const;
	~Deque();
};

template<typename T>
Deque<T>::Deque()
{
	backPtr = nullptr;
	frontPtr = nullptr;
}

template<typename T>
bool Deque<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

template<typename T>
bool Deque<T>::enqueue(const T& newEntry)
{
	dequeNode<T>* newNodePtr = new dequeNode<T>(newEntry);
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
	{
		newNodePtr->setPrev(backPtr);
		backPtr->setNext(newNodePtr); // The queue was not empty
	}
	
	backPtr = newNodePtr;
	return true;
}

template<typename T>
bool Deque<T>::enqueueFront(const T& newEntry)
{
	dequeNode<T>* newNodePtr = new dequeNode<T>(newEntry);

	if (isEmpty())	//special case if this is the first node to insert
		backPtr = newNodePtr; // The queue is empty
	else
	{
		newNodePtr->setNext(frontPtr);
		frontPtr->setPrev(newNodePtr); // The queue was not empty
	}

	frontPtr = newNodePtr;
	return true;
}

template<typename T>
bool Deque<T>::dequeueFront(T& FrontEntry)
{
	if (isEmpty())
		return false;

	dequeNode<T>* temp = frontPtr;
	FrontEntry = temp->getItem();
	frontPtr = frontPtr->getNext();
	if (temp == backPtr)	 // Special case: last node in the queue
	{
		backPtr = nullptr;
		delete temp;
		return true;
	}
	frontPtr->setPrev(nullptr);


	delete temp;
	return true;
}

template<typename T>
bool Deque<T>::dequeue(T& RearEntry)
{
	if (isEmpty())
		return false;
	
	dequeNode<T>* temp = backPtr;
	RearEntry = temp->getItem();
	backPtr = backPtr->getPrev();
	
	if (temp == frontPtr)	 // Special case: last node in the queue
	{
		frontPtr = nullptr;
		delete temp;
		return true;
	}

	backPtr->setNext(nullptr);

	delete temp;
	return true;
}

template<typename T>
bool Deque<T>::peek(T& FrontEntry) const
{
	FrontEntry = frontPtr->getItem();
	return true;
}

template<typename T>
inline bool Deque<T>::peekRear(T& RearEntry) const
{
	RearEntry = backPtr->getItem();
	return true;
}

template<typename T>
void Deque<T>::printAll() const
{
	if (!frontPtr)
		return;

	dequeNode<T>* temp = frontPtr;

	while (temp)
	{
		cout << temp->getItem() << endl;
		temp = temp->getNext();
	}
}

template<typename T>
Deque<T>::~Deque()
{
	T tst;
	while (dequeueFront(tst));
}
