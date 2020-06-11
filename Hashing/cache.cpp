#ifndef CACHE__CPP
#define CACHE__CPP
#include "cache.h"
#include<iostream>
#include <sstream>
#include<time.h>
#include<fstream>
#include<string>
#include<vector>
#include<iterator>
#include <bits/stdc++.h>
#include "hashfunctions.cpp"
#include<cstdlib>
#include<string>
using namespace std;




hashcash::hashcash()
{

	tableSize = 1000;
	HashTable = new block*[tableSize]();
	entries = 0;

	dict.open("dictionary.txt");



}


hashcash::~hashcash()
{
/*
	for(int i = 0; i < tableSize; i++)
	{

		if(HashTable[i] != NULL)
		{

			delete HashTable[i];


		}

		
	}

*/

}


void hashcash::opener_cached()
{

ifstream open_this("secret1.txt");
string holder;
string shaved;

  clock_t t;
    t = clock();

while(!open_this.eof())
{

open_this >> holder;
shaved = holder.substr(0,holder.length()-1);
unsigned long converted = stol(shaved);

block* exist = find(shaved);


	if(exist != NULL)
	{
		
		lf_update(converted);
	}

	else
	{
		
		copy_dict_hc(converted);
	}

}
open_this.close();


 t = clock() - t; 
    double time_taken = ((double)t) / CLOCKS_PER_SEC; 
   cout << "Time taken is : " << std::fixed << time_taken << endl;  

}


void hashcash::inserter(unsigned long k, string val)
{

ostringstream strm;
strm << k;
string temp = strm.str();

unsigned long ind = b_hash(temp);


int i = 0;
while(i <tableSize)
{
	ind = ind % (tableSize); 
	if(HashTable[ind] == NULL || (HashTable[ind]->key == -9 && HashTable[ind]->value == "~"))
	{

	block * temp_insert = new block(k, val);
	HashTable[ind] = temp_insert;

	entries++;
	break;

	}
	i++;
	ind++;

}


}


void hashcash::copy_dict_hc(unsigned long do_this )
{

string word;
unsigned long key_h; 

dict.clear();
dict.seekg( 0, std::ios::beg );

while(!dict.eof())
{

dict >> key_h;
dict >> word;


if(do_this == key_h)
	{
	checker(do_this);
	inserter(key_h,word);
	break;

	}
}


}

void hashcash::lf_update(unsigned long conv)
{


int i = 0;
while(i < V.size())
	{	

		if(V[i].first==conv)
		{
			V[i].second = V[i].second + 1;
			break;

		}

		else
		{
			i++;
		}

	}


}

block * hashcash::find(string val)
{
unsigned long k_holder = stol(val);

unsigned long ind = b_hash(val);

if(HashTable[ind] == NULL)
{

	return NULL;
}
else if(HashTable[ind]->key == k_holder)
{
	return HashTable[ind];
}
else
{
	int counter = 0;
	while(counter < tableSize)
	{
		ind = ind % tableSize;

		if(HashTable[ind]==NULL)
		{
			return NULL;
		}

		else if(HashTable[ind]->key == k_holder)
		{
			return HashTable[ind];
		}
		counter++;
		ind++;
	}

}

	return NULL;


}
void hashcash::remove_word(string val)
{

block * check_t = find(val);
if(check_t != NULL)
{
check_t->key = -9;
check_t->value = "~";
entries--;
}





}
	

unsigned long hashcash::remove_least_lf()
{

unsigned long tbd;

vector< pair<unsigned long,unsigned long> >::iterator vp;
vector< pair<unsigned long,unsigned long> >::iterator min = V.begin();

for(vp = V.begin();vp < V.end();vp++)
{
	if(vp->second < min->second)
	{	
		min = vp;

	}

}


	tbd = min->first;
	V.erase(min);
	return tbd;


}




unsigned long hashcash::b_hash(string value) 
{
  unsigned long bh = bitHash(value);
  return (bh % (tableSize-1));

}



void hashcash::checker(unsigned long check_me)
{
if(entries == tableSize)
{

	unsigned long delete_me = remove_least_lf();

	ostringstream strm;
	strm << delete_me;


	 V.push_back( pair<unsigned long, unsigned long>(check_me,1) ); 

	remove_word(strm.str());

}

else
{
	  V.push_back( pair<unsigned long, unsigned long>(check_me,1) ); 

}

}




int main()
{

hashcash one;


one.opener_cached();
}


#endif