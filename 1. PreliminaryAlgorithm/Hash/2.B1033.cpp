#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100010;
//以bool型数组hashTable[256]来表示键盘上的字符是否完好，这里如果c是大写字母，先转换为小写字母
//读入第二个字符串，遍历字符，如果当前字符是大写字符，先转换为小写并检查上档键，都满足则输出大写字符。
bool hashTable[256];
char str[maxn];

int main()
{
    memset(hashTable, true, sizeof(hashTable)); //true表示所有键都完好
    gets(str);                                  //读入失效的键位
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] <= 'Z' && str[i] >= 'A')
        {
            str[i] = str[i] - 'A' + 'a'; //大写字母转化为小写字母
        }
        hashTable[str[i]] = false;
    }

    gets(str);
    len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] <= 'Z' && str[i] >= 'A')
        {
            int low = str[i] - 'A' + 'a';
            if (hashTable[low] == true && hashTable['+'] == true)
            { //只有小写字母的键位和上档位都完好才进行输出
                printf("%c", str[i]);
            }
            else if (hashTable[str[i]] == true)
            {
                printf("%c", str[i]);
            }
        }
    }
    printf("\n");
    return 0;
}