#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"

HashC::HashC(int size)
{

tableSize = size;
hashTable = new LinkedList<string>[size];


}
HashC::~HashC()
{


// Linked list implementatio so use it's destructors??

}

unsigned long HashC::hash(string input)
{

  unsigned long key = bitHash(input);
  unsigned long comp = divCompression(key, tableSize);
  return comp;


 
}

void HashC::insert(string word)
{
unsigned long index = hash(word);
hashTable[index].insertAtHead(word);


} 

ListItem<string>* HashC :: lookup(string word)
{

unsigned long hc = hash(word);
	
	
	return hashTable[hc].searchFor(word);

}

void HashC :: deleteWord(string word)
{

unsigned long del_me = hash(word);

hashTable[del_me].deleteElement(word);

}


#endif

