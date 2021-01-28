#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 100010;
int A[maxn], n; //A存放所有整数，n为其个数

int randPartition(int A[], int left, int right){
    int p = round(1.0 * rand() / RAND_MAX * (right - left) + left);
    swap(A[p], A[left]);    //交换A[p]与A[left]
    //下面为原先Partition函数的划分过程，不需要改变任何东西
    int temp = A[left]; 
    while(left < right){
        while(left < right && A[right] > temp){ 
            right--;
        }
        A[left] = A[right]; 
        while(left < right && A[left] <= temp){ 
            left++;         
        }
        A[right] = A[left]; 
    }
    A[left] = temp; 
    return left;    
}

int randSelect(int A[], int left, int right, int K){
    if(left == right){
        return A[left]; //边界
    }
    int p = randPartition(A, left, right);  //划分后主元的位置为p
    int M = p - left - 1;   //A[p]是A[left,right]中的第M大
    if(K == M){ //找到第K大的数
        return A[p];
    }
    if(K < M){  //第K大的数在主元左侧
        return randSelect(A, left, p - 1, K);   //往左侧找第K大
    }else{  //第K大的数在主元右侧
        return randSelect(A, p + 1, right, K - M);  //往主元右侧找第K-M大
    }
}

int main(){
    srand((unsigned)time(NULL)); //初始化随机数种子
    //sum和sum1记录所有整数之和与切分后前n/2个元素之和
    int sum = 0, sum1 = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d", &A[i]);
        sum += A[i];
    }
    randSelect(A, 0, n - 1, n / 2);
    for (int i = 0; i < n / 2;i++){
        sum1 += A[i];
    }
    printf("%d\n", (sum - sum1) - sum1);
    return 0;
}