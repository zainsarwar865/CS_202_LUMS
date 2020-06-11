#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"


HashD::HashD()
{
  tableSize = 10000;
  count = 0;
hashTable = new block*[tableSize]();
  
}

HashD::~HashD()
{


  for(int i = 0; i < tableSize;i++)
  {

  	if(hashTable[i] != NULL)
  	{
  		delete hashTable[i];
  	}


  }
  delete hashTable;

}

void HashD::resizeTable()
{
	unsigned long old_s = tableSize;
 	
tableSize = tableSize *4;
 count = 0;
  string new_val;

  block ** prev_t = hashTable;
  hashTable = new block*[tableSize]();
  for (int i = 0; i < old_s; i++)
   {
    if (prev_t[i]!= NULL) 
    {
    	new_val = prev_t[i]->value;
      insert(new_val);
    }
  }
  

  for(int i = 0; i < old_s;i++)
  {

  	if(prev_t[i] != NULL)
  	{
  		delete prev_t[i];
  	}


  }
  delete prev_t;
}



void HashD::insert(string value)
{
  
  unsigned long h1 = hash1(value);

  unsigned long h2 = hash2(value);

  unsigned long key_insert = 0;


  unsigned long ap = bitHash(value);
  unsigned long ind;
  unsigned long iterator = 0;

  while(1)
  {
  	
  	key_insert = h1 + (iterator*h2);
  	ind = key_insert  % (tableSize-1);

  	if(hashTable[ind] == NULL)
  	{

  		block* t = new block(ap,value);
  		hashTable[ind] = t;
  		count++;
  		break;
  	}
  	else
  	{
  		iterator++;
  	}



  }

  unsigned long l_fr = tableSize / 3; // check again wha LF should be
  if (l_fr < count) 
  {
    resizeTable();
  }
  
}

void HashD::deleteWord(string value)
{
 

unsigned long key_holder = bitHash(value);
unsigned long iterator = 0;
unsigned long ind;
unsigned long hash_1 = hash1(value);
unsigned long hash_2 = hash2(value);


while(iterator < tableSize)
{

ind = (hash_1 + (iterator*hash_2)) % (tableSize-1);

if(hashTable[ind] == NULL)
{
	return;
}
else if ((hashTable[ind]->key == key_holder) && (hashTable[ind]->value == value))
{
	delete hashTable[ind];
	count--;
}

else
{

	iterator++;

}


}



}


unsigned long HashD::hash2(string value) 
{
  unsigned long ph = bitHash(value);

  return madCompression(ph,tableSize);

}

block* HashD::lookup(string value)
{

unsigned long key_holder = bitHash(value);
unsigned long iterator = 0;
unsigned long ind;
unsigned long hash_1 = hash1(value);
unsigned long hash_2 = hash2(value);


while(iterator < tableSize)
{

ind = (hash_1 + (iterator*hash_2)) % (tableSize-1);

if(hashTable[ind] == NULL)
{
	return NULL;
}
else if ((hashTable[ind]->key == key_holder) && (hashTable[ind]->value == value))
{
	return hashTable[ind];
}

else
{

	iterator++;

}


}


}


unsigned long HashD::hash1(string value) 
{
  unsigned long bh = bitHash(value);
  return bh % (tableSize-1);

}


#endif