
#ifndef KLASY_HPP

#define KLASY_HPP


class Punkt{
    
    private:
    double X;
    double Y;
    
    public:
    Punkt();
    
    Punkt(double x, double y);
    
    Punkt(const Punkt &p);
    
    Punkt& operator = (const Punkt &punkt);
    
    
    void setX(double x);
    
    
    void setY(double y);

    double getX();

    
    double getY();
    
    void przesun(Punkt v);

    
    void obroc(Punkt p, double alfa);


};


class Odcinek{
    
    public:
    
    Punkt P1;
    Punkt P2;
    
    public:
    
    Odcinek();
    
    
    Odcinek(Punkt p1, Punkt p2);
    
    Odcinek& operator = (const Odcinek &odcinek);
    
    
    Odcinek(const Odcinek &odcinek);
    
    void setP1(double x, double y);
    
    
    void setP2(double x, double y);

    Punkt getP1();

    Punkt getP2();

    
    
    bool lezyNaOdcinku(Punkt p);
    
    bool onSegment(Punkt q);

    double dlugosc();

    
    
    Punkt srodek(Odcinek o);

    void obroc(Punkt p, double alfa);

    void przesun(Punkt v);

};

class Trojkat{
    
    
    private:
    Punkt P1;
    Punkt P2;
    Punkt P3;
    
    public:
    
    Trojkat();
    
    Trojkat(Punkt p1, Punkt p2, Punkt p3);
    
    Trojkat(const Trojkat &trojkat);
    
    Trojkat& operator = (const Trojkat &trojkat);
    
    
    void setP1(double x, double y);
    
    void setP2(double x, double y);
    
    void setP3(double x, double y);
    
    Punkt getP1();
    
    Punkt getP2();
    
    Punkt getP3();
    
    
    
    double obwod(Trojkat t);
    
    double pole(Trojkat t);
    
    Punkt srodek(Trojkat t);
    
    bool zawieraSie(Punkt p);
    void obroc(Punkt p, int alfa);
    
    void przesun(Punkt v);
    
    
    
    
    
    
    
};

namespace globalne{

bool zawierajaSie(Trojkat t1, Trojkat t2);
bool saRozlaczne(Trojkat t1, Trojkat t2);
bool saRownolegle(Odcinek o1, Odcinek o2);

bool saProstopadle(Odcinek o1, Odcinek o2);
    
Punkt punktPrzeciecia(Odcinek o1, Odcinek o2);


double dystans(Punkt p1, Punkt p2);

}
#endif







