
/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers, 
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

				The Node: item of type T and a "next" pointer
					------------- 
					| item| next | --->
					-------------
General Queue case:

                 frontPtr																backPtr
					\											   						/		
					 \											  					   /		
					------------- 	  ------------- 	  ------------- 	  ------------- 	  	  
					| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
					------------- 	  ------------- 	  ------------- 	  -------------	  
		
Empty Case:

                 frontptr	 backptr
						\	 /				
						 \	/				
					---- NULL ------


Single Node Case:
                 frontPtr	 backPtr
					\		/	
					 \	   /			
					----------- 	
					|item| next| -->NULL
					-----------	

*/

#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include <iostream>
using namespace std;
#include "Node.h"
#include "QueueADT.h"

template <typename T>
class LinkedQueue:public QueueADT<T>
{
private :
	Node<T>* backPtr;
	Node<T>* frontPtr;
	int count;
public :
	LinkedQueue();	
	LinkedQueue(const LinkedQueue<T>& queue2);
	bool isEmpty() const ;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);  
	bool peek(T& frntEntry)  const;	
	void print() const;
	int getCount() const;
	~LinkedQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr=nullptr;
	frontPtr=nullptr;
	count = 0;
}
template<typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& queue2)
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;
	if (queue2.frontPtr)
	{
		Node<T>* current = queue2.frontPtr;
		while (current)
		{
			enqueue(current->getItem());
			current = current->getNext();
		    count++;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr==nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::enqueue( const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	count++;
	return true ;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>:: dequeue(T& frntEntry)  
{
	if(isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr ;	
		
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
bool LinkedQueue<T>:: peek(T& frntEntry) const 
{
	if(isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
template<typename T>
inline void LinkedQueue<T>::print() const
{
	Node<T> *ptr = frontPtr;
	while (ptr)
	{
		cout << ptr->getItem();
		if (ptr->getNext())
			cout << ", ";
		ptr = ptr->getNext();
	}

}
template<typename T>
inline int LinkedQueue<T>::getCount() const
{
	return count;
}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	//Note that the cout statements here is just for learning purpose
	//They should be normally removed from the destructor
//	cout<<"\nStarting LinkedQueue destructor...";
	//cout<<"\nFreeing all nodes in the queue...";

	//Free all nodes in the queue
	T temp;
	while(dequeue(temp));
	
	//cout<<"\n Is LinkedQueue Empty now?? ==> "<<boolalpha<<isEmpty();
	//cout<<"\nEnding LinkedQueue destructor..."<<endl;
}

#endif