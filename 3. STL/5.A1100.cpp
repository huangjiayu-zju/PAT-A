#include<cstdio>
#include<map>
#include<iostream>
#include<string>
using namespace std;

string unitDigit[13] = {"tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec"};
string tenDigit[13] = {"tret", "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou"};
string numToStr[170];//数字->火星文
map<string, int> strToNum;//火星文->数字

void init(){
    for (int i = 0; i < 13; i++)
    {
        numToStr[i] = unitDigit[i];//个位为[0,12]，十位为0
        strToNum[unitDigit[i]] = i;
        numToStr[i * 13] = tenDigit[i]; //个位为0，十位为[0,12]
        strToNum[tenDigit[i]] = i * 13;
    }
    for (int i = 1; i < 13; i++)//十位
    {
        for (int j = 1; j < 13; j++)//个位
        {
            string str = tenDigit[i] + " " + unitDigit[j]; //火星文
            numToStr[13 * i + j] = str;//数字->火星文
            strToNum[str] = 13 * i + j;//火星文->数字
        }
    }
}

int main(){
    init();//打表
    int n;
    scanf("%d%*c", &n);//吸收换行符
    while(n--){
        string str;
        getline(cin, str);//逐行接受
        if(str[0]>='0'&&str[0]<='9'){
            int num = 0;
            for (int i = 0; i < str.length(); i++)
            {
                num = num * 10 + (str[i] - '0');
            }
            cout << numToStr[num] << endl;
        }
        else{
            cout << strToNum[str] << endl;
        }
    }
    return 0;
}






