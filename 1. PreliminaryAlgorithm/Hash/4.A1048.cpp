#include <cstdio>
#include <algorithm>
const int maxn = 1010;
int hashTable[maxn] = {0};//hashTable[i]表示数字i出现的个数

int main()
{
    int n, m, a;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a);
        hashTable[a]++;
    }
    for (int i = 1; i < m / 2 + 1; i++) //i从1开始
    {
        if (hashTable[i] && hashTable[m - i])
        {
            if (i == m - i && hashTable[i] < 2) //i == m-i 时，必须保证数字i的个数大于等于2
            {
                continue;
            }
            printf("%d %d\n", i, m - i);
            return 0; //提前返回
        }
    }
    printf("No Solution\n");
    return 0;
}
