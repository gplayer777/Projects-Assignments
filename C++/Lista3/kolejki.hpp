
#ifndef KOLEJKI_HPP

#define KOLEJKI_HPP


class Kolejka{
    
private:
    
    std::string *kol;
    int pojemnosc;
    int koniec;
    int pocz;
    
public:
    
    Kolejka();
    Kolejka(int poj);
    
    ~Kolejka();
    
    
    Kolejka(std::initializer_list<std::string> l);
    
    
    Kolejka(Kolejka&& k);
    
    Kolejka& operator =(Kolejka&& k);
    
    Kolejka& operator = (const Kolejka &k);
    
    Kolejka(const Kolejka &k);
    void wloz(std::string k);
    
    std::string wyciagnij();
    
    std::string sprawdz();
    
    int rozmiar();
    void wyswietl();
    
    
    
    
    
};

#endif





