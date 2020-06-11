#ifndef __TREE_H
#define __TREE_H
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cstring>
#include "queue.cpp"
#include<string>

using namespace std;

struct TreeItem
{
	string name;
	int generation;
	vector<TreeItem*> children; 

	TreeItem()
	{
		name = "";
	}

	TreeItem(string name)
	{
		this->name = name;
	}
};


class Tree
{

private:

	TreeItem* root;

public:
	// Constructor
	Tree(string name); 

	// Destructor
	~Tree();
	

	// Member Functions
	void AddChild(string parent_name, string child_name);
	TreeItem* GetPerson(string person_name);
		void GetParent(string child_name);
	void GetChildren(string parent_name);
	int GetGeneration(string person_name);
	int GenerationCount(int generation);
	int GenerationGap(string person_name1, string person_name2);
	void level_traversal();
	void finder(TreeItem* T, string name, bool& found, TreeItem*&person_pointer);
	void traverser(TreeItem* R, int& count, int generation);
	void parent_getter(TreeItem*& start, string child_name, TreeItem*& parent_ptr, bool& found);
	void level_printer(TreeItem*& hopper, Queue<TreeItem*> q1);

	/*You can add additional functions if necessary*/
	void twoQueueDestructor();
	void que_filler(TreeItem*& hopper,Queue<TreeItem*>& q1,Queue<TreeItem*>& q2);


};





#endif
