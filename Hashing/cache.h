#ifndef H_CASH
#define H_CASH
#include "doubleHash.cpp" // includes hash functions
#include "cache.cpp"
#include<map>
#include<vector>
#include<bits/stdc++.h>
#include<string>

class hashcash
{


public:
	hashcash();
	~hashcash();
	void copy_dict_hc(unsigned long do_this); // Why is this boolean?
	block * find(string val);
	unsigned long remove_least_lf();
	void checker(unsigned long check_me);
	void remove_word(string val);
	void inserter(unsigned long k, string val);
	void lf_update(unsigned long conv);
	void opener_cached();
	unsigned long b_hash(string value); // copied from old 

private:
	block ** HashTable;
	unsigned long entries;
	long tableSize;
	vector< pair<unsigned long,unsigned long> > V;
	ifstream dict;
};

#endif