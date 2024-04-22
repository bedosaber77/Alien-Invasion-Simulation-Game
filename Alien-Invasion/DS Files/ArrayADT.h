#pragma once

#ifndef ARRAY_ADT_
#define ARRAY_ADT_

#include <iostream>
using namespace std;

template <typename T>
class ArrayADT
{
	enum { MAX_SIZE = 1000 };
private:
	T items[MAX_SIZE];    // Array of list items
	int count;             // count of list items
public:
	ArrayADT();
	bool isEmpty() const;
	bool insert(const T& newEntry);
	bool remove(T& removedEntry, int index);
	bool getItem(T& Entry, int index)  const;
	void print() const;
	int getCount() const;
	~ArrayADT();
};
//////////////////////////////////////////////////////////////////////////

/*
Function: ArrayADT
The constructor of the Array class.

*/

template<typename T>
inline ArrayADT<T>::ArrayADT()
{
	count = 0;
}

//////////////////////////////////////////////////////////////////////////
/*
Function: isEmpty
Sees whether this list is empty.

Input: None.
Output: True if the list is empty; otherwise false.
*/

template<typename T>
inline bool ArrayADT<T>::isEmpty() const
{
	return (count == 0);
}

//////////////////////////////////////////////////////////////////////////
/*Function:insert
Adds newEntry at the back of this list.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template<typename T>
inline bool ArrayADT<T>::insert(const T& newEntry)
{
	//if the array is full return false
	if (count == MAX_SIZE)
		return false;

	items[count++] = newEntry;
	return true;
}

//////////////////////////////////////////////////////////////////////////
/*Function: remove
removes the item with the given index

Input: index.
Output: True if the operation is successful; otherwise false.
*/

template<typename T>
inline bool ArrayADT<T>::remove(T& removedEntry, int index)
{
	if (isEmpty())
		return false;
	
	removedEntry = items[index];
	items[index] = items[count - 1];

	count--;
	return true;
}


//////////////////////////////////////////////////////////////////////////
/*Function: get
returns the item with the given index

Input: index.
Output: True if the operation is successful; otherwise false.
*/

template<typename T>
inline bool ArrayADT<T>::getItem(T& Entry, int index) const
{
	if(index >= count)
        return false;

	Entry = items[index];
}

//////////////////////////////////////////////////////////////////////////
/*Function: print
prints all the items in the array

Input: index.
Output: True if the operation is successful; otherwise false.
*/

template<typename T>
inline void ArrayADT<T>::print() const
{
	for (int i = 0; i < count; i++)
	{
		cout << items[i];
		if (i + 1 < count)
			cout << ", ";
	}

}

//////////////////////////////////////////////////////////////////////////

template<typename T>
inline int ArrayADT<T>::getCount() const
{
	return count;
}

template<typename T>
inline ArrayADT<T>::~ArrayADT()
{
	
}



#endif
