#ifndef PRIQUEUE_H
#define PRIQUEUE_H

#include "priNode.h"
using namespace std;

//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class priQueue
{
    priNode<T>* head;
    int count = 0;
public:
    priQueue() : head(nullptr) {}

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

    //insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);

        if (head == nullptr || priority > head->getPri()) {

            newNode->setNext(head);
            head = newNode;
            ++count;
            return;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
        ++count;
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        --count;
        delete temp;
        return true;
    }

    bool peek(T& topEntry, int& pri) const {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        pri = head->getPri();
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int length() const
    {
        return count;
    }

    void printAll() const
    {
        if (!head)
            return;
        int pri;
        priNode<T>* temp = head;
        cout << temp->getItem(pri);
        temp = temp->getNext();
        while (temp)
        {
            cout <<", "<< temp->getItem(pri) ;
            temp = temp->getNext();
        }
    }
};
#endif