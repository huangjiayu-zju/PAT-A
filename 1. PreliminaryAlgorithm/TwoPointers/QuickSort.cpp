#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

//对区间[left, right]进行划分
int Partition(int A[], int left, int right){
    int temp = A[left]; //将A[left]存放至临时变量temp
    while(left < right){//只要left与right不相遇
        while(left < right && A[right] > temp){ //反复左移right
            right--;
        }
        A[left] = A[right]; //将A[right]挪到A[left]
        while(left < right && A[left] <= temp){ //反复右移left
            left++;         
        }
        A[right] = A[left]; //将A[left]挪到A[right]
    }
    A[left] = temp; //把temp放到left与right相遇的地方
    return left;    //返回相遇的下标
}

//快速排序，left与right初值为序列首尾下标（例如1与n）
void quickSort(int A[], int left, int right){
    if(left < right){   //当前区间长度超过1
        int pos = Partition(A, left, right);//将[left,right]按A[left]一分为二，返回相遇的下标
        quickSort(A, left, pos - 1);    //对左子区间递归进行快速排序
        quickSort(A, pos + 1, right);   //对右子区间递归进行快速排序
    }
}

//选取随机主元，生成范围在[left,right]内的随机数p，然后以A[p]作为主元来进行划分
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

//随机选择算法，从A[left, right]返回第k大的数
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