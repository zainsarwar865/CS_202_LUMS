#ifndef __DICTIONARY_CPP
#define __DICTIONARY_CPP
#include "adictionary.h"
#include <time.h>
#include <stdio.h>
#include<cstdlib>
#include<string>
#include<fstream>

Dictionary::Dictionary() 
{
	wordsTree = NULL; 

}

Dictionary::~Dictionary()
{
wordsTree = NULL;

}

void Dictionary::initialize(string wordsFile)
{
	wordsTree = new BST<string>;

	ifstream dict;
	dict.open(wordsFile);
    
	if(dict.fail())
	{
		cout << "Failed to open file\n";
		exit(1);

	}

	string word;

	while(!dict.eof())
	{

		dict >> word;
		wordsTree->insert(word,word);

	}


dict.close();


}

bool Dictionary::deleteWord(string word) 
{
	

	node<string>* temp = findWord(word);
	if(temp == NULL){return false;}

	wordsTree->delete_node(word);
	return true;

}
bool Dictionary::editWord(string oldWord, string newWord) 
{

	node<string>* temp = findWord(oldWord);
	if(temp == NULL){return false;}

	wordsTree->delete_node(oldWord);
	insertWord(newWord);

	return true;
}
bool Dictionary::insertWord(string word)
{


	node<string>* temp = findWord(word);
	if(temp != NULL){return false;}

	wordsTree->insert(word,word);
	return true;
}
node<string>* Dictionary::findWord(string word) {
	clock_t t; 
    t = clock();
    

    node<string>* temp =  wordsTree->search(word);
    

    t = clock() - t; 
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds 
    cout << "findWord() took " << std::fixed << time_taken << "sec to search for " << word << endl;  

    return temp; // TODO
}



int menu()
{


		cout << "1 - Search\n";
		cout << "2 - Insert a word\n";
		cout << "3 - Edit a word\n";
		cout << "4 - Delete a word\n";
		
		int ans ;
		cin >> ans;
		return ans;

}

int main() 
{

Dictionary one;
string inp = "words.txt";
one.initialize(inp);

char e = 'N';
int result;
string word;
string word2;

node<string>* t = NULL;
bool check = false;
/*
while(e != 'Y')
{

	result = menu();
	if(result == 1) 
		{

			cout << "Enter word\n";
			cin >> word;
			t = one.findWord(word);
			if(t != NULL) {cout << "Found it\n";}
			else{cout << "Word doesn't exist\n";}
		 }

	else if (result == 2)
	{

		cout << "Enter word you want to insert\n";
		cin >> word;
		check = one.insertWord(word);
		if(check) {cout << "Inserted\n";}
		else{cout << "Word already present?\n";}

	}	 

	else if(result == 3)
	{
	cout << "Enter word you want to edit\n";
		cin >> word;
		cout << "With what?\n";
		cin >> word2;
		check = one.editWord(word,word2);
		if(check) {cout << "Edited\n";}
		else{cout << "Word doesn't exist?\n";}
	}


	else if (result == 4)
	{

		cout << "Enter word you want to delete\n";
		cin >> word;
		check = one.deleteWord(word);
		if(check) {cout << "Deleted\n";}
		else{cout << "Word doesn't exist?\n";}

	}	 
 


cout << "Press Y to exit or something else to continie\n";
cin >> e;


}



	*/

}
	
#endif



