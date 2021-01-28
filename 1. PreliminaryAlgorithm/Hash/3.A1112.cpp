#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1010;           //字符串长度上限
const int maxm = 128;            //ASCII码上限
char str[maxn];                  //输入的字符串
int k, len, isStuck[maxm] = {0}; //K为重复次数，len为字符串长度，数组记录键位好坏(-1为已输出的坏键，0为坏，1为好)

void judgeStuck()
{                     //判断每个键位是否是好的
    int i = 0, j = 0; //分别为重复键位左右端点;
    while (i < len)
    { //左端点不动，右端点右移
        while (j < len && str[i] == str[j])
        {
            j++;
        }
        if ((j - i) % k != 0)
        {
            isStuck[str[i]] = 1;
        }
        i = j; //左端点设置为当前右端点
    }
}

int main()
{
    scanf("%d%s", &k, str); //注意格式
    len = strlen(str);
    judgeStuck();                 //遍历输入的字符串
    for (int i = 0; i < len; i++) //输出坏键
    {
        if (isStuck[str[i]] == 0)
        {
            printf("%c", str[i]);
            isStuck[str[i]] = -1;
        }
    }
    printf("\n");
    for (int i = 0; i < len;) //输出还原的字符串
    {
        if (isStuck[str[i]] != 1)
        {
            printf("%c", str[i]);
            i += k;
        }
        else
        {
            printf("%c", str[i]);
            i++;
        }
    }
    return 0;
}
