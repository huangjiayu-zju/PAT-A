#include<cstdio>
#include<cstring>

int main(){
    char str[1000];
    scanf("%s", str);
    int N = strlen(str);
    int n1 = (N + 2) / 3, n3 = n1, n2 = N + 2 - n1 - n3;//公式
    for (int i = 0; i < n1 - 1; i++)//输出前n1-1行
    {
        printf("%c", str[i]);
        for (int j = 0; j < n2 - 2; j++)
        {
            printf(" ");//输出n2-2个空格
        }
        printf("%c\n", str[N - i - 1]);//输出当前行的右侧字符
    }
    for (int i = 0; i < n2; i++)
    {
        printf("%c", str[n1 + i - 1]);//输出底部的n个字符
    }
    return 0;
}