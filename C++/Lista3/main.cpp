
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include "klasy.hpp"

using namespace std;

int main(void){
    
    Punkt p(-4, 4);
    Punkt w(-12, 2);
    Punkt s(1, 1);
    
    Odcinek o(p, w);
    
    o.obroc(s, 0.349);
    
    cout<<o.getP1().getX()<<endl;
    cout<<o.getP1().getY()<<endl;
    
    cout<<o.getP2().getX()<<endl;
    cout<<o.getP2().getY()<<endl;
    
    Punkt o1(2, 9);
    Punkt o2(5, 4.5);
    
    Odcinek O1(o1, o2);
    
    Punkt c(4.4, 5.4);
    
    
    cout<<O1.onSegment(c)<<endl;
    
    Punkt o3(1, 2);
    Punkt o4(7, 8);
    
    Odcinek O2(o3, o4);
    
    
    
    try{
        p.setX(globalne::punktPrzeciecia(O1, O2).getX());
        p.setY(globalne::punktPrzeciecia(O1, O2).getY());
        
        cout<<p.getX()<<endl;
        cout<<p.getY()<<endl;
        
    }catch(invalid_argument&){
        cout<<"nie przecinaja sie "<<endl;
    }
    
    
    Punkt t1(0, 0);
    Punkt t2(20, 0);
    Punkt t3(10, 30);
    
    Punkt s1(10, 15);
    Punkt s2(30, 15);
    
    
    Trojkat t(t1, t2, t3);
    
    cout<<t.zawieraSie(s1)<<endl;
    cout<<t.zawieraSie(s2)<<endl;
    
    Punkt o5(o2);
    
    
    return 0;
}








