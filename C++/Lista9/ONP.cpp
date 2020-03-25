


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <stack>
#include <sstream>
#include <map>


using namespace std;

class symbol{
    
public:
    
    string typ;
    string nazwa;
    double val;
    
    symbol(string name, string type){
        nazwa = name;
        typ = type;
    }
    symbol(){}
    
    symbol(double value, string type){
        val = value;
        typ = type;
    }
    
};


class operand : public symbol{
    
  public:
  
    
    operand(string name, string type ):symbol(name, type){
        
    }
    
    operand(){}
    
    
    operand(double val, string type ):symbol(val, type){
        
    }
   
    
};


class funkcja : public symbol {

   public:

    funkcja(string name, string type):symbol(name, type){
       
    }
};



class liczba : public operand{
    
   public:
    
    liczba(double num, string type):operand(num, type){
    
    }
    
    
    
};



class zmienna: public operand{

   public:
    
    
    
    zmienna(string name, string type): operand(name, type){
        
    }
    
    
};

class stala: public operand{

public:
    
  
     stala (string name, string type): operand(name, type){
     
    }
    
};







double rpn(const string &expr, map<string, double> &zmienne, map<string, double> &stale){
   
    
    
    istringstream iss(expr);
    
    vector<double> stack;
    
    
    string token;
    while (iss >> token) {
       
        double tokenNum;
        if (istringstream(token) >> tokenNum) {
           
            stack.push_back(tokenNum);
        } else {
            
            map<string,double>::iterator it = zmienne.find(token);
            map<string,double>::iterator it2 = stale.find(token);
            
            
            if (token == "*"){
                
                double secondOperand = stack.back();
                stack.pop_back();
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(firstOperand * secondOperand);
            }
            
            else if (token == "/"){
                double secondOperand = stack.back();
                stack.pop_back();
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(firstOperand / secondOperand);
            }
            
            else if (token == "-"){
                double secondOperand = stack.back();
                stack.pop_back();
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(firstOperand - secondOperand);
            }
            
            else if (token == "+"){
                double secondOperand = stack.back();
                stack.pop_back();
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(firstOperand + secondOperand);
            }
            
            else if (token == "^"){
                
                double secondOperand = stack.back();
                stack.pop_back();
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(pow(firstOperand, secondOperand));
            }
            
            else if (token == "%"){
                
                double secondOperand = stack.back();
                stack.pop_back();
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back((int)firstOperand%(int)secondOperand);
            }
            
            else if (token == "cos"){
                
                
                double firstOperand = stack.back();
                stack.pop_back();
                
                
                stack.push_back(cos(firstOperand));
            }
            
            else if (token == "min"){
                
                double secondOperand = stack.back();
                stack.pop_back();
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(min(firstOperand, secondOperand));
            }
            
            else if (token == "max"){
                
                double secondOperand = stack.back();
                stack.pop_back();
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(max(firstOperand, secondOperand));
                
            }
            
            else if (token == "log"){
                
                double firstOperand = stack.back();
                stack.pop_back();
                
                stack.push_back(log(firstOperand));
            }
            else if (token == "sin"){
                
                double firstOperand = stack.back();
                stack.pop_back();
                
                stack.push_back(sin(firstOperand));
            }
            else if (token == "abs"){
                
               
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(abs(firstOperand));
            }
            else if (token == "sgn"){
                ///
                
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(signbit(firstOperand));
            }
            else if (token == "floor"){
                
                
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(floor(firstOperand));
            }
            else if (token == "ceil"){
                
                
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(ceil(firstOperand));
            }
            else if (token == "frac"){
                
                
                double firstOperand = stack.back();
                stack.pop_back();
                double intpart;
                
                stack.push_back(modf(firstOperand, &intpart));
            }
            else if (token == "atan"){
                
                
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(atan(firstOperand));
            }
            else if (token == "acot"){
                
                
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back((3.141592/2)-atan(firstOperand));
                
            }
            else if (token == "ln"){
                
                
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(log(firstOperand));
            }
            else if (token == "exp"){
                
                
                double firstOperand = stack.back();
                stack.pop_back();
                stack.push_back(exp(firstOperand));
            }
            
            
            
            
            
            
            
            else if(it != zmienne.end())
            {
                
                double value = it->second;
                stack.push_back(value);
                
            }
            else if(it2!= stale.end()){
                
                double value = it2->second;
                stack.push_back(value);
                
                
                
            }
            
            
            else {
                cerr << "Error" << endl;
                throw invalid_argument("wrong input");
            }
        }
        
       
    }
    
    return stack.back();
    
}



void parse(string input, vector <symbol*> &container, vector<string> &liczby, vector<string> &funkcje){
    
    
    string temp;
    
    
    for(int i = 0;i<input.length();i++){
        
        switch(input[i]){
                
                
        }
    }
    
    
    
    
}

void uzupelnijStale(map<string, double> &stal ){
   
    stal.insert(pair<string, double>("pi", 3.141592653589));
    stal.insert(pair<string, double>("fi", 1.618033988750));
    stal.insert(pair<string, double>("e", 2.718281828459));
    

}

void uzupelnijfunkcje(vector<string> &func ){
    
    func.push_back("+");
    func.push_back("*");
    func.push_back("-");
    func.push_back("/");
    func.push_back("^");
    
}

bool isFunction(string s, vector<string> &func){
    
    
    return false;
    
    
}

bool isNumber(string s, vector<string> &func){
    
    return false;

}

int toInt(char num){
    
    return (int)num-48;
}


enum string_code {
    eprint,
    eassign,
    eclear,
    eexit,
    error
    
};

string_code hashit (std::string const& inString) {
    if (inString == "print") return eprint;
    if (inString == "assign") return eassign;
    if (inString == "clear") return eclear;
    if (inString == "exit") return eexit;
    else return error;
    
}

int main() {
    
    map<string,double> stale;
    map<string,double> zmienne;
    
    zmienne.insert(pair<string, double>("a", 5));

    vector<string> funkcje;
    
    uzupelnijStale(stale);
    
    
    
    
    vector<symbol*> symbole;
    


    
    
    
    
    
    
    string case4 ="342*15-23^^/+";
    
    
    
    string case1 = " 3 4 2 * 1 5 - 2 3 ^ ^ / + ";
    string case2 = " 3 4 1111 + 1 5 - 2 3 ^ ^ / + ";
    string case3 = " 3 4 2 * + ";
   
    
    string temp;
   
    string m;
    bool k = true;
    
    while(k){
        
        cin>>m;
        
        switch(hashit(m)){
            case eexit:{
                k = false;
                break;
                
            }
                
                
            case eprint:{
                string d;
                cin.ignore();
                getline(cin, d);
                
                
                try{
                    cout<<rpn(d, zmienne, stale)<<endl;
                }catch( const std::invalid_argument& e ) {
                    cout<<"wrong argument"<<endl;
                    break;
                }
                
                break;
            }
            case eassign:{
                cout<<"podaj nazwe"<<endl;
                string d;
                cin.ignore();
                getline(cin, d);
                string ff;
                double val = 0;
                
                cout<<"podaj wartość"<<endl;
                
                cin.ignore();
                getline(cin, ff);
                
                
                try{
                    val = rpn(ff, zmienne, stale);
                } catch( const std::invalid_argument& e ) {
                    cout<<"wrong argument"<<endl;
                    break;
                }
                
                map<string,double>::iterator it = zmienne.find(d);
                
                if(it != zmienne.end())
                {
                  
                    it->second = val;
                
                    
                }
                
                if(d.length()>7){
                    cout<<"za dluga nazwa"<<endl;
                    break;
                }
                
                if(d=="clear"||d=="exit"||d=="print"||d=="print"){
                    cout<<"zla nazwa"<<endl;
                    break;
                }
                
                zmienne.insert(pair<string, double>(d, val));
                break;
            }
            case eclear:{
                
                zmienne.clear();
                break;
            }
            case error:{
                
                break;
            }
                
                
        }
    }
    
    
    
    
    
    
    
    
    
    return 0;


}
