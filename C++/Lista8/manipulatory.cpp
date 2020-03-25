#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <algorithm>

using namespace std;


istream &eatline(istream &in)
{
    while(in && in.get() != '\n')
    {
    }
    return in;
}



ostream &comma(ostream &out)
{
    return out << ": ";
}


ostream &colon(ostream &out)
{
    return out << ", ";
}




class streamable
{
public:
    int n;
    int m;
    
    streamable(int x){
        n = x;
    }
    streamable(int x, int w){
        n = x;
        m = w;
    }

    int getIndex(){
        
        return n;
    }

} ;

istream &operator>>(istream &in, const streamable& ign){
    
    
    int count = 1;
    
    while(in && in.get() != '\n'&&count<ign.n)
    {
        count++;
        
    }
    return in;
    
    
}

ostream &operator<<(ostream &out, const streamable& ign){
    
    string temp = "";
    int count = 0;
    
    while(count<ign.m){
        temp+=" ";
        count++;
    }
    
    out<<"["<<temp<<ign.n<<"]";
    
    
    return out;
    
    
}

streamable Ignore(int x){
 
    return streamable(x);
}

streamable Index(int x, int w){
    
    return streamable(x, w);
}






class wejscie{
    
public:
    ifstream ifs;

    
  
    wejscie(string filename){
        
        ifs.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
        try {
        ifs.open(filename, ios::binary);
        }
        catch (std::ifstream::failure e) {
            std::cerr << "Exception opening/reading file";
        }
        
        }
    
    ~wejscie(){
        ifs.close();
    }
    
    friend ostream &operator<<(ostream &in, wejscie& w){
        
        
        in<<w.getbit()<<endl;
        
     
     
        
        return in;
        
        
    }
    
    int getbit(){
        
        char temp;
        
        ifs.read(&temp, 1);
        
        
        unsigned int number = (unsigned int)(temp);
        
        
        return number;
    }
    
    
    
};





class wyjscie{
    
public:
    
    ofstream ofs;
   
   
    int num;
    
    wyjscie(string filename){
       
       
        ofs.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
        try {
            ofs.open(filename, ios::binary);
        }
        catch (std::ifstream::failure e) {
            std::cerr << "Exception opening/reading file";
        }
        
    }
    
    ~wyjscie(){
        ofs.close();
    }
    

    
    
    void setbit(int byte){
        
       
        
        char temp = (char)byte;
        
        printf("sss \n");
        
        ofs.write(&temp, 1);
        
       
    }
    
    
    
};



int main(void){
    string ss;
    
    vector<pair<int, string>> streamer;
    
    
   
    
    for(int i =0 ;i<5;i++){
        
        cin>>Ignore(2)>>ss;
        
        
        
        
        
        
        
        
        streamer.push_back(make_pair(i, ss));
    }
    
    
    
    
    
    
    sort(streamer.begin(), streamer.end());
    
    
    for(int i = 0;i<streamer.size();i++){
        
        cout<<streamer[i]<<endl;
    }
    
    
    
    
    cout<<ss<<endl;
    
 
    
    wejscie wyj("tekstowy");
    cout<<wyj.getbit();
    
    
    
    
    
    return 0;
    
    
    
}





