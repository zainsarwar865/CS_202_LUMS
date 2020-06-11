#include "bst.cpp"
#ifndef __BST_H
#define __BST_H
#include <string>
using namespace std;

template <class T>
class node{
    public:
    
    string value; 
    T key;
    node *left;
    node *right;
    int height;
    
    node (T key, string value){
        this->key = key;
        this->value = value;
        left = NULL;
        right = NULL;
        height = 1;
    }

    
};


template <class T>
class BST {
    private:    
    node<T> *root;
    
    
    node<T>* insertHelper(string value,T k, node<T> *p);
    node<T>* findmin(node<T> *p);
    node<T>* remove(node<T> *p,T k);
    node<T>* removemin(node<T> *p);
   public:
    BST(); // CONSTRUCTOR 
    ~BST(); // DESTRUCTOR
    void insert(string val, T k); // inserts the given key value pair into the tree
    void delete_node(T k);    
    node<T>* search(T k); // takes key as an input and returns the node pointer if key exists and NULL pointer if key does not exists 
    node<T>* getRoot();
    
    int height (node<T>* p);
    void set_height(string value, T k);
    void destruct(node<T>* p);
    void display(node<T> *p, int level);
    
    node<T>* getparent(node<T>* p,T k);
    

};


#endif
    