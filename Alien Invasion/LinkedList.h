#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		Node<T>* p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
			Head = nullptr;
		}
	}

	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data)
	{
		if (!Head)
			InsertBeg(data);
		else
		{
			Node<T>* P = Head;
			Node<T>* R = new Node<T>(data);
			while (P->getNext())
			{
				P = P->getNext();
			}
			P->setNext(R);
		}
	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(int Key)
	{
		Node<T>* P = Head;
		while (P)
		{
			if (P->getItem() == Key)
			{
				return true;
			}
			P = P->getNext();
		}
		return false;
	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value)
	{
		int count = 0;
		Node<T>* P = Head;
		while (P)
		{
			if (P->getItem() == value)
			{
				count++;
			}
			P = P->getNext();
		}
		return count;
	}

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst()
	{
		Node<T>* P = Head;
		Head = Head->getNext();
		delete P;
		P = nullptr;
	}


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast()
	{
		if (!Head || !Head->getNext())
		{
			delete Head;
			Head = nullptr;
			return;
		}
		Node<T>* P = Head;
		while (P->getNext()->getNext())
		{
			P = P->getNext();
		}
		delete P->getNext();
		P->setNext(nullptr);
	}

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& value)
	{
		if (!Head)
			return false;
		Node<T>* P1 = Head;
		Node<T>* P2 = nullptr;
		if (P1->getItem() == value)
		{
			Head = P1->getNext();
			delete P1;
			return true;
		}
		while (P1)
		{
			if (P1->getItem() == value)
			{
				if (P2)
					P2->setNext(P1->getNext());
				delete P1;
				return true;
			}
			P2 = P1;
			P1 = P1->getNext();
		}
		return false;
	}


	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value)
	{
		bool found = false;
		Node<T>* P1 = Head;
		Node<T>* P2 = nullptr;
		while (P1)
		{
			if (P1->getItem() == value)
			{
				found = true;
				if (P2)
				{
					P2->setNext(P1->getNext());
					delete P1;
					P1 = P2;
					P1 = P1->getNext();

				}
				else
				{
					Head = Head->getNext();
					delete P1;
					P1 = Head;
				}
			}
			else
			{
				P2 = P1;
				P1 = P1->getNext();
			}
		}
		return found;
	}

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(const LinkedList& L)
	{
		Node<T>* P = Head;
		while (P->getNext())
		{
			P = P->getNext();
		}
		P->setNext(L.Head);
	}

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse()
	{
		if (!Head)
			return;
		Node<T>* cptr1 = Head;
		Node<T>* cptr2 = Head->getNext();
		Head = nullptr;
		while (cptr2)
		{
			cptr1->setNext(Head);
			Head = cptr1;
			cptr1 = cptr2;
			cptr2 = cptr2->getNext();
		}
		cptr1->setNext(Head);
		Head = cptr1;
	}

};

#endif	
