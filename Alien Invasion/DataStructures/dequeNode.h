#ifndef	DEQUENODE_H
#define DEQUENODE_H

template < typename T>
class dequeNode
{
private:
	T item;
	dequeNode<T>* prev; // Pointer to prev node
	dequeNode<T>* next; // Pointer to next node
public:
	dequeNode();
	dequeNode(const T& r_Item);
	dequeNode(const T& r_Item, dequeNode<T>* nextNodePtr);
	dequeNode(const T& r_Item, dequeNode<T>* nextNodePtr, dequeNode<T>* prevNodePtr);
	T getItem();
	void setItem(const T& r_Item);
	dequeNode<T>* getNext();
	void setNext(dequeNode<T>* nextNodePtr);
	dequeNode<T>* getPrev();
	void setPrev(dequeNode<T>* prevNodePtr);
};
#endif

template<typename T>
dequeNode<T>::dequeNode()
{
	prev = nullptr;
	next = nullptr;
}

template<typename T>
dequeNode<T>::dequeNode(const T& r_Item)
{
	item = r_Item;
	prev = nullptr;
	next = nullptr;
}

template<typename T>
dequeNode<T>::dequeNode(const T& r_Item, dequeNode<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
	prev = nullptr;
}

template<typename T>
dequeNode<T>::dequeNode(const T& r_Item, dequeNode<T>* nextNodePtr, dequeNode<T>* prevNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
	prev = prevNodePtr;
}

template<typename T>
T dequeNode<T>::getItem()
{
	return item;
}

template<typename T>
void dequeNode<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template<typename T>
dequeNode<T>* dequeNode<T>::getNext()
{
	return next;
}

template<typename T>
void dequeNode<T>::setNext(dequeNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template<typename T>
dequeNode<T>* dequeNode<T>::getPrev()
{
	return prev;
}

template<typename T>
void dequeNode<T>::setPrev(dequeNode<T>* prevNodePtr)
{
	prev = prevNodePtr;
}
