#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>

using namespace std;




class Punkt{
    
    private:
    double X;
    double Y;
    
    public:
    Punkt(){
        
    }
    
    Punkt(double x, double y){
        this->X = x;
        this->Y = y;
        
    }
    
    Punkt(const Punkt &p){
        this->X = p.X;
        this->Y = p.Y;
    }
    
    Punkt& operator = (const Punkt &punkt){
        
        return *this;
    }
    
    
    void setX(double x){
        this->X = x;
        
    }
    
    void setY(double y){
        this->Y = y;
        
    }
    
    double getX(){
        
        return this->X;
        
    }
    
    double getY(){
        
        return this->Y;
        
    }
    
    void przesun(Punkt v)
    {
        X = (X+v.getX());
        Y = (Y+v.getY());
    }
    
    
    void obroc(Punkt p, double alfa){
        
        
        X = ((X-p.getX())*cos(alfa)-(Y-p.getY())*sin(alfa)+ p.getX());
        Y = ((X-p.getX())*sin(alfa)+(Y-p.getY())*cos(alfa)+ p.getY());
        
        
    }
  

    
};


class Odcinek{
    
    public:
    
    Punkt P1;
    Punkt P2;
    
    public:
    
    Odcinek(){
        
        
    }
    
    
    Odcinek(Punkt p1, Punkt p2){
        
        this->P1.setX(p1.getX());
        this->P1.setY(p1.getY());
        
        this->P2.setX(p2.getX());
        this->P2.setY(p2.getY());
        
    }
    
    Odcinek& operator = (const Odcinek &odcinek){
        
        return *this;
    }
    
    
    Odcinek(const Odcinek &odcinek){
        
        this->P1 = odcinek.P1;
        
        this->P2 = odcinek.P2;
    }
    
    void setP1(double x, double y){
        this->P1.setX(x);
        this->P1.setY(y);
        
        
    }
    
    void setP2(double x, double y){
        this->P2.setX(x);
        this->P2.setY(y);
        
    }
    
    Punkt getP1(){
        
        return this->P1;
        
    }
    
    Punkt getP2(){
        
        return this->P2;
        
    }
    
    
    
    bool lezyNaOdcinku(Punkt p){
        
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
    
    double dlugosc(){
        
        
        double x1 = this->P1.getX();
        double y1 = this->P1.getY();
        
        double x2 = this->P2.getX();
        double y2 = this->P2.getY();
        
        
        double length = sqrt( (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
        
        return length;
    }
     
    
    
    Punkt srodek(Odcinek o){
        
        Punkt S(((o.getP1().getX()+o.getP2().getX())/2), ((o.getP1().getY()+o.getP2().getY())/2));
        
        
        return S;
    }
    
    void obroc(Punkt p, double alfa){
        
        
        P1.obroc(p, alfa);
        P2.obroc(p, alfa);
        
   
        
    }
    
    void przesun(Punkt v)
    {
        P1.przesun(v);
        P2.przesun(v);
        
        
    }
};

class Trojkat{
    
    
    private:
    Punkt P1;
    Punkt P2;
    Punkt P3;
    
    public:
    
    Trojkat(){}
    
    Trojkat(Punkt p1, Punkt p2, Punkt p3){
        
        this->P1 = p1;
        
        this->P2 = p2;
      
        this->P3 = p3;
        
    }
    
    Trojkat(const Trojkat &trojkat){
        
        this->P1 = trojkat.P1;
        
        this->P2 = trojkat.P2;
        
        this->P3 = trojkat.P3;
    }
    
    Trojkat& operator = (const Trojkat &trojkat){
        
        return *this;
    }
    
    
    void setP1(double x, double y){
        this->P1.setX(x);
        this->P1.setY(y);
        
        
    }
    
    void setP2(double x, double y){
        this->P2.setX(x);
        this->P2.setY(y);
        
    }
    
    void setP3(double x, double y){
        this->P3.setX(x);
        this->P3.setY(y);
        
    }
    
    Punkt getP1(){
        
        return this->P1;
        
    }
    
    Punkt getP2(){
        
        return this->P2;
        
    }
    
    Punkt getP3(){
        
        return this->P3;
        
    }
    
    
    
    double obwod(Trojkat t){
        
        double x1 = t.getP1().getX();
        double y1 = t.getP1().getY();
        
        double x2 = t.getP2().getX();
        double y2 = t.getP1().getY();
        
        double x3 = t.getP3().getX();
        double y3 = t.getP3().getX();
        
        double obw = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))+sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2))+sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
        
        return obw;
        
    }
    
    double pole(Trojkat t){
        
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
    
    Punkt srodek(Trojkat t){
        
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
    
    bool zawieraSie(Punkt p){
        
        
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
    
    void obroc(Punkt p, int alfa){
        
        P1.obroc(p, alfa);
        P2.obroc(p, alfa);
        P3.obroc(p, alfa);//setX((this->P1.getX()-p.getX())*cos(alfa)-(this->P1.getY()-p.getY())*sin(alfa)+ p.getX());
        
    }
    
    void przesun(Punkt v){
        
        P1.przesun(v);
        P2.przesun(v);
        P3.przesun(v);
        
    }
    
    
    
    
    
    
    
};



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
        throw invalid_argument("rownolegle");
        
        Punkt p(0.0, 0.0);
        
        
        return p;
    }
    else
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        
        Punkt p(x, y);
        
        if(o1.lezyNaOdcinku(p)&&o2.lezyNaOdcinku(p)){
            
            return p;
        }else{
            
            throw invalid_argument("nie maja przeciecia");
            
        }
        
    }
}



double dystans(Punkt p1, Punkt p2){
    Odcinek o(p1, p2);
    
    return o.dlugosc();
}




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
    Punkt o2(4, 6);
    
    Odcinek O1(o1, o2);
    
    Punkt o3(1, 2);
    Punkt o4(7, 8);
    
    Odcinek O2(o3, o4);
    
    try{
        p.setX(punktPrzeciecia(O1, O2).getX());
        p.setY(punktPrzeciecia(O1, O2).getY());
        
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
    
    //cout<<t.zawieraSie(s1)<<endl;
    //cout<<t.zawieraSie(s2)<<endl;
    
    
    return 0;
}
