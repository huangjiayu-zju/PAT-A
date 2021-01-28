#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

//考虑到对一个确定的数字串来说，它的进制越大，则将该数字串转换为十进制的结果也就越大
//因此使用二分法，二分N2的进制，将N2从该进制转换为10进制，令其与N1的十进制比较，如果大于说明N2当前进制太大。
//数据过大时，要考虑溢出的情况！

LL map[256];              //对应0-9,a-z,注意要定义为long long型
LL inf = (1LL<<63)-1;       //long long类型最大值2^63-1

void init()
{
    for (char c = '0'; c <= '9'; c++)
    {
        map[c] = c - '0';
    }
    for (char c = 'a'; c <= 'z'; c++)
    {
        map[c] = c - 'a' + 10;
    }
}

LL convertNum10(char a[], LL radix, LL t)
{               //将a转换为10进制，t为上界防止溢出
    LL ans = 0; //注意ans类型
    int len = strlen(a);
    for (int i = 0; i < len; i++)
    {
        ans = ans * radix + map[a[i]];
        if (ans < 0 || ans > t)
        { //溢出
            return -1;
        }
    }
    return ans;
}

int cmp(char N2[], LL radix, LL t)
{ //将N2的十进制与t比较，t为N1的十进制值，
    int len = strlen(N2);
    LL num = convertNum10(N2, radix, t); //将N2转换为十进制后与t比较
    if (num < 0)
    { //溢出，N2>t
        return 1;
    }
    if (t > num)
    { //N1>N2，返回-1
        return -1;
    }
    else if (t == num)
    {
        return 0;
    }
    else
    { //N2>N1。返回1
        return 1;
    }
}

LL binarySearch(char N2[], LL left, LL right, LL t)
{ //二分求解N2的进制,t为N1的十进制值
    LL mid;
    while (left <= right)
    {
        mid = (left + right) / 2;
        int flag = cmp(N2, mid, t);
        if (flag == 0)
        {
            return mid;
        }
        else if (flag == 1)
        { //如果N2>N1，说明当前进制较大，应该往左子区间继续二分
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return -1; //解不存在
}

int findLargestDigit(char N2[])
{
    int len = strlen(N2), ans = 0;
    for (int i = 0; i < len; i++)
    {
        if (ans < map[N2[i]])
        {
            ans = map[N2[i]];
        }
    }
    return ans + 1; //注意进制下界是ans+1
}

int main()
{
    char N1[20], N2[20], temp[20];
    int tag, radix;
    init();
    scanf("%s%s%d%d", N1, N2, &tag, &radix);
    if (tag == 2)
    { //交换N1与N2
        strcpy(temp, N1);
        strcpy(N1, N2);
        strcpy(N2, temp);
    }
    LL t = convertNum10(N1, radix, inf);       //t为N1的十进制值
    LL left = findLargestDigit(N2);            //二分下界
    LL right = max(left, t) + 1;               //上界是下界与N1的十进制值的较大值加一
    LL ans = binarySearch(N2, left, right, t); // 二分查找
    if (ans == -1)
    {
        printf("Impossible\n");
    }
    else
    {
        printf("%lld\n", ans); //long long类型的输出%lld
    }
    return 0;
}