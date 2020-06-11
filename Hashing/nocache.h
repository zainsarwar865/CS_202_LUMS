#ifndef H_CASH
#define H_CASH
#include "doubleHash.cpp" // includes hash functions
#include "cache.cpp"
#include<map>
#include<vector>
#include<bits/stdc++.h>

class nocash
{


public:
	nocash();
	~nocash();
	
	void opener();
	block * find(string val);
	
private:
	unsigned long entries;
	
	ifstream dict;

};

#endif