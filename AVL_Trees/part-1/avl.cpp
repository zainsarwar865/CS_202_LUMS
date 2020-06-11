#ifndef __AVL_CPP
#define __AVL_CPP
#include "avl.h"
#include <iostream>
#include <queue>
// HELPER FUNCTIONS HERE...
template <class T>
BST<T>::BST(){
	root = NULL;
}

template <class T>
BST<T>:: ~BST(){

  // destruct(root);
}


template<class T>
void BST<T>:: destruct(node<T>* destroy_this)
{
	if(destroy_this == NULL) {return;}

	if(destroy_this->left!= NULL) 
	{
		destruct(destroy_this->left);
	}



	if(destroy_this->right!= NULL) 
	{
		destruct(destroy_this->right);
	}

	 destroy_this->left = NULL;
     destroy_this->right = NULL;
	delete destroy_this;

}

template <class T>
int BST<T> :: height (node<T>* p)
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



template <class T>
int BST<T> :: balanceFactor(node<T>* p)
{
    
	int bf;

	int l_h = height(p->left);
	int r_h = height(p->right);
	bf = l_h - r_h;
	return bf;


}

template <class T>
void BST<T> :: fixHeight(node<T>* p)
{
    
int h = 0;
h = height(p);

	p->height = h;
}

// ROTATING HELPERS 
    
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p) // RR roration
{
	node<T>* temp = p->right;
	p->right = temp->left;
	temp->left = p;
	
	fixHeight(p);
	fixHeight(temp);

    return temp;
}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* p){ // LL rotation
    
	node<T>* temp = p->left;
	p->left = temp->right; // or just NULL???
	temp->right = p;
	
	fixHeight(p);
	fixHeight(temp);
  

    return temp;
}

template <class T>
node<T>* BST<T>::rl_rotation(node<T>* p) // 
{

node<T>* temp = p->right;
p->right = rotateright(temp);
	fixHeight(p);
	fixHeight(temp);
return rotateleft(p);

		
}


template <class T>
node<T>* BST<T>:: lr_rotation(node<T>* p)
{

node<T>* temp = p->left;
p->left = rotateleft(temp);
	fixHeight(p);
	fixHeight(temp);
return  rotateright(p);
}

template <class T>
node<T>* BST<T> :: balance(node<T>* p)
{    
    	
	int diff = balanceFactor(p);
	

	if(diff > 1)
	{

		if(balanceFactor(p->left) > 0 )
			{	
				p = rotateright(p);
			}
		else
			{
				p = lr_rotation(p);
			}	
	}

	else if(diff < -1)
	{

		if(balanceFactor(p->right) <  0)
			{	
			p = rotateleft(p);
			}
		else
			{	
			p = rl_rotation(p);
			}	
	}
	

    return p;
    
}
// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k)
{
    
  root = insertHelper(value, k, root);


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



template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) 
{

    if (p == NULL)
    {
        p = new node<T>(k,value);
        
          return p;
    }
    else if (k < p->key)
    {
        p->left = insertHelper(value,k,p->left);
        p = balance (p);
    }
    else if (k >= p->key)
    {
        p->right = insertHelper(value,k,p->right);
        p = balance (p);
    }
    return p;





}
template<class T>
node<T>* BST<T> ::search(T key)
{
    

    node<T>* holder = root;

    		while((holder != NULL) && (holder->key != key) )
    		{

    			if(holder->key < key)
    			{
    				holder = holder->right;
    			}
    			else 
    			 {   			
    				holder = holder->left;
    			}
    		}

    		//	if(holder->key != key) {holder = NULL;}
                return holder;
}


// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p)
{

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

removeminh(p);

}

template<class T>
node<T>* BST<T>::removeminh(node<T>*& p) 
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
node<T>*  BST<T>::remove(node<T>* p, T k) // MAKE THIS RETURN BALANCED STUFF;

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
      p-> value = rem_this->value;
      p-> key = rem_this->key;
      p-> right = remove(p->right, rem_this-> key);

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

  return balance(p);




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
one.insert("zain",1);
one.insert("aa",10);
one.insert("Sssd",11);
one.insert("sss",1000);
one.insert("s",1999);
one.insert("sdsd",555);
one.insert("asas",2);
one.insert("asas",0);

one.insert("asas",3);
one.insert("asas",7);
one.insert("a",17);
one.insert("a",1229);
one.insert("a",17111);
one.insert("a",171);
one.insert("a",58);


one.insert("sds",1333);
//one.delete_node();
one.insert("sdss",122);
//one.insert("as",17);

one.delete_node(7);



//one.removemin(one.getRoot());


one.display(one.getRoot(),1);

//one.insert("zaina",50);

//one.insert("zaasain",5);
//one.insert("S",1);
//one.insert("Ssa",0);
//one.insert("ssa",111);

//one.delete_node(30);


}
*/

#endif



