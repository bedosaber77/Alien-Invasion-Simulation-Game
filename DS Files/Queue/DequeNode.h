template <typename T>
class DequeNode
{
private:
	T item; // A data item
	DequeNode<T>* next; // Pointer to next DequeNode
	DequeNode<T>* previous; // Pointer to previous DequeNode
public:
	DequeNode();
	DequeNode(const T& r_Item);
	DequeNode(const T& r_Item, DequeNode<T>* nextNodePtr);
	DequeNode(const T& r_Item, DequeNode<T>* nextNodePtr, DequeNode<T>* previousNodePtr);
	void setItem(const T& r_Item);
	void setNext(DequeNode<T>* nextNodePtr);
	void setPrevious(DequeNode<T>* previousNodePtr);
	T getItem() const;
	DequeNode<T>* getNext() const;
	DequeNode<T>* getPrevious() const;
}; // end DequeNode

template < typename T>
DequeNode<T>::DequeNode()
{
	next = nullptr;
	previous = nullptr;
}

template < typename T>
DequeNode<T>::DequeNode(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
	previous = nullptr;
}

template < typename T>
DequeNode<T>::DequeNode(const T& r_Item, DequeNode<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
	previous = nullptr;
}
template<typename T>
inline DequeNode<T>::DequeNode(const T& r_Item, DequeNode<T>* nextNodePtr, DequeNode<T>* previousNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
	previous = previousNodePtr;
}
template < typename T>
void DequeNode<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void DequeNode<T>::setNext(DequeNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}
template<typename T>
inline void DequeNode<T>::setPrevious(DequeNode<T>* previousNodePtr)
{
	previous = previousNodePtr;
}


template < typename T>
T DequeNode<T>::getItem() const
{
	return item;
}

template < typename T>
DequeNode<T>* DequeNode<T>::getNext() const
{
	return next;
}
template<typename T>
inline DequeNode<T>* DequeNode<T>::getPrevious() const
{
	return previous;
}