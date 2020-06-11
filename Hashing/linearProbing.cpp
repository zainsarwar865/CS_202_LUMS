#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "linearProbing.h"
#include "hashfunctions.cpp"


HashL::HashL(){
    tableSize = 1000; // you cant change this
    hashTable = new block* [tableSize]();
}

HashL::~HashL()
{

	for(int i = 0; i < tableSize; i++)
	{

		if(hashTable[i] != NULL)
		{

			delete hashTable[i];


		}

		delete [] hashTable;

	}


}

unsigned long HashL :: hash(string value)
{
  unsigned long key = bitHash(value);
  unsigned long ind = key % tableSize;
  return ind;



}

void HashL::resizeTable()
{

unsigned long new_t_size = tableSize*3;
count = 0; // new table is empty  
block **new_table = new block* [new_t_size]();
unsigned long temp_key;
string val;
unsigned long compressed_temp;

for(int i = 0; i < tableSize;i++)
  { 

    if(hashTable[i] != NULL)
    {

    temp_key = hashTable[i]->key;
    val =  hashTable[i]->value;
    compressed_temp = temp_key % new_t_size;

    for(int j = 0; j <  new_t_size; j++)
      { 
        if(new_table[compressed_temp] == NULL)
          { 

              block* temp_block = new block(temp_key, val);
              new_table[compressed_temp] = temp_block;
              count++;
              break;

          }
      compressed_temp++; // check this later..

      }


    }


  }
  tableSize = new_t_size;
  hashTable = new_table;
  

}

void HashL::insert(string value)
{

unsigned long hash_key = bitHash(value);
unsigned long compressed = hash_key % tableSize;


  for (int j = 0; j < tableSize; j++) 
  {
	compressed = (compressed % tableSize);

    if (hashTable[compressed] == NULL) 
    {
      	block* temp = new block(hash_key, value); // Store original hask-eky when re-sizing?? hmmm
    
     	 hashTable[compressed] = temp;
      	count++;
    	  break;
    }


    compressed++;
  }


  unsigned long l_fr = tableSize / 3; // check again wha LF should be
  if (l_fr < count) 
  {
    resizeTable();
  }

}

void HashL::deleteWord(string value)
{

  unsigned long index = hash(value);
  unsigned long hash_val = bitHash(value);

  if(hashTable[index] == NULL)
  {
    return;
  }

  else if(hashTable[index]->value == value && hashTable[index]->key == hash_val)
  {
    delete hashTable[index];
    hashTable[index] = NULL;
  }
  else
  {
  for(int i =0; i < tableSize;i++)
    { 
    index =  divCompression(index, tableSize);      

      if(hashTable[index]==NULL)
      {
        return; 
      }

      else if(hashTable[index]->value == value && hashTable[index]->key == hash_val)
      {
        delete hashTable[index];
        hashTable[index] = NULL;
  
      }
      index++;

    }

  }

	
}

block* HashL::lookup(string value)

{
	unsigned long index = hash(value);
	unsigned long hash_val = bitHash(value);

	if(hashTable[index] == NULL)
	{
		return NULL;
	}

	else if(hashTable[index]->value == value && hashTable[index]->key == hash_val)
	{
		return hashTable[index];
	}
	else
	{
		index++;	
	for(int i =0; i < tableSize;i++)
		{	
		index =  index % tableSize;		

			if(hashTable[index]==NULL)
			{
				return NULL;	
			}

			else if(hashTable[index]->value == value && hashTable[index]->key == hash_val)
			{

				return hashTable[index];

			}

			index++;

		}

	}
		return NULL;



}
#endif
