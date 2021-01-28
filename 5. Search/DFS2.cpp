#include<cstdio>
#include<vector>
using namespace std;
const int maxn = 1001;
int n, k, x, maxSumSqu = -1, A[maxn];//序列A中n个数选出k个数使得和为x，最大平方和为maxSumSqu
vector<int> temp, ans;//temp存放临时方案，ans存放平方和最大的方案
//当前处理index号整数，当前已选整数个数为nowK，当前已选整数和为sum，已选整数平方和为sumSqu
void DFS(int index, int nowK, int sum, int sumSqu){
    if(nowK == k && sum == x){//找到k个数和为x
        if(sumSqu > maxSumSqu){//更新最优方案
            maxSumSqu = sumSqu;
            ans = temp;
        }
        return;
    }
    //已经处理完n个数，或者超过k个数，或者和超过x。直接返回
    if(index == n || nowK > k || sum > x){
        return;
    }
    //选index号数
    temp.push_back(A[index]);
    DFS(index + 1, nowK + 1, sum + A[index], sumSqu + A[index] * A[index]);
    temp.pop_back();
    //不选index号数
    DFS(index + 1, nowK, sum, sumSqu);
}
