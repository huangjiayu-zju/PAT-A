## 简单数学 1-5

## 最大公约数与最小公倍数 6

求解最大公约数

```c
int gcd(int a, int b){
    if(b == 0) return a;
    else return gcd(b,a % b);
}
```
或者
```c
int gcd(int a, int b){
    return !b ? a : gcd(b, a % b);
}
```
求解最小公倍数
先求得最大公约数d，最小公倍数为`a/d*b`,因为a*b可能会溢出。
## 分数的四则运算 7,8

分数的表示
```c
struct Fraction{//分数
    int up, dpwn;//分子，分母
};
```
分数的化简：
1. 如果分母down为负数，那么令分子uo和分母down都变为相反数（使down为非负数）
2. 如果分子uo为0，呢么令分母down为1
3. 约分：求出分子绝对值与分母绝对值的最大公约数d，然后令分子分母同时除以d

分数的输出：
1. 化简 
2. 如果分数r的分母down为1，说明是整数，直接输出分子
3. 如果分数r的分子up绝对值大于分母down，说明分数是真分数，应按带分数的形式输出，即整数部分为`r.up/r.down`，分子部分为`abs(r.up)%r.down`，分母部分为`r.down`。

注意：由于分数的乘法和除法过程中可能使分子或分母超过int型表示范围，因此一般情况下分子和分母使用longlong型存储】

## 素数 9,10
判断是否是素数`O(sqrt(n))`
```c
bool isPrime(int n){
    if(n<=1){
        return false;
    }
    int sqr = (int)sqrt(n * 1.0);
    for (int i = 2; i <= sqr; i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}
```

素数表获取：埃氏筛法 `O(nloglogn)`
```c
const int maxn = 101;//表长
int prime[maxn], pNum=0;//prime存放所有素数，pNum为素数个数
bool p[maxn]={0};
void Find_prime(){
    for(int i = 2;i < maxn; i++){//从2开始，//不能写成i <= maxn
        if(p[i]==false){
            prime[pNum++]=i;
            for(int j = i + i;j < maxn; j += i){//不能写成j <= maxn
                p[j] = true;
            }
        }
    }
}
```

## 质因子分解 11,12
先打印素数表prime[i]
定义结构体factor，存放质因子及其个数
```
struct factor{
    int x, cnt; //x为质因子，cnt为其个数
}fac[10];
```
考虑到2*3*5*7*11*13*17*19*23*29已经超过了int范围，因此对一个int型的数来说，fac数组大小只需要开到10就可以了

核心思想：对整数n来说，如果它存在[2,n]范围内的质因子，要么这些质因子全部小于等于sqrt(n)，要么只存在一个大于sqrt(n)的质因子，而其余质因子全部小于等于sqrt(n)。
1. 枚举1~sqrt(n)内的所有质因子p，判断p是否是n的因子
    - 如果p是因子，给fac数组中增加质因子p，初始化其个数为0.然后只要p还是n的因子，就让n不断除以p，每次操作令p的个数加1，直到p不再是n的因子为止
    - 如果p不是因子，则跳过。
    ```c
    if(n % prime[i] == 0){
        fac[num].x = n;
        fac[num].cnt = 0;
        while(n%prime[i]==0){
            fac[num].cnt++;
            n /= prime[i];
        }
        num++;
    }
    ```
2. 如果上面步骤结束后n仍然大于1，说明n有且仅有一个大于srqt(n)的质因子（有可能是n本身），这时将这个质因子加入fac数组，并令其个数为1.
```c
if(n != 1){
    fac[num].x = n;
    fac[num++].cnt = 1;
}
```
## 大整数存储 13,14
按顺位存储：整数的高位存储在数组的高位，整数的低位存储在数组的低位。如整数235813，有d[0]=3,d[1]=1.d[2]=8,d[3]=5,d[4]=3,d[5]=2。原因是进行运算的时候都是从整数的低位到高位进行枚举。因此注意当把整数按字符串%s读入的时候，实际上是逆位存储的，即str[0]='2',str[1]='3',...,str[5]='3'，因此在读入后需要在另存至d[]数组的时候反转一下。


## 扩展欧几里得算法
- 扩展欧几里得算法
- 方程ax+by=c的求解
- 同余式ax=c(mod m)的求解
- 逆元的求解


## 组合数
*求n!中有多少个质因子p*

直观的想法是计算1~n中的每个数各有多少个质因子p，然后将结果累加，时间复杂度为`O(nlogn)`

优化：时间复杂度为`O(logn)`的算法
```c
int cal(int n, int p){
    int ans = 0;
    while(n){
        ans += n/p;//累加n/p^k
        n /= p;
    }
    return ans;
}
```
还可以推导出：n!中质因子p的个数，实际上等于1~n中p的倍数的个数n/p加上(n/p)!中质因子p的个数，递归代码如下
```
int cal(int n, int p){
    if(n < p) return 0;
    return n/p + cal(n/p,p);
}
```

*组合数的计算*

计算$C^m_n$：时间复杂度为`O(m)`
```c
long long C(long long n, long long m){
    long long ans = 1;
    for(long long i = 1; i <= m; i++){
        ans = ans * (n - m + i) / i;//注意一定要先乘再除
    }
    return ans;
}
```
计算$C^m_n\%p$
- 递归
    ```c
    int res[1010][1010] = {0};
    int C(int n, int m, int p){
        if(m = 0|| m = n) return 1;
        if(res[n][m]!=0) return res[n][m];
        return res[n][m] = (C(n-1,m) + C(n-1,m-1)) % p;
    }
    ```
- 递推
    ```c
    void calC(){
        for(int i = 0; i <= n; i++){
            res[i][0] = res[i][i] = 1;//初始化边界
        }
        for(int i = 2; i <= n; i++){
            for(int j = 0; j <= i/2; j++){
                res[i][j] = (res[i][j-1]+res[i-1][j-1]) % p;
                res[i][i-j] = res[i][j];//C(i,i-j)=C(i,j)
            }
        }
    }
    ```