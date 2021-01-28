#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
const int maxn = 10010;
string str[maxn];

bool cmp(string a, string b){
    return a+b < b+a;//如果a+b<b+a,就把a排前面，即判断拼接后的字典序
}

int main(){
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> str[i];
    }
    sort(str,str+n,cmp);
    string ans;//结果字符串
    for (int i = 0; i < n; i++)
    {
        ans += str[i];
    }
    while(ans.size()!=0&&ans[0]=='0'){
        ans.erase(ans.begin());//去除前导0
    }
    if(ans.size()==0) cout << 0;//如果去除前导0后串的长度变为0，应该输出0
    else cout << ans;
    return 0;
    
    
}