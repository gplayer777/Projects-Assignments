


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include "drzewa.hpp"





using namespace std;


    template<typename T>
    node* bst<T>:: find(node* t, T x)
    {
    if(t == NULL)
        return NULL;
    else if(x < t->data)
        return find(t->left, x);
    else if(x > t->data)
        return find(t->right, x);
    else
        return t;
    }


    template<typename T>
    node* bst<T>::node<T>:: insert(T x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if(x < t->data)
            t->left = insert(x, t->left);
        else if(x > t->data)
            t->right = insert(x, t->right);
        return t;
    }

    template<typename T>
    node* bst<T>::node<T>:: remove(T x, node* t)
    {
        node* temp;
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        
        return t;
    }

    template<typename T>
    node* bst<T>::node<T>:: makeEmpty(node* t)
    {
        if(t == NULL)
            return NULL;
        
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        
        return NULL;
    }

    template<typename T>
    void bst<T>::node<T>:: inorder(node* t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    template<typename T>
    node* bst<T>::node<T>:: findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    template<typename T>
    node* bst<T>::node<T>:: findMax(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }
    
    

    template<typename T>
    bst<T>::node<T>::bst()
    {
        root = NULL;
    }

    template<typename T>
    bst<T>::node<T>::~bst()
    {
        root = makeEmpty(root);
    }

    template<typename T>
    void bst<T>::node<T>:: insert(T x)
    {
        root = insert(x, root);
    }

    template<typename T>
    void bst<T>::node<T>:: remove(T x)
    {
        root = remove(x, root);
    }

    template<typename T>
    void bst<T>::node<T>:: display()
    {
        inorder(root);
        cout << endl;
    }

    template<typename T>
    void bst<T>::node<T>:: search(T x)
    {
        root = find(root, x);
    }

    template<typename T>
    bool bst<T>::node<T>:: find1(T x)
    {
        if(root == NULL)
            return false;
        else if(x < root->data)
            return find(root->left, x);
        else if(x > root->data)
            return find(root->right, x);
        else
            return true;
    }
    



    
    
    
    






