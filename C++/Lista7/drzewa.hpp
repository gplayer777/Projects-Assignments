
#ifndef DRZEWA_HPP

#define DRZEWA_HPP


using namespace std;


template<typename T>
class bst
{
    
    
    struct node
    {
        T data;
        node* left;
        node* right;
    };
    
    
    node* root;
    
    
    node* find(node* t, T x)
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
    
    
    
    node* insert(T x, node* t)
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
    
    node* remove(T x, node* t)
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
    
    node* makeEmpty(node* t)
    {
        if(t == NULL)
            return NULL;
        
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        
        return NULL;
    }
    
    void inorder(node* t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }
    
    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }
    
    node* findMax(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }
    
    
    
    
public:
    
    bst(std::initializer_list<T> l){
        std::vector<T> temp(l.size());
        std::copy(l.begin(), l.end(), temp);
        
       for(int i = 0;i<l.size();i++){
            insert(temp.at(i), root);
       }
    
    }
    
    friend ostream& operator<< (ostream &wyj, const bst &w){
        
        wyj<<w.display();
        
        return wyj;
        
    }
    
    bst(const bst &p){
        this->root = p.root;
    }
    
    
    bst& operator = (const bst &w){
        //return *this;
        
        if (this != &w){
            
            root = w.root;

            
        }
        
        return *this;
    }
    
    
    bst()
    {
        root = NULL;
    }
    
    ~bst()
    {
        root = makeEmpty(root);
    }
    
    void insert(T x)
    {
        root = insert(x, root);
    }
    
    void remove(T x)
    {
        root = remove(x, root);
    }
    
    void display()
    {
        inorder(root);
        cout << endl;
    }
    
    void search(T x)
    {
        root = find(root, x);
    }
    
    bool find1(T x)
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
};




#endif





