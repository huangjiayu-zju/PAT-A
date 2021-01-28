#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 260;//之前第四个检测点一直过不了，因为这个开的是256，后面改成258也不行，应该是fgets保存了\n\0等，而gets不保存

int n, minLen = maxn, ans = 0;//minLen为所有字符串的最小长度,ans保存公共后缀长度
char s[100][maxn];//最多100字符串，每个字符串最多256字符

int main(){
    scanf("%d", &n);
    getchar();  //接受换行符，或者写scanf("%d\n", &n)
    for (int i = 0; i < n; i++){
        fgets(s[i], maxn, stdin);
        int len = strlen(s[i]) - 1;//注意这里要减1，fgets得到的最后一个是'\n'
        if(len < minLen){
            minLen = len;//取最小长度
        }
        reverse(s[i] , s[i] + len );//反转字符串
    }
    for (int i = 0; i < minLen; i++)//判断所有字符串的第i个字符是否全部相等
    {
        char c = s[0][i];//取第一个字符串的第i个字符
        bool same = true;
        for (int j = 1; j < n; j++){
            if(c != s[j][i]){
                same = false;
                break;
            }
        }
        if(same){
            ans++;//若所有字符串的第i位相等，则ans加1
        }else{
            break;
        }
    }
    if(ans){
        for (int i = ans - 1; i >= 0; i--){
            printf("%c", s[0][i]);
        }        
    }else{
        printf("nai");
    }
    return 0;
}