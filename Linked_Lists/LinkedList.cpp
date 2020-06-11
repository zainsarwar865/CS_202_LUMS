
#include <cstdlib>
#include<iostream>
#include "LinkedList.h"
#include<cmath>

using namespace std;
template <class T>
LinkedList<T>::LinkedList()
{

 head = new ListItem<T>(); // Sentinel 
 tail = new ListItem<T>(); // Sentinel
 head->next = tail;
 tail->prev = head;
 head->prev = NULL;
 tail->next = NULL;
 len = 0;

}


template<class T>
T LinkedList<T>::Tail_Element()
{
	return tail->prev->value;


}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{

	ListItem<T>* hopper = otherLinkedList.head->next;
	while(hopper != tail)
	{
		ListItem<T>* temp = new ListItem<T>(hopper->value);
		temp->next = temp->prev->next;
		temp->prev = temp->next->prev;
		temp->prev->next = temp;
		temp->next->prev = temp;
		hopper = hopper->next;
		len++;
		// Add len??
	}

}

template <class T>
LinkedList<T>::~LinkedList()
{

	while(Get_Length()!= 0)
		{	
			Delete_Head(); // Could be Delete_Tail as well


		}

		delete head;
		delete tail;

}

template <class T>
void LinkedList<T>::Insert_at_Head(T item)
{

	ListItem<T>* temp = new ListItem<T>(item);
	temp->next = head->next;
	temp->prev = head->next->prev;
	head->next = temp;
	temp->next->prev = temp;
	len++;

}

template <class T>
void LinkedList<T>::Insert_at_Tail(T item)
{

	ListItem<T>* temp = new ListItem<T>(item);
	temp->next = tail;
	temp->prev = tail->prev;
	tail->prev = temp;
	temp->prev->next = temp;
	len++;
}

template <class T>
void LinkedList<T>::Insert_After(T toInsert, T afterWhat)
{

	// Insert after particular value?? or node?

	ListItem<T>* hopper = head->next;
	while(hopper->value != afterWhat && (hopper != tail))
		{	
			hopper = hopper->next;
		}

		if(hopper == tail) {std::cout << "Element to be inserted after not found\n"; return ;}

		ListItem<T>* temp = new ListItem<T>(toInsert);
		temp->next = hopper->next;
		temp->prev = hopper->next->prev;
		hopper->next = temp;
		temp->next->prev = temp;
		len++;
}


template <class T>
ListItem<T>* LinkedList<T>::Get_Head()
{
	return head->next; // // Not done
}

template <class T>
ListItem<T>* LinkedList<T>::Get_Tail()
{
	return tail->prev; // Not done
}

template <class T>
ListItem<T>* LinkedList<T>::Search_For_Element(T item)
{
	ListItem<T>* finder = head->next;
	while(finder->value!= item && (finder != tail))
		{
		finder = finder->next;	
		}
		if(finder == tail) {std::cout << "Element not found"; return NULL;}
		return finder;
}

template <class T>
ListItem<T>* LinkedList<T>::Get_Min()
{
	T temp_min = head->next->value;
	ListItem<T>* hopper = head->next;
	ListItem<T>* min;
	while(hopper != tail->prev)
		{	

			if(hopper->value < temp_min)
				{	
					temp_min = hopper->value;
					min = hopper;
				}
			hopper = hopper->next;		
		}
		return min;

}

template <class T>
ListItem<T>* LinkedList<T>::Get_Max()
{

	T temp_max = head->next->value;
	ListItem<T>* hopper = head->next;
	ListItem<T>* max;
	while(hopper != tail->prev)
		{	

			if(hopper->value > temp_max)
				{	
					temp_max = hopper->value;
					max = hopper;
				}
			hopper = hopper->next;		
		}
		return max;

}

template <class T>
void LinkedList<T>::Delete_Element(T item)
{
	ListItem<T>* delete_this = head->next;
	while(delete_this->value != item & delete_this != tail)
		{	
			delete_this = delete_this->next;
		}
		if(delete_this == tail) {std::cout << "Not found "; return;}

	delete_this->next->prev = delete_this->prev;
	delete_this->prev->next = delete_this->next;
	delete delete_this; 	
	len--;
}


template <class T>
void LinkedList<T>::Delete_Head()
{
	if(len==0) {cout << "Nothing to delete"; return;}

		ListItem<T>* delete_this = head->next;
		delete_this->next->prev = head;
		head->next = delete_this->next;
		delete delete_this;
		len--;

}

template <class T>
void LinkedList<T>::Delete_Tail()
{

	if(len==0) {cout << "Nothing to delete"; return;}
	ListItem<T>* delete_this = tail->prev;
	delete_this->prev->next = tail;
	tail->prev = delete_this->prev;
	delete delete_this;
	len--;

}

template <class T>
int LinkedList<T>::Get_Length()
{
	
	return len;
}


template <class T>
void LinkedList<T>::Reverse_List()
{


ListItem<T>* hopper = head->next;

ListItem<T>* holder;



while(hopper != tail)
    {



        holder = hopper->next;
        hopper->next = hopper->prev;
  
       hopper->prev = holder;

      hopper = hopper->prev;
    }

head->prev = head->next;
//head->next = NULL;

tail->next = tail->prev;
   tail->prev = NULL;
holder = head;
head = tail;
tail = holder;

}

template <class T>
void LinkedList<T>::Print_List()

{

ListItem<T>* hopper = head->next;
while(hopper!= tail)
{
	cout << hopper->value << "  ";
	hopper = hopper->next;
}
cout << endl;


}
