#include "queue.cpp"
#include<iostream>
using namespace std;


template<class T>
void Queue_To_Stack(Queue<T> &one, Queue<T> &two, bool which)
{


	while((one.list.Get_Length() != 0 )|| (two.list.Get_Length() != 0 )) // both aren't empty
	{

	if(which)
	{

		
		while(one.list.Get_Length()!= 1) // one element left
				{	
					
					T temp = one.list.Get_Head()->value;
					one.Dequeue();
					two.Enqueue(temp);
				}
		
	}	
			
	
			if(which && one.list.Get_Length()!=0){cout << " Element removed is: " << one.Dequeue() << endl;}
			which = false;
		
		if(!which)		
	{		
	
	while(two.list.Get_Length()!= 1)	
		{	
			T temp = two.list.Get_Head()->value;
			two.Dequeue();
			one.Enqueue(temp);

		}

	if(!which && two.list.Get_Length()!=0){cout << "Element removed is: " << two.Dequeue()<< endl;}

		which = true;
	}
}


}


int main()
{

bool which = true;

Queue<int> one;
Queue<int> two;

one.Enqueue(1);
one.Enqueue(2);
one.Enqueue(3);
one.Enqueue(4);
one.Enqueue(5);
one.Enqueue(6);
one.Enqueue(7);
one.Enqueue(8);
Queue_To_Stack(one, two, which);

}




