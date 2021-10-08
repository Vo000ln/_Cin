#ifndef _Cin_H
#define _Cin_H
#include<type_traits>
#include<iostream>
#include<vector>
#include<limits>
#include"Myex.h"
int _find(const std::string &a,char e){
    int count(0);
    for(int i=0;i<a.length();++i){
        if(a[i]==e){
            count++;
        }
    }
    return count;
}
//Последнюю цифру в строке увеличиваем на 1
std::string& increasestr(std::string &a){
    a[a.length()-1]=static_cast<char>(static_cast<int>(a[a.length()-1])+1);
    return a; 
}
//Последнюю цифру в строке уменьшаем на 1
std::string& decreasestr(std::string &a){
    a[a.length()-1]=static_cast<char>(static_cast<int>(a[a.length()-1])-1);
    return a; 
}
//из строки в число (целочисленное) с проверкой на диапазон
template<typename T>
T getnumber(T min,T max){        

    std::string tmp,a,max_max(std::to_string(std::numeric_limits<T>::max()));
    bool b(0),minus(0);
    T count(0);
    
    if(min>max)return 0;

    do{

        try{

            getline(std::cin,a);

            if(a.length()!=0){

                b=1;
                minus=0;
                tmp="";

                //если есть минус
                if(a[0]=='-'){
                    minus=1;
                    a.erase(0,1);
                    //если только минус
                    if(a.length()==0){
                        throw Myexcept("Not right Symbol");
                    }
                    //так как макс отр число больше по модулю на 1 увеливаем последнюю цифру на 1
                    max_max=increasestr(max_max);
                }

                //Удаляем ведущие нули в начале 
                if(a.length()==1&&a[0]=='0'){}
                else {
                    while(a[0]=='0'&&a.length()>1){
                        a.erase(0,1);
                    }
                }
                //проверка на число
                for(int i=0;i<a.length();++i){

                    if(static_cast<int>(a[i])>=48&&static_cast<int>(a[i])<=57){
                        tmp+=a[i];
                    }else{
                        throw Myexcept("Not right symbol");
                    }
                }
                //проверка на границы
                if(b&&a.length()!=0){
                    //сравнение строк как чисел. если хоть одно число меньше выходим из цикла так как длины гарантировано равны
                    if(a.length()==max_max.length()){

                        for(int i=0;i<max_max.length();++i){
                            if(a[i]<max_max[i]){
                                break;
                            }
                            else if(a[i]>max_max[i]){
                                if(minus)throw Myexcept("too  small number");
                                else throw Myexcept("too big number");
                            }
                        }//если длина больше максимальной для типа

                    }else if(a.length()>max_max.length()){
                        if(minus)throw Myexcept("too  small number");
                        else throw Myexcept("too big number");
                    }

                }
                //если тип беззнаковый и есть минус
                if(minus&&!std::numeric_limits<T>::is_signed)throw Myexcept("Number cannot be negative");
                //если число максимально минимальное
                if(tmp==max_max&&minus){
                    count=(-stoll(decreasestr(max_max)))-1;
                }
                else if(b&&a.length()!=0){
                    if(minus){
                        count=(-stoll(tmp));
                    }
                    else if(b&& a.length()!=0){
                        count=(stoll(tmp));
                    }
                }
            }else {
                throw Myexcept("you have not entered anything");
            }
            if(count<min){
                throw Myexcept("too small number");
            }
            if(count>max){
                throw Myexcept("too big number");
            }
        }
        catch(const std::exception &ex){
            b=0;
            std::cout<<ex.what()<<'\n'<<"Try again\n";
            //чтобы числа не вышли за границы
            if(minus)decreasestr(max_max);
        }
    }while(!b);
    return count;    
}
//проверка на double с експоненциальной записью
template<typename T>
T getdouble(T min,T max){       

    std::string tmp,a,check;
    bool b(0),minus(0),f(0),exptopoint(0);
    T count(0);
    int lentoexp(0),maxexp,maxlen;
    //инициализируем maxlen and maxexp от типа данных
    if(std::is_same<T,double>::value){
        maxlen=15;
        maxexp=308;
    }else if(std::is_same<T,float>::value){
        maxlen=7;
        maxexp=38;
    }else{
        maxlen=19;
        maxexp=308;
    }
    if(min>max)return 0;

    do{    
        try{    
            b=1;
            tmp="";
            a="";
            minus=0;
            //f Для проверки с плавающей точкой
            f=0;
            //проверка была ли e до точки
            exptopoint=0;
            getline(std::cin,a);
            if(a.length()!=0){
                //удаляем минус
                if(a[0]=='-'){
                    minus=1;
                    a.erase(0,1);
                    //если только минус
                    if(a.length()==0){
                        throw Myexcept("Not right Symbol");
                    }
                }
                //удаляем все 0 до точки,если точка или  e то не включая перед ней
                while(a[0]=='0'&&a[1]!='.'&&a[1]!='e'&&a.length()>1){
                    a.erase(0,1);
                }
                //проверка на число с плавающей точкой
                if(_find(a,'e')<=1){ 
                    for(int i=0;i<a.length()&&b;++i){
                        if(static_cast<int>(a[i])>=48&&static_cast<int>(a[i])<=57){
                            tmp+=a[i];
                        }else if(a[i]=='e'){
                            tmp+=a[i];exptopoint=1;
                        }else if(a[i-1]=='e'&&i+1<=a.length()-1&&(a[i]=='-'||a[i]=='+')){
                            tmp+=a[i];
                        }
                        //если пред цифра и сейчас точка и след цифра или e
                        else if(i>0&&static_cast<int>(a[i-1])>=48&&static_cast<int>(a[i-1])<=57&&a[i]=='.'&&i<a.length()-1&&(static_cast<int>(a[i+1])>=48&&static_cast<int>(a[i+1])<=57||a[i+1]=='e')&&!exptopoint){
                            tmp+='.';
                            //со след если цифры
                            for(int j=i+1;j<a.length();++j){
                                if(static_cast<int>(a[j])>=48&&static_cast<int>(a[j])<=57){
                                    tmp+=a[j];
                                    //если точка это ласт символ
                                    if(a.length()==j+1){
                                        f=1;
                                    }//проверка на е
                                }else if(a[j]=='e'){
                                    tmp+=a[j];           
                                }else if((a[j-1]=='e'&&j+1<=a.length()-1)&&(a[j]=='-'||a[j]=='+')){
                                    tmp+=a[j];
                                }else{
                                    std::cout<<a[j]<<' '<<a[j-1]<<' '<<j+1<<' '<<a.length()-1<<'\n';
                                    throw Myexcept("Not right symbol");
                                }
                            }
                        }else {
                            throw Myexcept("Not right symbol");
                        }
                        if(f){
                            break;
                        }
                    }
                }else throw Myexcept("Not right symbol");
                if(a.length()>maxlen){
                    if(minus)throw Myexcept("too small or long number");
                    throw Myexcept("too big or long number");
                }
                //если есть ешка
                if(_find(a,'e')==1){
                    //проверка е на степень string для этого
                    //получим количество цифр до точки или до e чтобы подправить макс степень e
                    check="";
                    if(!exptopoint){
                        lentoexp=a.substr(0,a.find('.')).length();
                        for(int i=0;i<a.length();++i){
                            if(a[i]=='e'){for(int j=i+1;j<a.length();++j)check+=a[j];break;}
                        }
                    }else {
                        lentoexp=a.substr(0,a.find('e')).length();
                        for(int i=0;i<a.length();++i){
                            if(a[i]=='e'){for(int j=i+1;j<a.length();++j)check+=a[j];break;}
                        }
                    }
                    //чтобы после е что то было
                    if(check.length()==0){
                        throw Myexcept("Not right symbol");
                    }
                    //если срез от начала строки до е равен в числе нулю
                    if(stoll(a.substr(0,'e'))!=0){
                        //-1 чтобы макс степень была на 1 меньше чем возможная
                        if(stoll(check)>(maxexp-lentoexp)){
                            throw Myexcept("too big number");
                        }else if(-stoll(check)>(maxexp+lentoexp-2)){
                            throw Myexcept("too small number");
                        }
                    }
                }
                // из строки в число если с минусом
                if(minus){
                    count=(-stold(tmp));
                }// без минуса
                else{
                    count=stold(tmp);
                }
            }else{
                throw Myexcept("you have not entered anything"); 
            }
            if(count<min){throw Myexcept("too small number");}
            if(count>max){throw Myexcept("too big number");}
        }
        catch(const std::exception& ex){
            std::cout<<ex.what()<<'\n'<<"Try Again\n";
            b=0;
        }
    }while(!b);
    return count;    
}

template<class T>
class _Cin{
private:
    std::vector<T> m_data;
public:
    _Cin(int c=1){ 
        if(std::numeric_limits<T>::is_integer){
            do{
                m_data.push_back(getnumber(std::numeric_limits<T>::lowest(),std::numeric_limits<T>::max()));
            }while(m_data.size()<c);
        }else if(std::is_floating_point<T>::value){
            do{
                m_data.push_back(getdouble(std::numeric_limits<T>::lowest(),std::numeric_limits<T>::max()));
            }while(m_data.size()<c);
        }else{
            throw Myexcept("template argument is invalid");
        }
    }
    _Cin(T min,T max,int c=1){ 
        if(std::numeric_limits<T>::is_integer){
            if(min<std::numeric_limits<T>::lowest()){
                min=std::numeric_limits<T>::min();
            }
            if(max>std::numeric_limits<T>::max()){
                max=std::numeric_limits<T>::max();
            }
            do{
                m_data.push_back(getnumber(min,max));
            }while(m_data.size()<c);
        }else if(std::is_floating_point<T>::value){
            do{
                m_data.push_back(getdouble(min,max));
            }while(m_data.size()<c);
        }else{
            throw Myexcept("template argument is invalid");
        }
    }
    /*_Cin(int c=1){ 
        if(typeid(m_data)==typeid(std::vector<int>)||typeid(m_data)==typeid(std::vector<short>)||typeid(m_data)==typeid(std::vector<long long int>)){
            do{
                m_data.push_back(getnumber(std::numeric_limits<T>::lowest(),std::numeric_limits<T>::max()));
            }while(m_data.size()<c);
        }else if(typeid(m_data)==typeid(std::vector<double>)){
            do{
                //lowest так как мин возвращает полож число минимальное 
                m_data.push_back(getdouble(std::numeric_limits<T>::lowest(),std::numeric_limits<T>::max()));
            }while(m_data.size()<c);
        }else{
            throw Myexcept("template argument is invalid");
        }
    }  
    _Cin(T min,T max,int c=1){
        if(typeid(m_data)==typeid(std::vector<int>)||typeid(m_data)==typeid(std::vector<short>)||typeid(m_data)==typeid(std::vector<long long int>)){
            min<std::numeric_limits<T>::min()?min=std::numeric_limits<T>::min():min=min;
            max>std::numeric_limits<T>::max()?max=std::numeric_limits<T>::max():max=max; 
            do{
                m_data.push_back(getnumber(min,max));
            }while(m_data.size()<c);
        }else if(typeid(m_data)==typeid(std::vector<double>)){
            do{
                m_data.push_back(getdouble(min,max));
            }while(m_data.size()<c);
        }else{
            throw Myexcept("template argument is invalid");
        }
    }*/
    void print(){
        for(const auto &v:m_data)std::cout<<v<<' ';
    }
    std::vector<T>& getvec(){
        return m_data; 
    }
    T getvalue(){
        return m_data[0];
    }
    //перегрузка в вектор и в число
    operator std::vector<T>&(){return m_data;}
    operator T(){return m_data[0];}
};
#endif
/*#ifndef _Cin_H
#define _Cin_H
#include<typeinfo>
#include<iostream>
#include<vector>
#include<cassert>
#include<limits.h>
#include<float.h>
#ifndef Isfloat 
#define Isfloat i>0&&static_cast<int>(a[i-1])>=48&&static_cast<int>(a[i-1])<=57&&a[i]=='.'&&i<a.length()-1&&static_cast<int>(a[i+1])>=48&&static_cast<int>(a[i+1])<=57
#endif
//Последнюю цифру в строке увеличиваем на 1
std::string& increasestr(std::string &a){
    a[a.length()-1]=static_cast<char>(static_cast<int>(a[a.length()-1])+1);
    return a; 
}
//Последнюю цифру в строке уменьшаем на 1
std::string& decreasestr(std::string &a){
    a[a.length()-1]=static_cast<char>(static_cast<int>(a[a.length()-1])-1);
    return a; 
}
//из строки в число (целочисленное) с проверкой на диапазон
long long int getnumber(long long min,long long max,std::string &&max_max){        
    std::string tmp,a;bool b(0),minus(0);long long int count(0);
    do{
        try{
            getline(std::cin,a);
            if(a.length()!=0){
                b=1;
                minus=0;
                tmp="";
                //Удаляем ведущие нули в начале 
                if(a.length()==1&&a[0]=='0'){}
                else {
                    while(a[0]=='0'){
                        a.erase(0,1);
                    }
                }
                //проверка на число
                for(int i=0;i<a.length();++i){
                    if(static_cast<int>(a[i])>=48&&static_cast<int>(a[i])<=57){
                        tmp+=a[i];
                    }    
                    else if(i==0&&static_cast<int>(a[i])==45){
                        minus=1;b=1;
                    }
                    else {
                        b=0;
                        throw "Not right symbol\n";
                    }
                }
                //удаляем минус если отр число
                if(minus){
                    a.erase(0,1);
                    max_max=increasestr(max_max);
                }
                //проверка на границы
                if(b&&a.length()!=0){
                    if(a.length()==max_max.length()){
                        for(int i=0;i<max_max.length();++i){
                            if(a[i]<max_max[i]){
                                break;
                            }
                            else if(a[i]>max_max[i]){
                                b=0;
                                if(minus)throw "too  small number\n";
                                else throw "too big number\n";
                            }
                        }
                    }else if(a.length()>max_max.length()){
                        b=0;
                        if(minus)throw "too  small number\n";
                        else throw "too big number\n";
                    }
                }
                //если число максимально минимальное
                if(tmp==max_max&&minus){
                    count=(stoll(max_max)*-1);
                    b=1;
                    if(count<min){b=0;throw "too small number\n";}
                    if(count>max){b=0;throw "too big number\n";}
                }
                else if(b&&a.length()!=0){
                    if(minus){
                        count=(-stoll(tmp));
                        if(count<min){b=0;throw "too small number\n";}
                        if(count>max){b=0;throw "too big number\n";}
                    }
                    else if(b&& a.length()!=0){
                        count=(stoll(tmp));
                        if(count<min){b=0;throw "too small number\n";}
                        if(count>max){b=0;throw "too big number\n";}
                    }
                }
            }else {
                b=0;
                throw "you have not entered anything\n";
            }
            if(b&&minus){
                b=0;
                throw "Not right Symbol\n";
            }
        }
        catch(const char *ex){
            std::cout<<ex<<"Try again\n";
        }
    }while(!b);
    return count;    
}
//проверка на double но без експоненциальной записи
double getnumber(double min,double max){        
    std::string tmp,a;bool b(0),minus(0),f(0);double count(0);
    do{    
        try{
            b=1;
            tmp="";
            a="";
            f=0;
            
            if(min>max){b=0;exit(1);}
            getline(std::cin,a);
            if(a.length()!=0){
                if(a.length()==1&&a[0]=='0'||(a.length()==3&&a[0]=='0'&&a[1]=='.'&&a[2]=='0')){
                    count=(stod(a));
                    if(count<min){b=0;throw "too small number\n";}
                    if(count>max){b=0;throw "too big number\n";}
                    b=1;
                    break;
                }
                while(a[0]=='0'&&a[1]!='.'){
                    a.erase(0,1);
                }
                if(a[0]=='-'){
                    minus=1;
                    a.erase(0,1);
                } 
                for(int i=0;i<a.length()&&b;++i){
                    if(static_cast<int>(a[i])>=48&&static_cast<int>(a[i])<=57){
                        tmp+=a[i];
                    }
                    else if(Isfloat){
                        tmp+='.';
                        for(int j=i+1;j<a.length();++j){
                            if(static_cast<int>(a[j])>=48&&static_cast<int>(a[j])<=57){
                                tmp+=a[j];
                                if(a.length()==j+1){
                                    f=1;
                                }    
                            }
                            else {
                                b=0;
                                throw "Not right symbol\n";
                            }
                        }
                    }else {
                        b=0;
                        throw "Not right symbol\n";
                    }
                    if(f){
                        break;
                    }
                }
                if(b){
                    if(a.length()>15){
                        b=0;
                        if(minus)throw "too small number\n";
                        throw "too big number\n";
                    }
                }
                if(b){
                    if(minus){
                        count=(-stod(tmp));
                        if(count<min){b=0;throw "too small number\n";}
                        if(count>max){b=0;throw "too big number\n";}
                    }
                    else{
                        count=stod(tmp);
                        if(count<min){b=0;throw "too small number\n";}
                        if(count>max){b=0;throw "too big number\n";}
                    }
                }
            }else{
                b=0;
                throw "you have not entered anything\n"; 
            }
            if(b&&minus){
                b=0;
                throw "Not right Symbol\n";
            }
        }
        catch(const char* ex){
            std::cout<<ex<<"Try Again\n";
        }
    }while(!b);
    return count;    
}
template<class T>
class _Cin{
private:
    std::vector<T> m_data;
public:
    _Cin(int c=1){ 
        std::string max_int="2147483647",max_short="32767",max_long="9223372036854775807";
        if(typeid(m_data)==typeid(std::vector<int>)){
            do{
                m_data.push_back(getnumber(INT_MIN,INT_MAX,std::string(max_int)));
            }while(m_data.size()<c);
        }else if(typeid(m_data)==typeid(std::vector<short>)){
            do{
                m_data.push_back(getnumber(SHRT_MIN,SHRT_MAX,std::string(max_short)));
            }while(m_data.size()<c);
        }else if(typeid(m_data)==typeid(std::vector<double>)||typeid(m_data)==typeid(std::vector<float>)){
            do{
                m_data.push_back(getnumber(DBL_MIN,DBL_MAX));
            }while(m_data.size()<c);
        }else if(typeid(m_data)==typeid(std::vector<long long int>)){
            do{
                m_data.push_back(getnumber(LLONG_MIN,LLONG_MAX,std::string(max_long)));
            }while(m_data.size()<c);
        }else{
            std::cout<<"this type is not supported\n";
        }
    }
    _Cin(long long int min,long long int max,int c=1,bool plus=1){
        std::string max_int="2147483647",max_short="32767",max_long="9223372036854775807";
        if(typeid(m_data)==typeid(std::vector<int>)){
            min<INT_MIN?min=INT_MIN:min=min;
            max>INT_MAX?max=INT_MAX:max=max;
            if(plus&&min<0)min=0;
            do{
                m_data.push_back(getnumber(min,max,std::string(max_int)));
            }while(m_data.size()<c);
        }else if(typeid(m_data)==typeid(std::vector<short>)){
            min<SHRT_MIN?min=SHRT_MIN:min=min;
            max>SHRT_MAX?max=SHRT_MAX:max=max;
            if(plus&&min<0)min=0;
            do{
                m_data.push_back(getnumber(min,max,std::string(max_short)));
            }while(m_data.size()<c);
        }else if(typeid(m_data)==typeid(std::vector<double>)||typeid(m_data)==typeid(std::vector<float>)){
            if(plus&&min<0)min=0;
            do{
                m_data.push_back(getnumber(min,max));
            }while(m_data.size()<c);
        }else if(typeid(m_data)==typeid(std::vector<long long int>)){
            min<LLONG_MIN?min=LLONG_MIN:min=min;
            max>LLONG_MAX?max=LLONG_MAX:max=max;
            if(plus&&min<0)min=0;
            do{
                m_data.push_back(getnumber(min,max,std::string(max_long)));
            }while(m_data.size()<c);
        }else{
            std::cout<<"this type is not supported\n";
        }
    }
    void print(){
        for(auto &v:m_data)std::cout<<v<<' ';
    }

    std::vector<T>& getvec(){
        return m_data; 
    }

    T getvalue(){
        assert(m_data.size()==1&&"Size not 1");
            return m_data[0];
    }
};
#endif
int rr(const std::string &a,char f){
    for(int i=0;i<a.length();++i)if(a[i]==f)return i;
    return 101;
}
double gggg(std::string &a){
    int j(0),e(0);std::string b;
    double res;
    if(rr(a,'.')!=101){
    b=a.substr(rr(a,'.')+1,a.length()-rr(a,'.')-1);
    a.erase(a.length()-b.length()-1,b.length()+1);
    for(int i=0;i<a.length();++i){
        if(CHAR_TO_NUMBER.find(a[i])!=CHAR_TO_NUMBER.cend()){j+=CHAR_TO_NUMBER.at(a[i])*pow(10,a.length()-i-1);}
    }
    for(int i=0;i<b.length();++i){
        if(CHAR_TO_NUMBER.find(b[i])!=CHAR_TO_NUMBER.cend()){e+=CHAR_TO_NUMBER.at(b[i])*pow(10,b.length()-i-1);}
    }
    int d=-b.length();
    res=j+e*pow(10,d);
    std::cout<<j<<' '<<e<<' '<<std::setprecision(15)<<res<<'\n';
    return res;
    }else
    {for(int i=0;i<a.length();++i){
        if(CHAR_TO_NUMBER.find(a[i])!=CHAR_TO_NUMBER.cend()){j+=CHAR_TO_NUMBER.at(a[i])*pow(10,a.length()-i-1);}
    }
    return j;
    }
}static std::map<char,int> CHAR_TO_NUMBER{{'0',0},{'1',1},{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9}};
*/