#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1010;
int hashTable[80] = {0}, miss = 0; //hashTable记录第一串中每种颜色珠子的个数，miss记录缺少的珠子个数

int change(char c)
{ //将数字和字母转换为hashTable的下标
    if (c >= '0' && c <= '9')
    { //数字
        return c - '0';
    }
    else if (c >= 'a' && c <= 'z') //小写字母
    {
        return c - 'a' + 10;
    }
    else if (c >= 'A' && c <= 'Z') //大写字母
    {
        return c - 'A' + 36;
    }
}

int main()
{
    char whole[maxn], target[maxn];
    scanf("%s\n", whole);
    scanf("%s", target);
    int len1 = strlen(whole);
    int len2 = strlen(target);
    for (int i = 0; i < len1; i++)
    {
        hashTable[change(whole[i])]++;
    }
    for (int i = 0; i < len2; i++)
    {
        hashTable[change(target[i])]--;
        if (hashTable[change(target[i])] < 0)
        {
            miss++;
        }
    }
    if (miss > 0)
    {
        printf("No %d\n", miss);
    }
    else
    {
        printf("Yes %d\n", len1 - len2);
    }
    return 0;
}