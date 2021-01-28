#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;

struct Fraction{//分数
    ll up, down;//分子，分母
};

ll gcd(ll a, ll b){
    if(b == 0) return a;
    else return gcd(b,a % b);
}

//分数的化简
Fraction reduction(Fraction result){
    if(result.down < 0){
        result.down = -result.down;
        result.up = -result.up;
    }
    if(result.up == 0){
        result.down = 1;
    }else{
        int d = gcd(abs(result.down), abs(result.up));//这里要取绝对值
        result.up /= d;
        result.down /= d;
    }
    return result;
}

//分数的四则运算
Fraction add(Fraction a,Fraction b){
    Fraction result;
    result.up = a.up * b.down + a.down * b.up;
    result.down = a.down * b.down;
    return reduction(result);
}

Fraction minu(Fraction a,Fraction b){
    Fraction result;
    result.up = a.up * b.down - a.down * b.up;
    result.down = a.down * b.down;
    return reduction(result);
}

Fraction multi(Fraction a, Fraction b){
    Fraction result;
    result.up = a.up * b.up;
    result.down = a.down * b.down;
    return reduction(result);
}

//除法如果除数为0(b.up==0)，应直接输出Error或Inf，只有当除数不为0时才能用上面函数计算
Fraction divide(Fraction a,Fraction b){
    Fraction result;
    result.up = a.up * b.down;
    result.down = a.down * b.up;
    return reduction(result);
}

void showResult(Fraction r){
    r = reduction(r);
    if(r.down == 1){
        printf("%lld", r.up);
    }
    else if(abs(r.up)>r.down){
        printf("%lld %lld/%lld", r.up / r.down, abs(r.up) % r.down, r.down);
    }else{
        printf("%lld/%lld", r.up, r.down);
    }
}