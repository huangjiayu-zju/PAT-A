#include<cstdio>
#include<string.h>
#include<algorithm>

struct bign{
    int d[1000];
    int len;//记录大整数长度
    bign(){//构造函数初始化结构体
        memset(d, 0, sizeof(d));
        len = 0;
    }
};

//把读入的字符串另存至bign结构体，使其顺位存储
bign change(char str[]){
    bign a;
    a.len = strlen(str);
    for (int i = 0; i < a.len; i++)
    {
        a.d[i] = str[a.len - i - 1] - '0';//逆着赋值
    }
    return a;
}

//比较两个bign变量大小
int compare(bign a, bign b){//a大、相等、a小分别返回1、0、-1
    if (a.len>b.len){
        return 1;
    }else if(a.len < b.len){
        return -1;
    }else{
        for (int i = a.len - 1; i >= 0;i--){
            if(a.d[i] > b.d[i]){
                return 1;
            }else if(a.d[i]<b.d[i]){
                return -1;
            }
        }
        return 0;
    }
}

//高精度加法
bign add(bign a, bign b){//a,b都为非负整数
    bign c;
    int carry = 0; //进位
    for (int i = 0; i < a.len || i < b.len; i++)//以较长的为界限
    {
        int temp = a.d[i] + b.d[i] + carry;//两个对应位与进位相加
        c.d[c.len++] = temp % 10;//个位数为该位结果
        carry = temp / 10;
    }
    if(carry != 0){
        c.d[c.len++] = carry;
    }
    return c;
}

//高精度减法
bign sub(bign a, bign b){//a-b，使用前要比较两个数的大小，如果被减数小于减数，需要先交换两个变量，然后输出负号，再使用sub函数
    bign c;
    for (int i = 0; i < a.len || i < b.len; i++)//以较长的为界限
    {
        if(a.d[i] < b.d[i]){//如果不够减
            a.d[i + 1]--;
            a.d[i] += 10;
        }
        c.d[c.len++] = a.d[i] - b.d[i];
    }
    while(c.len - 1 >= 1 && c.d[c.len - 1] == 0){
        c.len--; //去除高位的0，同时至少保留一位最低位
    }
    return c;
}

//高精度乘法
bign multi(bign a, int b){
    bign c;
    int carry = 0;
    for (int i = 0; i < a.len; i++){
        int temp = a.d[i] * b + carry;
        c.d[c.len++] = temp % 10;//个位作为该位结果
        carry = temp / 10; //高位部分作为新的进位
    }
    while(carry != 0){//乘法的进位不止一位，用while不是if
        c.d[c.len++] = carry % 10;
        carry / 10;
    }
    return c;
}

//高精度除法
bign divide(bign a, int b, int& r){//r为余数，这里将余数写成引用的形式直接作为参数传入，也可以设成全局变量。
    bign c;
    c.len = a.len;//被除数的每一位和商的每一位是一一对应的，因此先令长度相等
    for (int i = a.len - 1; i >= 0; i--)//从高位开始
    {
        r = r * 10 + a.d[i];//和上一位遗留的余数组合
        if(r < b){//不够除，该位为0
            c.d[i] = 0;
        }else{//够除
            c.d[i] = r / b;
            r = r % b;
        }
    }
    while(c.len - 1 >= 1 && c.d[c.len - 1] == 0){
        c.len--;
    }
    return c;
}


//输出bign
void print(bign a){
    for (int i = a.len - 1; i >= 0; i--)
    {
        printf("%d", a.d[i]);
    }
    
}