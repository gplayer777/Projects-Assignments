#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include "klasy.hpp"
#include <stdexcept>





Punkt::Punkt(){
    
}

Punkt::Punkt(double x, double y){
    this->X = x;
    this->Y = y;
    
}

Punkt::Punkt(const Punkt &p){
    this->X = p.X;
    this->Y = p.Y;
}

Punkt& Punkt::operator = (const Punkt &punkt){
    
    return *this;
}


void Punkt::setX(double x){
    this->X = x;
    
}

void Punkt::setY(double y){
    this->Y = y;
    
}

double Punkt::getX(){
    
    return this->X;
    
}

double Punkt::getY(){
    
    return this->Y;
    
}

void Punkt::przesun(Punkt v)
{
    X = (X+v.getX());
    Y = (Y+v.getY());
}


void Punkt::obroc(Punkt p, double alfa){
    
    
    X = ((X-p.getX())*cos(alfa)-(Y-p.getY())*sin(alfa)+ p.getX());
    Y = ((X-p.getX())*sin(alfa)+(Y-p.getY())*cos(alfa)+ p.getY());
    
    
}




    
    Odcinek::Odcinek(){
        
        
    }
    
    
    Odcinek::Odcinek(Punkt p1, Punkt p2){
        
        this->P1.setX(p1.getX());
        this->P1.setY(p1.getY());
        
        this->P2.setX(p2.getX());
        this->P2.setY(p2.getY());
        
    }
    
    Odcinek& Odcinek::operator = (const Odcinek &odcinek){
        
        return *this;
    }
    
    
    Odcinek::Odcinek(const Odcinek &odcinek){
        
        this->P1 = odcinek.P1;
        
        this->P2 = odcinek.P2;
    }
    
    void Odcinek::setP1(double x, double y){
        this->P1.setX(x);
        this->P1.setY(y);
        
        
    }
    
    void Odcinek::setP2(double x, double y){
        this->P2.setX(x);
        this->P2.setY(y);
        
    }
    
    Punkt Odcinek::getP1(){
        
        return this->P1;
        
    }
    
    Punkt Odcinek::getP2(){
        
        return this->P2;
        
    }
    
    
    
    bool Odcinek::lezyNaOdcinku(Punkt p){
        
        double x1 = this->P1.getX();
        double y1 = this->P1.getY();
        
        double x2 = this->P2.getX();
        double y2 = this->P2.getY();
        
        double z1 = p.getX();
        double z2 = p.getY();
        
        
    /*    double AB = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));
        double AP = sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1)+(z-z1)*(z-z1));
        double PB = sqrt((x2-x)*(x2-x)+(y2-y)*(y2-y)+(z2-z)*(z2-z));
        
        if(AB == AP + PB)
            return true;
        
        return false;
     
     */
        
        
        double crossproduct = (z2 - y1) * (x2 - x1) - (z2 - x1) * (y2 - y1);
        
        double epsilon = 0.001;
        
        
        if (abs(crossproduct) > epsilon)
            return false;
            
        double dotproduct = (z1 - x1) * (x2 - x1) + (z2 - y1)*(y2 - y1);
            if (dotproduct < 0)
                return false;
                
        double squaredlengthba = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
                if (dotproduct > squaredlengthba)
                    return false;
                    
                    
                    
                    
        return true;
        
        
        
        
        
    }

    bool Odcinek:: onSegment(Punkt q)
    {
    if (q.getX() <= fmax(P1.getX(), P2.getX()) && q.getX() >= fmin(P1.getX(), P2.getX()) &&
        q.getY() <= fmax(P1.getY(), P2.getY()) && q.getY() >= fmin(P1.getY(), P2.getY()))
        return true;
    return false;
    }

    double Odcinek::dlugosc(){
        
        
        double x1 = this->P1.getX();
        double y1 = this->P1.getY();
        
        double x2 = this->P2.getX();
        double y2 = this->P2.getY();
        
        
        double length = sqrt( (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
        
        return length;
    }
     
    
    
    Punkt Odcinek::srodek(Odcinek o){
        
        Punkt S(((o.getP1().getX()+o.getP2().getX())/2), ((o.getP1().getY()+o.getP2().getY())/2));
        
        
        return S;
    }
    
    void Odcinek::obroc(Punkt p, double alfa){
        
        
        P1.obroc(p, alfa);
        P2.obroc(p, alfa);
        
   
        
    }
    
    void Odcinek::przesun(Punkt v)
    {
        P1.przesun(v);
        P2.przesun(v);
        
        
    }



    
    Trojkat::Trojkat(){}
    
    Trojkat::Trojkat(Punkt p1, Punkt p2, Punkt p3){
        
        this->P1 = p1;
        
        this->P2 = p2;
      
        this->P3 = p3;
        
    }
    
    Trojkat::Trojkat(const Trojkat &trojkat){
        
        this->P1 = trojkat.P1;
        
        this->P2 = trojkat.P2;
        
        this->P3 = trojkat.P3;
    }
    
    Trojkat& Trojkat::operator = (const Trojkat &trojkat){
        
        return *this;
    }
    
    
    void Trojkat::setP1(double x, double y){
        this->P1.setX(x);
        this->P1.setY(y);
        
        
    }
    
    void Trojkat::setP2(double x, double y){
        this->P2.setX(x);
        this->P2.setY(y);
        
    }
    
    void Trojkat::setP3(double x, double y){
        this->P3.setX(x);
        this->P3.setY(y);
        
    }
    
    Punkt Trojkat::getP1(){
        
        return this->P1;
        
    }
    
    Punkt Trojkat::getP2(){
        
        return this->P2;
        
    }
    
    Punkt Trojkat::getP3(){
        
        return this->P3;
        
    }
    
    
    
    double Trojkat::obwod(Trojkat t){
        
        double x1 = t.getP1().getX();
        double y1 = t.getP1().getY();
        
        double x2 = t.getP2().getX();
        double y2 = t.getP1().getY();
        
        double x3 = t.getP3().getX();
        double y3 = t.getP3().getX();
        
        double obw = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))+sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2))+sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
        
        return obw;
        
    }
    
    double Trojkat::pole(Trojkat t){
        
        double x1 = t.getP1().getX();
        double y1 = t.getP1().getY();
        
        double x2 = t.getP2().getX();
        double y2 = t.getP1().getY();
        
        double x3 = t.getP3().getX();
        double y3 = t.getP3().getX();
        
        
        double a = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
        double b = sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
        double c = sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
        double p = obwod(t)/2;
        
        double P = sqrt(p*(p-a)*(p-b)*(p-c));
        
        return P;
        
    }
    
    Punkt Trojkat::srodek(Trojkat t){
        
        double x1 = t.getP1().getX();
        double y1 = t.getP1().getY();
        
        double x2 = t.getP2().getX();
        double y2 = t.getP1().getY();
        
        double x3 = t.getP3().getX();
        double y3 = t.getP3().getX();
        
        double s1 = (x1+x2+x3)/3;
        double s2 = (y1+y2+y3)/3;
        
        Punkt sr(s1, s2);
        
        
        return sr;
        
        
    }
    
    bool Trojkat::zawieraSie(Punkt p){
        
        
        double ax = P1.getX();
        double ay = P1.getY();
        
        double bx = P2.getX();
        double by = P2.getY();
        
        double cx = P3.getX();
        double cy = P3.getY();
        
        
        double px = p.getX();
        double py = p.getY();
      
        
        double d1 = px*(ay-by) + py*(bx-ax) + (ax*by-ay*bx);
        double d2 = px*(by-cy) + py*(cx-bx) + (bx*cy-by*cx);
        double d3 = px*(cy-ay) + py*(ax-cx) + (cx*ay-cy*ax);
        
        if (((d1<=0)&&(d2<=0)&&(d3<=0)) || ((d1>=0)&&(d2>=0)&&(d3>=0) ))
            return true;
        
        
        
        return false;
        
    }


    
    void Trojkat::obroc(Punkt p, int alfa){
        
        P1.obroc(p, alfa);
        P2.obroc(p, alfa);
        P3.obroc(p, alfa);//setX((this->P1.getX()-p.getX())*cos(alfa)-(this->P1.getY()-p.getY())*sin(alfa)+ p.getX());
        
    }
    
    void Trojkat::przesun(Punkt v){
        
        P1.przesun(v);
        P2.przesun(v);
        P3.przesun(v);
        
    }
    
    
    
    
    



namespace globalne{

bool zawierajaSie(Trojkat t1, Trojkat t2){
    
    
    if(t1.zawieraSie(t2.getP1())&&t1.zawieraSie(t2.getP2())&&t1.zawieraSie(t2.getP3()))
        return true;
    
    return false;
}

bool saRozlaczne(Trojkat t1, Trojkat t2){
    
    if(!zawierajaSie(t1, t2))
        return true;
        
        return false;
}

bool saRownolegle(Odcinek o1, Odcinek o2){
    
    double A =  o1.getP1().getX()+ o1.getP2().getX();
    double B =  o1.getP1().getY()+ o1.getP2().getY();
    
    
    double C = o2.getP1().getX() + o2.getP2().getX();
    double D = o2.getP1().getY() + o2.getP2().getY();
    
    if(A/C == B/D)
        return true;
    
    return false;

}

bool saProstopadle(Odcinek o1, Odcinek o2){
    
    double A =  o1.getP1().getX()+ o1.getP2().getX();
    double B =  o1.getP1().getY()+ o1.getP2().getY();
    
    
    double C = o2.getP1().getX() + o2.getP2().getX();
    double D = o2.getP1().getY() + o2.getP2().getY();
    
    if(A*C + B*D == 0)
        return true;
    
    return false;
    
}
    
Punkt punktPrzeciecia(Odcinek o1, Odcinek o2){ // throw Exception
    
    double a1 = o1.getP2().getY()-o1.getP1().getY();
    double b1 = o1.getP1().getX()-o1.getP2().getX();
    double c1 = a1*(o1.getP1().getX()) + b1*(o1.getP1().getY());
    
    double a2 = o2.getP2().getY()-o2.getP1().getY();
    double b2 = o2.getP1().getX()-o2.getP2().getX();
    double c2 = a2*(o2.getP1().getX()) + b2*(o2.getP1().getY());
    
    double determinant = a1*b2 - a2*b1;
    
    if (determinant == 0)
    {
        throw std::invalid_argument("rownolegle");
        
        Punkt p(0.0, 0.0);
        
        
        return p;
    }
    else
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        
        Punkt p(x, y);
        
        if(o1.onSegment(p)&&o2.onSegment(p)){
            
            return p;
        }else{
            
            throw std::invalid_argument("nie maja przeciecia");
            
        }
        
    }
}



double dystans(Punkt p1, Punkt p2){
    Odcinek o(p1, p2);
    
    return o.dlugosc();
}
}











