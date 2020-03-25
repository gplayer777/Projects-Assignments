#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "drzewa.hpp"

using namespace std;


int main()
{
    bst<int> BSTInt;
    bst<string> BSTstring;
    
    
    BSTInt.insert(20);
    BSTInt.insert(25);
    BSTInt.insert(15);
    BSTInt.insert(10);
    BSTInt.insert(30);
    BSTInt.display();
    BSTInt.remove(20);
    BSTInt.display();
    BSTInt.remove(25);
    BSTInt.display();
    BSTInt.remove(30);
    BSTInt.insert(88);
    BSTInt.insert(12);
    BSTInt.display();
   
    cout<<BSTInt.find1(20)<<endl;

    BSTstring.insert("basia");
    BSTstring.insert("zosia");
    BSTstring.insert("ala");
    BSTstring.display();
    BSTstring.remove("ala");
    BSTstring.display();
    BSTstring.remove("basia");
    BSTstring.insert("magda");
    
    BSTstring.display();
    
  
    
    return 0;
}
