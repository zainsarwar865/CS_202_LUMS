
#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"
#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
using namespace std;



template <class T>
Stack<T>::Stack() 
{
// Nothing to intitialize;

}
    
template <class T>
Stack<T>::Stack(const Stack<T>& otherStack)
{
	ListItem<T>* hopper = otherStack.Get_Head();
	while(hopper != otherStack.Get_Tail->prev)
		{
			ListItem<T>* temp = new ListItem<T>(hopper->value);
			list.Insert_at_Head(temp);

		}
		//Not set last element to null since DoublyLinked Lst;

}

template <class T>
Stack<T>::~Stack()
{
	
	while(!Is_Empty())
		{	
		
		cout <<	Pop();
		
		}
}

template <class T>
void Stack<T>::Push(T item)
{

	list.Insert_at_Head(item);
	
}

template <class T>
T Stack<T>::Top()
{
	return (list.Get_Head()->value);
}


template <class T>
T Stack<T>::Pop()
{
	if(Is_Empty()) {cout << "Nothing to remove"; exit(1);}
	T temp = Top();
	list.Delete_Head();
	return temp;

}


template <class T>
int Stack<T>::Get_Length()
{
	return list.Get_Length();
}

template <class T>
bool Stack<T>::Is_Empty()
{

	return (list.Get_Length()==0);
}




#endif
