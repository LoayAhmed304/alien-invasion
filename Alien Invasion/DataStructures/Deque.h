#ifndef DEQUE_H
#define DEQUE_H

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
	int count;
public:
	Deque();
	bool isEmpty() const;
	int length() const;
	bool enqueue(const T& newEntry);
	bool enqueueFront(const T& newEntry);
	bool dequeue(T& RearEntry);
	bool dequeueRear(T& FrontEntry);
	bool peek(T& FrontEntry) const;
	bool peekRear(T& RearEntry) const;
	void printAll() const;
	~Deque();
};
#endif

template<typename T>
Deque<T>::Deque()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;
}

template<typename T>
bool Deque<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

template<typename T>
int Deque<T>::length() const
{
	return count;
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

	++count;
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

	++count;
	frontPtr = newNodePtr;
	return true;
}

template<typename T>
bool Deque<T>::dequeue(T& FrontEntry)
{
	if (isEmpty())
		return false;

	dequeNode<T>* temp = frontPtr;
	FrontEntry = temp->getItem();
	frontPtr = frontPtr->getNext();
	if (temp == backPtr)	 // Special case: last node in the queue
	{
		backPtr = nullptr;
		--count;
		delete temp;
		return true;
	}

	frontPtr->setPrev(nullptr);
	--count;
	delete temp;
	return true;
}

template<typename T>
bool Deque<T>::dequeueRear(T& RearEntry)
{
	if (isEmpty())
		return false;

	dequeNode<T>* temp = backPtr;
	RearEntry = temp->getItem();
	backPtr = backPtr->getPrev();

	if (temp == frontPtr)	 // Special case: last node in the queue
	{
		frontPtr = nullptr;
		--count;
		delete temp;
		return true;
	}

	backPtr->setNext(nullptr);
	--count;
	delete temp;
	return true;
}

template<typename T>
bool Deque<T>::peek(T& FrontEntry) const
{
	if (isEmpty())
		return false;
	FrontEntry = frontPtr->getItem();
	return true;
}

template<typename T>
inline bool Deque<T>::peekRear(T& RearEntry) const
{
	if (isEmpty())
		return false;
	RearEntry = backPtr->getItem();
	return true;
}

template<typename T>
void Deque<T>::printAll() const
{
	if (!frontPtr)
		return;

	dequeNode<T>* temp = frontPtr;
	cout << temp->getItem();
	temp = temp->getNext();

	while (temp)
	{
		cout << ", " << temp->getItem();
		temp = temp->getNext();
	}
}

template<typename T>
Deque<T>::~Deque()
{
	T tst;
	while (dequeue(tst));
}
