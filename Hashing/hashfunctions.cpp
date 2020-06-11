#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 9)
{


//cout << "Enter polynomial term\n";
int term = a;
//cin >> term;
while(term == 1)
{
cout << "Term can't be 1\n";
cout << "Enter polynomial term\n";
cin >> term;

}
	
unsigned long len = value.length();
unsigned long hash_code = 0;

for(int i = 0; i < len;i++)
{

hash_code  = hash_code + (value[i] * pow(term,i)); 

}

return hash_code;
	
}




unsigned long bitHash(std::string value)
{
	unsigned long bth = 0;
	for(int i = 0; i < value.length();i++)
		{	
			bth ^= (bth << 5) + (bth >> 2) + value[i];

		}
		return bth;
}
unsigned long divCompression(unsigned long hash,long size)
{

return ((hash) % (size-1));

}
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637)
{
	return ((m * hash +a) % (size-1));

}
#endif
