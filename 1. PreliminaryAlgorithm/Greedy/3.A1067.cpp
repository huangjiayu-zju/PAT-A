#include <algorithm>
#include <cstdio>
using namespace std;

//如果数字0当前在i号位，则找到数字i当前所处的位置，然后把0与i进行交换。
//交换后数字i不会再变动，注意如果数字0回到了0的位置，就随意选择一个还没有回到本位的数字，让其与0交换位置
//具体实现可以用left记录除0外不在本位上的数的个数，在读入数据时预处理其初值

const int maxn = 100010;
int pos[maxn]; //pos存放各数字当前所处的位置编号(我一开始定义seq[maxn]直接按顺序存放输入数字，结果很麻烦)

int main()
{
    int n, ans = 0; //ans记录交换步数
    scanf("%d", &n);
    /*两个循环可以合并
    for (int i = 0; i < n; i++)
    {
        int a;
        scanf("%d",&a);
        pos[a]=i;
    }
    int left=n-1;//left记录除零以外不在本位上的个数,巧妙作为判断循环终止条件
    for (int i = 1; i < n; i++)
    {
        if(pos[i]==i){
            left--;
        }
    }
    */

    int left = n - 1, num; //left存放除0以外不在本位上的数的个数
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num);
        pos[num] = i;
        if (num == i && num != 0) //如果除0外有在本位上的数
        {
            left--;
        }
    }

    /*这段代码在测试点1，2上超时了,经过测试原因是for循环中的int k = 1，将它写在循环外即可通过测试
    while (left>0)
    {
        if(pos[0]==0){//如果零在0号位
            for (int k = 1; k < n; k++)//找到最近的不在原位置的数k，初始为1，逐渐线性增长
            {
                if(pos[k]!=k){
                    swap(pos[0],pos[k]);  
                    ans++;
                    break;                  
                }
            }                       
        }
        else{//如果零不在0号位，使它下标回到正确位置
            swap(pos[pos[0]],pos[0]);//有点绕人
            left--;
            ans++;
        }
    }
    */

    int k = 1;
    while (left > 0)
    {
        if (pos[0] == 0)
        {                 //如果零在0号位
            while (k < n) //找到最近的不在原位置的数k，初始为1，逐渐线性增长
            {
                if (pos[k] != k)
                {
                    swap(pos[0], pos[k]);
                    ans++;
                    break;
                }
                k++;
            }
        }
        while (pos[0] != 0)
        {                              //如果零不在0号位，就将0所在位置的数的当前所处位置与0的位置交换
            swap(pos[pos[0]], pos[0]); //有点绕人
            left--;
            ans++;
        }
    }

    printf("%d", ans);
    return 0;
}