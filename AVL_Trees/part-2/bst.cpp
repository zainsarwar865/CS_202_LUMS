#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>
#include<cstdlib>


// HELPER FUNCTIONS HERE...
template <class T>
BST<T>::BST(){
    
    root = NULL;
}

template <class T>
BST<T>:: ~BST()
{

destruct(root);

}


template<class T>
void BST<T>:: destruct(node<T>* destroy_me)
{

    if(destroy_me!= NULL)

     {   if(destroy_me->left != NULL)
        {
            destruct(destroy_me->left);
        }
        if(destroy_me->right != NULL)
        {
            destruct(destroy_me->right);
        }

        destroy_me->left = NULL;
        destroy_me->right = NULL;
        delete destroy_me;


      }
    


}






template <class T>
int BST<T>::height (node<T>* p)
{
   
      
	int h = 0;
	if(p!= NULL)
	{

		int l_h = height(p->left);
		int r_h = height(p->right);
		int max_l_r = std::max(l_h,r_h);
		h = max_l_r + 1;

	}
	return h;


}

// CLASS FUNCTIONS HERE
template <class T>
void BST<T>::insert(string value,T k){
    
    if(root==NULL)

     {
    
        root = new node<T>(k,value);
            set_height(value,k);
    
        return;
     }
     else
     {
      insertHelper(value,k,root);
          set_height(value, k);

    } 


}

template<class T>
void BST<T>::set_height(string value, T k)
{

node<T>* holder = root;
    bool found = false;
    int height = 1;

        
        
               while(!found)
                {


                    if (holder->key < k)
                        {
                        
                        holder = holder->right;
                        height++;
                        }

                    else if (holder->key > k)
                    
                        {
                            holder = holder->left;
                            height++;
                        }                             

                     else
                        {
                            break;
                        }
                }
                   
                
        holder->height = height;
  
}

// insertion helpe  r
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T>*p) { // note we need a helper because we need recursive calls
    // Insertion code goes here.
       if(k < p->key)
        {
              if(p->left!=NULL)
                {   
                    insertHelper(value,k, p->left);

                }
             else
             {
                p->left = new node<T>(k, value);
             }   

        } 

        else if(k > p->key)
        {
            if(p->right!=NULL)
                {   
                    insertHelper(value,k, p->right);

                }
             else
             {
                p->right = new node<T>(k, value);
             }   

        } 


        return p;

}
template<class T>
node<T>* BST<T>::search(T key)
{
    
    node<T>* holder = root;
    bool found = false;

        if(root==NULL){ return holder;}
        
        else
        {       while(!found)
                {
                    if(holder->key == key)
                    {
                        found = true;
                        break;
                    }

                    else if (holder->key < key)
                        {
                    
                            if(holder->right != NULL)
                            {    
                            holder = holder->right;
                            }
                            else
                            {
                                break;
                            }
                        }

                    else if (holder->key > key)
                    
                        {
                    
                            if(holder->left!= NULL)
                            {    
                            holder = holder->left;
                            }
                            else
                            {
                                break;
                            }
                        }
                   
                }

                if(holder->key != key){holder = NULL;}
                return holder;


        }

}
// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p){
    // This function finds the min node of the tree.


	    node<T>* hopper = p;
        if(p == root  && p == NULL)
        {
            cout << "No tree exists\n";
            return p;
        }


    while(hopper->left!= NULL)
        {   

            hopper = hopper->left;


        }
        return hopper;


}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) 
{

    node<T>* temp = findmin(p);
    node<T>* parent = getparent(p,temp->key); 
    
    if(temp != NULL)
{
    delete_node(temp->key);	
}


}

template<class T>
void BST<T>::delete_node(T k)

{

        root = remove(root,k);            

}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{


  if (p == NULL) 
  {
    return p;
  }

  else if (k < p->key)
   {
    p->left = remove(p->left, k);
  	}
  else if (k > p -> key)
   {
    p->right = remove(p->right, k);
  }

   else 
   {

    if ((p-> right == NULL) && (p->left == NULL))
     {
     	 delete p;
    	  p = NULL;
    } 


    else if ((p->left != NULL) && (p->right != NULL)) 
    {

      node<T>* rem_this = findmin(p -> right);
      p->value = rem_this->value;
      p->key = rem_this->key;
      p->right = remove(p->right, rem_this->key);

    } 


    else if (p->right == NULL || p->left == NULL) 
    {

      if (p->left == NULL) 
      {
        node <T>* rem_this = p;
        p = p->right;
        rem_this->right = NULL;
        delete rem_this;
      }


     else if (p->right == NULL) 
      {
        node <T>* rem_this = p;
        p = p->left;
	  delete rem_this;
      	}

    }
  }


  if (p == NULL)
   {
    return NULL;
  }

  return p;


}


template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}
template<class T>
void BST<T>::display(node<T> *p, int level)
{
    int i;
    if (p!=NULL)
    {
        display(p->right, level + 1);
        cout << endl;
      if (p == root)
        cout<<"Root -> ";
        for (i = 0; i < level && p != root; i++)
            cout<<"        ";
        cout<<p->key;
        display(p->left, level + 1);
    }
}




template<class T>
node<T>* BST<T>:: getparent(node<T>* p,T k)
{

	node<T>* parent = NULL;
	node<T>* curr_node = p;

	while(curr_node != NULL && curr_node->key != k )
	{

			parent = curr_node;
		if(curr_node->key > k)
		{		
			curr_node = curr_node-> left;

		}
		else
		{

			curr_node = curr_node->right;

		}

	}

	return parent;


}

/*
int main()
{


BST<int> one;

one.insert("a",10);
one.insert("a",20);
one.insert("a",30);
one.insert("a",40);
one.insert("a",5);
one.insert("a",2);
one.insert("a",1);
//one.insert("a",0);

/*one.removemin(one.getRoot());

one.removemin(one.getRoot());

one.removemin(one.getRoot());

//one.removemin(one.getRoot());

//one.removemin(one.getRoot());

one.removemin(one.getRoot());

one.removemin(one.getRoot());

one.removemin(one.getRoot());
one.removemin(one.getRoot());

one.removemin(one.getRoot());
one.removemin(one.getRoot());

one.removemin(one.getRoot());


one.display(one.getRoot(),1);

}

*/
#endif



