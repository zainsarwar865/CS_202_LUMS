#include <cstdlib>
#include<iostream>
#include "stack.cpp"
#include<cmath>

using namespace std;

int main()
{
	cout << "Reverse Char-wise(1) or String-wise(2)?" << endl;
	int which;
	cin >> which;
if(which == 1)
{
cout << "Reverse char-wise" << endl;


Stack<char> char_input;

ifstream chartext("text.txt");
char p;

while(!chartext.eof())
	{
		chartext.get(p);
		char_input.Push(p);

	}


chartext.close();

}

if(which==2)
{
cout << "Reverse String-wise" << endl;



Stack<string> string_input;

ifstream stringtext;
stringtext.open("text.txt");
string holder;

while(!stringtext.eof())
	{	
		stringtext >> holder;
		
		string_input.Push(holder);
		string_input.Push(" ");
		
		
		

	}


stringtext.close();

}

	}

