
#include <cstdlib>
#include<iostream>

#include "LinkedList.cpp"
#include<cmath>

using namespace std;

int menu();

template<class T> 
void coefficient(LinkedList<T>& P);


template <class T>
void shift_graph(LinkedList<T>& P);

template <class T>
void add_term(LinkedList<T>& P);

template <class T>
void vertex(LinkedList<T>& P);

template <class T>
void quad_roots(LinkedList<T>& P);

template <class T>
void product(LinkedList<T>& P1, LinkedList<T>& P2);


template <class T>
LinkedList<T> sum(LinkedList<T>& P1, LinkedList<T>& P2);

template <class T>
void copy_temp(LinkedList<T>&temp,LinkedList<T>& final_poly);
template <class T>
void add_into(LinkedList<T>& P1, LinkedList<T>& P2);


int main()
{
 

cout << "Details for polynomial 1 \n\n";


LinkedList<int> Polynomials2;

int bagain = 10;

	
while(bagain != 5)
{
	bagain = menu();

	if(bagain == 1){add_term(Polynomials2);		}
	else if (bagain == 2) {quad_roots(Polynomials2); }
	else if(bagain == 3) {vertex(Polynomials2);}
	else if(bagain == 4) {coefficient(Polynomials2);}
	else if(bagain == 6) {shift_graph(Polynomials2);}

}

Polynomials2.Print_List();
cout << endl;;

cout << endl;

LinkedList<int> Polynomials1;

int again = 10;

cout << "Details for polynomial 2 \n\n";
while(again != 5)
{
	again = menu();

	if(again == 1){add_term(Polynomials1);		}
	else if (again == 2) {quad_roots(Polynomials1); }
	else if(again == 3) {vertex(Polynomials1);}
	else if(again == 4) {coefficient(Polynomials1);}
	else if(again == 6) {shift_graph(Polynomials1);}

}



//LinkedList<int> one = sum(Polynomials2,Polynomials1);
//one.Print_List();
cout << "The sum of the two polynomials is "; sum(Polynomials1,Polynomials2);

cout << endl;
cout << endl;
cout << "The product of the two polynomials is "; product(Polynomials1,Polynomials2);

}



template <class T>
void add_into(LinkedList<T>& P1, LinkedList<T>& P2)
{

		
	int result;

	ListItem<T>* hopper1 = P1.Get_Tail();
	ListItem<T>* hopper2 = P2.Get_Tail();

		

	while(hopper2 != P2.Get_Head()->prev)
	{
		hopper1->value = hopper2->value + hopper1->value;
	
		hopper1 = hopper1->prev;
		hopper2 = hopper2->prev;
	}
	

}

int menu()
{
	int answer;
	cout << "1 - Add another term\n"; // add_term
	cout << "2 - Return roots  (Only if quadratic)\n"; // quad_roots;
	cout << "3 - vertex of quadratic polynomial\n"; // vertex
	cout << "4 - Return coefficient of given exponent\n";
	cout << "5 -Exit\n";	// Do product add_into sum
	cout << "6 - Shift the graph\n"; // shift
	
	
	cin >> answer;
	return answer;

}
template <class T>
void shift_graph(LinkedList<T>& P)
{

cout << "Right now this polynomial is: ";
P.Print_List();
cout << endl;

int holder;

cout << "Shift across x(Press 1) or Y(Press 2): " << endl;

cin >> holder;

if(holder == 1)
	{
		int how_much;
		cout << "How much do you want to shift (Positive for leftwards & Negative for rightwards" << endl;
		cin >> how_much;

		ListItem<T>* holder = P.Get_Head();

		while(holder != P.Get_Tail()->next)
			{	

				holder->value = holder->value + how_much;	
				holder = holder->next;

			}
		cout << "After shifting, this this polynomial is: " << endl; 
		P.Print_List();
		cout << endl; 

	} 

else if (holder == 2)
	{	

		int how_much;
		cout << "How much do you want to shift (Positive for upwards & Negative for downards" << endl;
		cin >> how_much;

		P.Get_Tail()->value = P.Get_Tail()->value + how_much;

		cout << "After shifting, this this polynomial is: " << endl; 
		P.Print_List();
		cout << endl; 



	}


else{cout << "Invalid entry"; return;}
}
template <class T>
void add_term(LinkedList<T>& P)
{

int term = 0;
cout << "Enter coefficient for " << P.Get_Length() <<"th exponent\n";
cin >> term;
P.Insert_at_Head(term);

}

template <class T>
void vertex(LinkedList<T>& P){
if((P.Get_Length() != 3) || (P.Tail_Element()==0)) 

		{
			cout << "Not quadratic\n"; 
			return;
		}

double x, y;
	x = -(P.Get_Head()->next->value)/ (2*(P.Get_Head()->value));
	y = (P.Get_Head()->value)*(pow(x,2)) + (P.Get_Head()->next->value)*x + P.Get_Tail()->value;

	cout << "Vertex co-ordinates are\n";
	cout << "X : " << x << endl;
	cout << "Y : " << y << endl;

}

template<class T>
void quad_roots(LinkedList<T>& P)
{

	
	if((P.Get_Length() != 3) || (P.Tail_Element()==0)) 

		{
			cout << "Not quadratic\n"; 
			return;
		}
   	
   double a, b, c;
   a = P.head->next->value;
   b = P.head->next->next->value;
   	c = P.head->next->next->next->value;
   double root1 = (-b + (sqrt((b*b)-(4*a*c))))/(2*a);
   double root2 = (-b - (sqrt((b*b)-(4*a*c))))/(2*a);
   
   cout << root1 << endl;
   
   cout << root2 << endl;
	
}

template <class T>
void product(LinkedList<T>& P1, LinkedList<T>& P2)
{

	int no_of_zeros = 0;

	ListItem<T>* hopper = P1.Get_Tail();
	LinkedList<T> final_poly;
	while(hopper != P1.Get_Head()->prev)
		{	
			int counter = 0;
			LinkedList<T> temp;

			while(counter < no_of_zeros)
			{
				temp.Insert_at_Head(0);
				counter++;
			}

			double multiplier = hopper->value;
			
			ListItem<T>* iter_list2 = P2.Get_Tail();

				while(iter_list2 != P2.Get_Head()->prev)
				{

					double value_holder = multiplier * iter_list2->value;
					temp.Insert_at_Head(value_holder);
					iter_list2 = iter_list2->prev;
				}
		//	temp.Print_List();	
			add_into(temp, final_poly);
			copy_temp(temp,final_poly);
			hopper = hopper->prev;

			no_of_zeros++;
		}
		final_poly.Print_List();
}


template <class T>
LinkedList<T> sum(LinkedList<T>& P1, LinkedList<T>& P2)
{

	LinkedList<T> Sum;
	
	int result;

	ListItem<T>* hopper1 = P1.Get_Tail();
	ListItem<T>* hopper2 = P2.Get_Tail();

	while((hopper1 != P1.Get_Head()->prev) && (hopper2 != P2.Get_Head()->prev))
		{

		result = hopper1->value + hopper2->value;
		//hopper1->value = result;
		Sum.Insert_at_Head(result);  	
		hopper1 = hopper1->prev;
		hopper2 = hopper2->prev;
		}	
		
	while(hopper1 != P1.Get_Head()->prev)
	{
		result = hopper1->value;
		//hopper1->value = result;
		Sum.Insert_at_Head(result);
		hopper1 = hopper1->prev;
	}

	while(hopper2 != P2.Get_Head()->prev)
	{
		result = hopper2->value;
		Sum.Insert_at_Head(result);
		//hopper1->value = result;
		hopper2 = hopper2->prev;
	}
	Sum.Print_List();
	return Sum;
}


template <class T>
void copy_temp(LinkedList<T>&temp,LinkedList<T>& final_poly)
{

	T value_h;
	ListItem<T>* delete_hopper = final_poly.Get_Head();
	while(delete_hopper != final_poly.Get_Tail()->next)
	{
		final_poly.Delete_Head();
		delete_hopper = delete_hopper->next;
	}

	ListItem<T>* temp_hopper = temp.Get_Tail();
	while(temp_hopper != temp.Get_Head()->prev)
	{
		value_h = temp_hopper->value;
		final_poly.Insert_at_Head(value_h);
		temp_hopper = temp_hopper->prev;
	}

}


template<class T> 
void coefficient(LinkedList<T>& P)

{

cout << "Enter exponent power for which you need the coefficient\n";
int exp ;
cin >> exp;

if(exp > P.Get_Length()-1)
{
	cout << "Out of bound;" << endl;
	return;
}
	int counter = 0;
	ListItem<T>* hopper = P.Get_Tail();
	while(counter < exp)
	{
		hopper = hopper->prev;
		counter++;
	}

	int v = hopper->value;
	cout << "Coefficient for " << exp << " exponent is " << v << endl;
}

