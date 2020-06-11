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
int BST<T>::height (node<T>* p){
   
	int h = 0;
    h = height_calc(p);


   return h;


}
template<class T>

int BST<T>::height_calc(node<T>* p)
{

        if(p->left == NULL && p->right == NULL)
            {   

                return 1;
            }

        int h = 0;     

        if(p->left != NULL)
        {
            h = std::max(h,height_calc(p->left));
        }
        if(p->right != NULL)
        {
         h = std::max(h,height_calc(p->right));
        }

        return 1 + h;

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

    //return balance(p);
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


    node<T>* hopper = root;
        if(root == NULL)
        {
            cout << "No tree exists\n";
        }

    while(hopper->left!= NULL)
        {   

            hopper = hopper->left;


        }
        return hopper;


}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {

    node<T>* min_holder = root;
    if(min_holder == NULL)
        {   
            cout << "Tree is empty\n";
            return min_holder;
        }

    else if(min_holder->left == NULL)
    {
            if(min_holder->right == NULL)
                    {   
                        delete min_holder;
                        root = NULL;
                        return root;
                    
                    }
            else
                {  
                   node<T>* temp_holder = min_holder;

                    root = min_holder->right;
                    temp_holder->right = NULL;
                    delete temp_holder;
                    return root;
                }
    }        
    else
    {
        while(min_holder->left->left != NULL )
    {   

        min_holder = min_holder->left;
    }
          
                if(min_holder->left->right == NULL)
                    {   
                        delete min_holder->left;
                    }
                else
                {  

                    node<T>* temp_holder = min_holder->left;
                    min_holder->left = min_holder->left->right;
                    delete temp_holder;
                }
    }
    return min_holder; 
    
        // This function recursively finds the min node and deletes it.
}

template<class T>
void BST<T>::delete_node(T k)

{

        if(root==NULL)
        {
            cout << "Node doesn't exist\n" << endl;
            return;
        }

        if(root->key == k)
            {

                node<T>* temp_holder = NULL;
                node<T>* lag_parent = NULL;
                if(root->left== NULL && root->right==NULL)
                {   

                        delete root;
                        root = NULL;
                        return;
                }
                
                else if(root->right == NULL)
                {


                    temp_holder = root;
                    root = root->left;
                    delete temp_holder;
                    return;
                }

                else if(root->left == NULL)
                {


                    temp_holder = root;
                    root = root->right;
                    delete temp_holder;
                    return;
                }

                else
                {

                    temp_holder = root->right;
                    lag_parent = root;
                    while(temp_holder->left != NULL)
                        {   
                            lag_parent = temp_holder;
                            temp_holder = temp_holder->left;

                        }

                       //swapping starts
                       
                        T element_holder = root->key;
                        string value_holder = root->value;

                        root->key = temp_holder->key;
                        root->value = temp_holder->value;

                        temp_holder->key = element_holder;
                        temp_holder->value = value_holder;

                        // changing links

                        if(lag_parent == root) 
                        {

                            if(temp_holder->right != NULL)
                                {   
                                    lag_parent->right = temp_holder->right;
                                 
                                }
                             else
                             {
                                lag_parent->right = NULL;
                             }   
                        }
                        else
                        {

                            if(temp_holder->right != NULL)
                            {
                                lag_parent->left = temp_holder->right;

                            }
                            else
                            {
                                lag_parent->left = NULL;
                            }

                        }

                          delete temp_holder;
                           return; 
                        
                }

            }   
        else
        {
        remove(root, k);
        }

}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{


if(k < p->key)

{
    if(p->left != NULL)
    {

        if(p->left->key == k)
        {
                node<T>* temp_holder = NULL;
                node<T>* lag_parent = NULL;
                if(p->left->left== NULL && p->left->right==NULL)
                {   
                        delete p->left;
                        p->left = NULL;
                        return p;
                }
                
                else if(p->left->right == NULL)
                {
                    temp_holder = p->left;
                    p->left = p->left->left;
                    delete temp_holder;
                    return p;
                }

                else if(p->left->left == NULL)
                {
                    temp_holder = p->left;
                    p->left = p->left->right;
                    delete temp_holder;
                    return p;
                }

                
                else
                {

                    temp_holder = p->left->right;
                    lag_parent = p->left;
                    while(temp_holder->left != NULL)
                        {   
                            lag_parent = temp_holder;
                            temp_holder = temp_holder->left;

                        }

                       //swapping starts
                       
                        T element_holder = p->left->key;
                        string value_holder = p->left->value;

                        p->left->key = temp_holder->key;
                        p->left->value = temp_holder->value;

                        temp_holder->key = element_holder;
                        temp_holder->value = value_holder;

                        // changing links

                        if(lag_parent == p->left) 
                        {

                            if(temp_holder->right != NULL)
                                {   
                                    lag_parent->right = temp_holder->right;
                                 
                                }
                             else
                             {
                                lag_parent->right = NULL;
                             }   
                        }
                        else
                        {

                            if(temp_holder->right != NULL)
                            {
                                lag_parent->left = temp_holder->right;

                            }
                            else
                            {
                                lag_parent->left = NULL;
                            }

                        }

                          delete temp_holder;
                           return p; 

                    }    

            
        
        
        }
        
            else
            {
                remove(p->left,k);
                
            }
 

        }




    else
    {
        cout << "Element doesn't exist\n";
        p = NULL;
        return p;
    }


}


else if(k > p->key)
{

        if(p->right != NULL)
        {

            if(p->right->key == k)
            {

                node<T>* temp_holder = NULL;
                node<T>* lag_parent = NULL;
                if(p->right->left== NULL && p->right->right==NULL)
                {   
                        delete p->right;
                        p->right = NULL;
                        return p;
                }
                
                else if(p->right->right == NULL)
                {
                    temp_holder = p->right;
                    p->right = p->right->left;
                    delete temp_holder;
                    return p;
                }

                else if(p->right->left == NULL)
                {
                    temp_holder = p->right;
                    p->right = p->right->right;
                    delete temp_holder;
                    return p;
                }

                
                else
                {

                    temp_holder = p->right->right;
                    lag_parent = p->right;
                    while(temp_holder->left != NULL)
                        {   
                            lag_parent = temp_holder;
                            temp_holder = temp_holder->left;

                        }

                       //swapping starts
                       
                        T element_holder = p->right->key;
                        string value_holder = p->right->value;

                        p->right->key = temp_holder->key;
                        p->right->value = temp_holder->value;

                        temp_holder->key = element_holder;
                        temp_holder->value = value_holder;

                        // changing links

                        if(lag_parent == p->right) 
                        {

                            if(temp_holder->right != NULL)
                                {   
                                    lag_parent->right = temp_holder->right;
                                 
                                }
                             else
                             {
                                lag_parent->right = NULL;
                             }   
                        }
                        else
                        {

                            if(temp_holder->right != NULL)
                            {
                                lag_parent->left = temp_holder->right;

                            }
                            else
                            {
                                lag_parent->left = NULL;
                            }

                        }

                          delete temp_holder;
                           return p; 

                    }    

            }

            else
            {
                remove(p->right,k);

            }



        }

        else
        {
            cout << "Element doesn't exist\n";
            p = NULL;
            return p;
        }


}

    return p;

}


template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}





#endif



