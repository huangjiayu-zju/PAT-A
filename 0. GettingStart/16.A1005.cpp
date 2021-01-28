#include<cstdio>
#include<cstring>
char num[10][10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};//数字与单词的对应
char s[110];//初始字符串
char digit[10];//sprintf函数要求digit必须为字符型数组

int main(){
    scanf("%s", s);
    int len = strlen(s);
    int sum = 0, numLen = 0;//sum为数位之和，numLen计算sum长度
    for (int i = 0; i < len; i++){
        sum += (s[i] - '0');
    }
    if(sum == 0){//如果sum为0，特判输出num[0]
        printf("%s", num[0]);
    }
    else{
        sprintf(digit, "%d", sum);//把sum写到digit数组中
        numLen = strlen(digit);
        for (int i = 0; i <= numLen - 1; i++)
        {
            printf("%s", num[digit[i] - '0']);
            if(i != numLen - 1){
                printf(" ");
            }
        }
        
    }
    return 0;
}