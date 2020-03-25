


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include "kolejki.hpp"

using namespace std;

int main(void){
    
    bool dalej = false;
    string w;
    int d;
    
    vector<string> g;
    
    g.push_back("asia");
    g.push_back("basia");
    
    Kolejka m{"asia", "basa"};
    
    Kolejka z(100);
    
    do{
        cout<<"1 - wyswietl "<<endl;
        cout<<"2 - rozmiar"<<endl;
        cout<<"3 - sprawddz "<<endl;
        cout<<"4 - wyciagnij"<<endl;
        cout<<"5 - wloz"<<endl;
        cin>>d;
        
        switch(d){
            case 1:
                z.wyswietl(); break;
            case 2:
                cout<<z.rozmiar()<<endl; break;
            case 3:
                cout<<z.sprawdz()<<endl; break;
            case 4:
                cout<<z.wyciagnij()<<endl; break;
            case 5:
                cout<<"podaj el"<<endl;
                cin>>w;
                z.wloz(w); break;
        }
        
        
        
        
        cout<<"dalej? t/n"<<endl;
        cin>>w;
        if(w=="t")
            dalej = true;
        else
            dalej = false;
        
    }while(dalej);
    
    
    
    Kolejka k(5);
    k.wloz("asia");
    k.wloz("basia");
    k.wloz("kasia");
    k.wloz("zosia");
    k.wloz("gosia");
    //k.wloz("marzena");
    
    /*
     cout<<k.sprawdz()<<endl;
     k.wyciagnij();
     k.wyciagnij();
     k.wyciagnij();
     k.wyciagnij();
     k.wyciagnij();
     k.wyciagnij();
     cout<<k.sprawdz()<<endl;
     
     
     k.wloz("asia");
     k.wloz("basia");
     k.wloz("kasia");
     cout<<k.sprawdz()<<endl;
     k.wyciagnij();
     cout<<k.sprawdz()<<endl;
     k.wyciagnij();
     cout<<k.sprawdz()<<endl;
     k.wyciagnij();
     cout<<k.sprawdz()<<endl;
     k.wyciagnij();
     */
    
    
    Kolejka s(k);
    cout<<s.sprawdz()<<endl;
    s=k;
    cout<<s.sprawdz()<<endl;
    
    
    return 0;
    
    
    
}





