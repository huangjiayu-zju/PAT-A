#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 100;

//将数组A的[L1,R1]与[L2,R2]区间合并为有序区间（此处L2即为R1+1）
void merge(int A[], int L1, int L2, int R1, int R2){
    int i = L1, j = L2;         //i指向A[L1],j指向A[L2]
    int temp[maxn], index = 0;  //temp临时存放合并后的数组，index为其下标
    while (i <= R1 && j <= R2){
        if(A[i] <= A[j]){       //如果A[i]小，则把A[i]加入序列temp
            temp[index++] = A[i++];
        }else{
            temp[index++] = A[j++];
        }
    }
    while(i <= R1){             //将[L1,R1]剩余元素加入序列temp
        temp[index++] = A[i++];
    }
    while(j <= R2){
        temp[index++] = A[j++];
    }
    for (int i = 0; i < index; i++){//将合并后的序列赋值回数组A
        A[L1 + i] = temp[i];
    }    
}

//一、归并排序递归实现
void mergeSort(int A[], int left, int right){//将array数组当前区间[left, right]进行归并排序
    if(left < right){   //只要left小于right
        int mid = (left + right) / 2;   //取中点
        mergeSort(A, left, mid);        //递归，将左子区间[left,mid]归并排序
        mergeSort(A, mid + 1, right);   //递归，将右子区间[mid+1,right]归并排序
        merge(A, left, mid, mid + 1, right);//将左子区间和右子区间合并
    }
}


//二、归并排序非递归实现
int n;  //n为元素个数，数组下标从1开始，如果从0开始的写法看A1089
void mergeSort(int A[]){
    //step为组内元素个数，step / 2为左子区间元素个数，注意等号可以不取
    for (int step = 2; step / 2 <= n; step *= 2){
        //每step个元素一组，组内前step/2和后step/2个元素合并
        for (int i = 1; i <= n; i+= step){  //数组下标从1开始，对每一组
            int mid = i + step / 2 - 1;     //左子区间元素个数为step/2
            if(mid + 1 <= n){               //右子区间存在元素则合并
                //左子区间为[i,mid]，右子区间为[mid + 1, min(i + step - 1, n)]
                merge(A, i, mid, mid + 1, min(i + step - 1, n));
            }
        }
    }
}

//如果题目只要求给出归并排序每一趟结束时的序列，完全可以使用sort函数来代替merge函数
void mergeSort(int A[]){
    for(int step = 2; step / 2 <= n; step *= 2){
        for (int i = 1; i <= n; i+= step){
            sort(A + i, A + min(i + step, n + 1));
        }
        //此处可以输出归并排序的某一趟结束的序列
    }
}

