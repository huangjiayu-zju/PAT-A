#include<iostream>
#include<string>
#include<map>
using namespace std;
bool check(char c){
    if(c <= '9' && c >= '0'){
        return true;
    }
    if(c <= 'z' && c >= 'a'){
        return true;
    }
    if(c <= 'Z' && c >= 'A'){
        return true;
    }
    return false;
}


int main(){
    map<string, int> count;
    string str;
    getline(cin, str);      //读入整行字符串
    int i = 0;//下标
    while(i < str.length()){//遍历字符串
        string word;//单词
        while(i<str.length() && check(str[i])){//是单词字符
            if(str[i] >= 'A' && str[i] <= 'Z'){
                str[i] += 32;//大写字符转换为小写
            }
            word += str[i];
            i++;
        }
        if(word!=""){//注意前提是单词非空
            if(count.find(word)!=count.end()){
                count[word]++;
            }
            else{
                count[word] = 1;
            }
        }
        //跳过非单词字符
        while(i < str.length() && check(str[i])==false){
            i++;
        }
    }
    string ans;
    int max = 0;
    for (map<string, int>::iterator it = count.begin(); it != count.end(); it++){
        if(it->second > max){
            ans = it->first;
            max = it->second;
        }
    }
    cout << ans << " " << max << endl;
    return 0;
}
