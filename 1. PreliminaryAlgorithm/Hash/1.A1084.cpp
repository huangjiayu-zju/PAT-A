#include <cstdio>
#include <cstring>
using namespace std;

//如何在英文字母不区分大小写的情况下判断在第一个字符串中有哪些字符没有在第二个字符串中出现
//如何保证同一个字符（不区分大小写）只输出一次，且英文字母均使用大写输出
int main()
{
    char str1[100], str2[100];
    bool HashTable[128] = {false}; //用来标记字符是否被输出
    // gets(str1);//gets在PAT中编译失败，使用下面的方法
    // gets(str2);
    //用fgets也可以通过编译，更安全
    //fgets(str1,100,stdin);
    //fgets(str2,100,stdin);
    // int len1 = strlen(str1);
    // int len2 = strlen(str2);
    int len1 = 0, len2 = 0;
    while (true)
    {
        str1[len1++] = getchar();
        if (str1[len1 - 1] == '\n')
            break;
    }
    while (true)
    {
        str2[len2++] = getchar();
        if (str2[len2 - 1] == '\n')
            break;
    }
    for (int i = 0; i < len1; i++) //枚举第一个字符串中的每个字符
    {
        int j;
        char c1, c2;
        for (j = 0; j < len2; j++) //枚举第二个字符串中的每个字符
        {
            c1 = str1[i];
            c2 = str2[j];
            if (c1 >= 'a' && c1 <= 'z') //如果是小写字符则转化为大写
            {
                c1 -= 32;
            }
            if (c2 >= 'a' && c2 <= 'z')
            {
                c2 -= 32;
            }
            if (c1 == c2) //c1在第二个字符串中出现则跳出
            {
                break;
            }
        }
        if (j == len2 && HashTable[c1] == false) //在第二个字符串中未出现c1且c1未被输出过
        {
            printf("%c", c1);
            HashTable[c1] = true;
        }
    }
    return 0;
}