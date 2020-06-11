#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{
	// Nothing to intitialize;

}
    
template <class T>
Queue<T>::Queue(const Queue<T>& otherQueue)
{
// Copy constructor of LinkedList does the job since we're storing everything in the linkedlist

}

template <class T>
Queue<T>::~Queue()
{



}

template <class T>
void Queue<T>::Enqueue(T item)
{

	list.Insert_at_Tail(item);

}

template <class T>
T Queue<T>::Get_Front()
{
return list.Get_Head()->value;
}

template <class T>
T Queue<T>::Dequeue()
{
	if(Is_Empty()){cout << "Nothing to remove;"; exit(1);}
	T element = list.Get_Head()->value;

	list.Delete_Head();
	return element;
}

template <class T>
int Queue<T>::Get_Length()
{
	return list.Get_Length();
}

template <class T>
bool Queue<T>::Is_Empty()
{
return (list.Get_Length()==0);
}









#endif
