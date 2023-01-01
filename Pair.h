
#ifndef __PAIR
#define __PAIR

template<class A,class B>
class Pair
{
private:
    A a;
    B b;
public:
    Pair() = default;
    Pair(const A& a,const B& b);
    ~Pair() = default;

    A getA() const;
    void setA(const A& a);
    B getB() const;
    void setB(const B& b);
};

template<class A,class B>
Pair<A,B> :: Pair(const A& a,const B& b) : a(a),b(b){}

template<class A,class B>
A Pair<A,B> :: getA() const{
    return a;
}

template<class A,class B>
void Pair<A,B> :: setA(const A& a){
    this->a = a;
    return;
}

template<class A,class B>
B Pair<A,B> :: getB() const{
    return b;
}
    
template<class A,class B>
void Pair<A,B> :: setB(const B& b){
    this->b = b;
    return;
}

template<class A,class B>
bool operator>(const Pair<A,B>& first, const Pair<A,B>& second){
    if (first.getA() > second.getA()){
        return true;
    }
    else if (first.getA() < second.getA()){
        return false;
    }
    else{
        if(first.getB() > second.getB() ){
            return true;
        }
        else{
            return false;
        }
    }
}

template<class A,class B>
bool operator==(const Pair<A,B>& first, const Pair<A,B>& second){
    return( (first.getA() == second.getA()) && (first.getB() == second.getB()) );
}

template<class A,class B>
bool operator<(const Pair<A,B>& first, const Pair<A,B>& second){
    return !(first>second || first == second);
}

template<class A,class B>
bool operator<=(const Pair<A,B>& first, const Pair<A,B>& second){
    return( (first == second) || (first < second) );
}

template<class A,class B>
bool operator>=(const Pair<A,B>& first, const Pair<A,B>& second){
    return( (first == second) || (first > second) );
}



#endif //Pair