#ifndef CACHE__CPP
#define CACHE__CPP
#include "nocache.h"
#include<iostream>
#include <sstream>
#include<time.h>
#include<fstream>
#include<string>

#include <bits/stdc++.h>
#include<cstdlib>

using namespace std;




nocash::nocash()
{

	dict.open("dictionary.txt");

}


nocash::~nocash()
{
}





void nocash::opener()
{

ifstream open_this("secret1.txt");
string holder;
string shaved;
if(open_this.fail()) 
{
	cout << "Failure...." << endl;
	exit(1);
}
// ADD TIMINGGSSS
    clock_t t;
    t = clock();
//long i = 1;
while(!open_this.eof())
{

			open_this >> holder;
			shaved = holder.substr(0,holder.length()-1);
			unsigned long converted;
			istringstream is;
			is.str(holder);
			is >> converted;

				find(shaved);
				//cout << i << " ";
				//i++;
				

			}
			open_this.close();


			 t = clock() - t; 
				double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds 
				cout << "Time taken is : " << std::fixed << time_taken << endl;  

}




block * nocash::find(string val)
{

string num;
string	 word;
dict.clear();
dict.seekg( 0, std::ios::beg );


while(!dict.eof())
{

dict >> num;
dict >> word;
if(val == num)
{


	
	break;
}




}


}



int main()
{

nocash one;


one.opener();
}


#endif//include any header files as required
