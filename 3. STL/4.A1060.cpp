#include<iostream>
#include<string>
using namespace std;
int n;//有效位数

string deal(string s, int& e){//处理字符串，求出e并处理小数点与0，保留主体
    int k = 0; //s的下标
    while(s.length()>0 && s[0] == '0'){//去除前导0
        s.erase(s.begin());
    }
    if(s[0]=='.'){//整数部分为0的情况，指数e为小数点后0的个数相反数
        s.erase(s.begin());
        while(s.length()>0 && s[0] == '0'){
            s.erase(s.begin());
            e--;
        }
    }
    else{//整数部分不为0的情况
        while(k < s.length() && s[k] != '.'){
            k++;
            e++;
        }
        if(k < s.length()){//如果遇到小数点，删除小数点
            s.erase(s.begin() + k);
        }
    }
    if(s.length()==0){//如果去除前导数后s长度为0，说明这个数是0
        e = 0; 
    }
    int num = 0;//精度
    k = 0;
    string res;
    while(num < n){//当精度没到n
        if(k < s.length()){//只要有数字就加到res末尾
            res += s[k++];
        }
        else{//否则补0
            res += '0';
        }
        num++;
    }
    return res;
}

int main(){
    string s1, s2, s3, s4;
    cin >> n >> s1 >> s2;
    int e1 = 0, e2 = 0;
    s3 = deal(s1, e1);
    s4 = deal(s2, e2);
    if(s3 == s4 && e1 == e2){
        cout << "YES 0." << s3 << "*10^" << e1 << endl;
    }
    else{
        cout << "NO 0." << s3 << "*10^" << e1 << " 0." << s4 << "*10^" << e2 << endl;
    }
}