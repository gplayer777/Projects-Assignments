


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include "kolejki.hpp"


using namespace std;


   Kolejka::Kolejka(): Kolejka(1)
   {
       
   }
    
    Kolejka::Kolejka(int poj){
        pojemnosc = poj;
        kol = new string[poj];
        pocz = -1;
        koniec = -1;
        
    }

    Kolejka::~Kolejka (){
        delete[] kol;
    }
    
    
    Kolejka::Kolejka(std::initializer_list<string> l){
        
        kol = new string[l.size()];
        std::copy(l.begin(), l.end(), kol);
        koniec = l.size()-1;
        pocz = 0;
    }
    
    
    
    
    Kolejka::Kolejka(Kolejka&& k)
    : kol(nullptr)
    , pojemnosc(0)
    , koniec(-1)
    , pocz(-1)
    {
        kol = k.kol;
        pojemnosc = k.pojemnosc;
        koniec = k.koniec;
        pocz = k.pocz;
        
       // k.kol = nullptr;
    }



    
   Kolejka& Kolejka:: operator =(Kolejka&& k)
    {
        if(this!=&k){
            delete[] kol;
            
            kol = k.kol;
            pojemnosc = k.pojemnosc;
            koniec = k.koniec;
            pocz = k.pocz;
            
           // k.kol = nullptr;
        }
        
        
        return *this;
    }
    
    Kolejka& Kolejka:: operator = (const Kolejka &k){
        //return *this;
        
        if (this != &other){
            
            string* new_kol = new string[k.pojemnosc];
            std::copy(k.kol, k.kol+k.pojemnosc, new_kol);
            delete[] kol;
            
            kol = new_kol;
            pojemnosc  = k.pojemnosc;
            pocz = k.pocz;
            koniec = k.koniec;
        }
        
        return *this;
    }

    
    
    Kolejka::Kolejka(const Kolejka &k){
        
     
        
        
        this->operator = (k);
        
    }
    
    void Kolejka:: wloz(string k){
        
        if(koniec == pojemnosc-1){
            cout<<"nie ma miejsca w kolejce"<<endl;
            
        }
        else{
            
            if(pocz == -1)
                pocz = 0;
            
            koniec++;
            kol[koniec] = k;
            
            
        }
        
        
    }
    
    string Kolejka:: wyciagnij(){
        
        if(pocz == -1&&koniec == -1){
            cout<<"kolejka pusta"<<endl;
            return "";
        }
        if(pocz == 0 && koniec == 0){
            koniec = -1; pocz = -1;
            string s = kol[0];
            kol[0] = "";
            
            return s;
        }
        
        
        string s = kol[pocz];
        
        for(int i = 0; i<koniec;i++)
            kol[i] = kol[i+1];
        
        koniec--;
        
        return s;
    }
    
    string Kolejka:: sprawdz(){
        
        if(pocz == -1&&koniec == -1){
            cout<<"nie ma elementow"<<endl;
            return "";
        }
        
        
        return kol[pocz];
        
    }
    
    int Kolejka:: rozmiar(){
        
        return koniec+1;
    }
    
    void Kolejka:: wyswietl(){
        
        for(int i = pocz; i<=koniec;i++)
            cout<<kol[i]<<endl;
    }
    
    
    
    
    








