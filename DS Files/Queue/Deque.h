#pragma once
#include "DequeNode.h"
#include "QueueADT.h"
#include "iostream"
using namespace std;

template <typename T>
class Deque :public QueueADT<T>
{
private:
	DequeNode<T>* backPtr;
	DequeNode<T>* frontPtr;
	int count;
public:
	Deque();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool dequeueBack(T& backEntry);
	bool peek(T& frntEntry)  const;
	bool peekBack(T& BackEntry)  const;
	int getCount() const;
	void print();
	~Deque();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
Deque<T>::Deque()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool Deque<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool Deque<T>::enqueue(const T& newEntry)
{
	DequeNode<T>* newNodePtr = new DequeNode<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
	{
		backPtr->setNext(newNodePtr);
		newNodePtr->setPrevious(backPtr);
	} // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	count++;
	return true;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool Deque<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	DequeNode<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	frontPtr->setPrevious(nullptr);
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	count--;
	return true;
}

template<typename T>
 inline bool Deque<T>::dequeueBack(T& backEntry)
{
	if (isEmpty())
		return false;

	DequeNode<T>* nodeToDeletePtr = backPtr;
	backEntry = backPtr->getItem();
	backPtr = backPtr->getPrevious();
	backPtr->setNext(nullptr);
	// Queue is not empty; remove front
	if (nodeToDeletePtr == frontPtr)	 // Special case: last node in the queue
		frontPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	count--;
	return true;
}



/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/

template <typename T>
bool Deque<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
template<typename T>
 inline bool Deque<T>::peekBack(T& BackEntry) const
{
	if (isEmpty())
		return false;

	BackEntry = backPtr->getItem();
	return true;
}
template<typename T>
inline int Deque<T>::getCount() const
{
	return this->count;
}
template<typename T>
inline void Deque<T>::print()
{
	DequeNode<T>* ptr = frontPtr;
	while (ptr)
	{
		cout << ptr->getItem() << ' ';
		ptr = ptr->getNext();
	}
}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
Deque<T>::~Deque()
{
	//Note that the cout statements here is just for learning purpose
	//They should be normally removed from the destructor
	cout << "\nStarting LinkedQueue destructor...";
	cout << "\nFreeing all nodes in the queue...";

	//Free all nodes in the queue
	T temp;
	while (dequeue(temp));

	cout << "\n Is LinkedQueue Empty now?? ==> " << boolalpha << isEmpty();
	cout << "\nEnding LinkedQueue destructor..." << endl;
}
