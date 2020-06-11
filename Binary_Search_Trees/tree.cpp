#ifndef __TREE_CPP
#define __TREE_CPP
#include "tree.h"
#include "iostream"
#include <cstdlib>
#include<string>
#include<iterator>
#include<cstdlib>
using namespace std;



Tree::Tree(string name)
{	

root = new TreeItem(name);
root->generation = 1;
}

Tree::~Tree()
{


//	twoQueueDestructor();



}

void Tree::finder(TreeItem* T, string name, bool& found, TreeItem*& person_pointer)
{
	
	
	if(T->name == name)
		{	
			
			found = true;
			
			 person_pointer = T;

		}


	for(int i = 0; i < T->children.size();i++)
	{

		if(found) {break;}
		else
		{
			finder(T->children[i], name, found,person_pointer);
		}



	}



}



void Tree::AddChild(string parent_name, string child_name)
{

	TreeItem* parent_pointer = NULL;
	bool found = false;
	
	finder(root,parent_name, found, parent_pointer);
	
	
	if(parent_pointer == NULL) 
	{
		cout << "No such parent exists\n";
		 return;

	}
	else
	{

		TreeItem* new_child = new TreeItem;
		new_child->name = child_name;
		new_child->generation = (parent_pointer->generation + 1);

		parent_pointer->children.push_back(new_child);
	}


}

TreeItem* Tree::GetPerson(string person_name)
{
	
		TreeItem* person_pointer = NULL;
		bool found = false;

		finder(root,person_name, found, person_pointer);
		

			return person_pointer;
		

}


void Tree::GetParent(string child_name)
{

	bool found = false;


	if(child_name == root->name){cout << "Root has no parent\n"; return;}
	else
	
	{
		TreeItem* parent_ptr = NULL;
		TreeItem* start = root;
		parent_getter(start, child_name,parent_ptr,found);

		if(parent_ptr == NULL)
		{
			cout << "No node with this name exists\n";
		}
		else
		{

			cout << parent_ptr->name;


		}

	}

}

void Tree::parent_getter(TreeItem*& start, string child_name, TreeItem*& parent_ptr, bool& found)
{



	for(int i = 0; i < start->children.size();i++)
	{
		if(found) {break;}

	if(start->children[i]->name == child_name)
		{

			parent_ptr = start;
			found = true;
			break;
		}		
	else
	{
		parent_getter(start->children[i],child_name, parent_ptr, found);

	}	


	}






}



void Tree::GetChildren(string parent_name)
{

		bool found = false;
	
		TreeItem* parent_ptr = NULL;
		finder(root,parent_name, found, parent_ptr);
		if(parent_ptr == NULL)
		{
			cout << "No such parent exists\n";
			return;
		}
		else
		{

			if(parent_ptr->children.size() == 0) {cout << parent_name << " has no children";}
			else
			{
			for(int i = 0; i < parent_ptr->children.size();i++)
				{	

					cout << parent_ptr->children[i]->name << "  ";


				}

			}
		}



}

int Tree::GetGeneration(string person_name)
{
	TreeItem* person_ptr = NULL;
	person_ptr = GetPerson(person_name);
	if(person_ptr== NULL) 
	{
		cout << "Person doesn't exist" << endl; 
		return 0;
	}
	else
	{
	int temp = person_ptr->generation; 
	return temp;
	}
}

int Tree::GenerationCount(int generation)
{


	int count = 0;

	if(generation == 1) { return 1;}

	else
	{

	traverser(root, count,generation);
	return count;

	}


}

int Tree::GenerationGap(string person_name1, string person_name2)
{

TreeItem* p1_ptr = NULL;
TreeItem* p2_ptr = NULL;

bool found1 = false;
bool found2 = false;

//void finder(TreeItem* T, string name, bool& found, TreeItem*&person_pointer);


finder(root, person_name1,found1, p1_ptr );
finder(root, person_name2, found2,p2_ptr);


if(p1_ptr == NULL || p1_ptr == NULL)
{
	cout << "At least one of these people are not in the tree\n";
	return -1;

}

else
{
int difference = abs(p1_ptr->generation - p2_ptr->generation);
return difference;

}



}


void Tree::level_traversal() 
{ 

Queue<TreeItem*> q1;

TreeItem* hopper = root;
cout << "Next level" << endl;
cout << hopper->name << endl;
level_printer(hopper, q1);


} 



void Tree::level_printer(TreeItem*& hopper, Queue<TreeItem*> q1)
{


for(int i = 0; i < hopper->children.size();i++)
	{	

		cout << hopper->children[i]->name << "  ";
		q1.enqueue(hopper->children[i]);

	}

		

	if(!q1.isEmpty())
	{

		hopper = q1.dequeue();
		
		level_printer(hopper, q1);

	}



}





void Tree::traverser(TreeItem* R, int& count, int generation)
{

TreeItem* hopper = R;
for(int i = 0; i < R->children.size(); i++)
	{	

		if(hopper->children[i]->generation == generation)
			{	
				count++;

			}
		else
		{

			traverser(hopper->children[i], count,generation);
		}	
	}
	

}

void Tree::twoQueueDestructor()
{

Queue<TreeItem*> q1;
Queue<TreeItem*> q2;

TreeItem* hopper = root;
//cout << hopper->name;
q2.enqueue(hopper);
que_filler(hopper, q1,q2);

cout << "Lets start destryoin\n";

TreeItem* holder = NULL;
bool switcher = false;

while(1)
{
if(q2.isEmpty() && q1.isEmpty()) { break;}
else
{
if(!switcher)

	{
		holder = q2.dequeue();
		if(q2.isEmpty())
		{

			for(int i = 0; i < holder->children.size();i++)
				{	
					cout << holder->children[i]->name << endl;
					delete holder->children[i];
					
				}
			switcher = true;	
		}	
		else
		{
//	cout << holder->name << endl;	
		q1.enqueue(holder);
		}	
	}
else
	{
		holder = q1.dequeue();

		if(q1.isEmpty())
		{

			for(int i = 0; i < holder->children.size();i++)
				{	

						cout << holder->children[i]->name << endl;
					delete holder->children[i];
					
				}
			switcher = false;	

		}
		else
		{
		//cout << holder->name << endl;
		q2.enqueue(holder);
		}
	}	
}
}

cout << root->name;
	delete root;


}



void Tree::que_filler(TreeItem*& hopper,Queue<TreeItem*>& q1,Queue<TreeItem*>& q2)
{

for(int i = 0; i < hopper->children.size();i++)
	{	

		//cout << hopper->children[i]->name << "  ";
		q1.enqueue(hopper->children[i]);

	}

		//cout << endl;

	if(!q1.isEmpty())
	{
		
		hopper = q1.dequeue();
		q2.enqueue(hopper);
		que_filler(hopper, q1,q2);
	}

}


/*
int main()
{


TreeItem* stupid;
Tree one("one");
one.AddChild("one","two1");
one.AddChild("one","two2");
one.AddChild("one","two3");
one.AddChild("two1","three1");
one.AddChild("two1","three2");
one.AddChild("two1","three3");
one.AddChild("two2","three-2-1");
one.AddChild("two2","three-2-2");
one.AddChild("two2","three-2-3");
one.AddChild("two3","three-3-1");
one.AddChild("two3","three-3-2");

//one.level_traversal();








}
*/



#endif
