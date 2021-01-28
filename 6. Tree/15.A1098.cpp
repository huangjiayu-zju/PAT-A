#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 110;

int origin[maxn], tempOri[maxn], changed[maxn]; //原始数组、中间数组及目标数组
int n;  //元素个数

bool isSame(int A[], int B[]){
    for (int i = 1; i <= n; i++)
    {
        if(A[i] != B[i]){
            return false;
        }
    }
    return true;
}

void showArray(int A[]){
    for (int i = 1; i <= n; i++)
    {
        printf("%d", A[i]);
        if(i < n){
            printf(" ");
        }
    }
    printf("\n");
}

bool insert(){  //插入排序
    bool flag = false;  //记录是否存在数组中间步骤与changed数组相同
    for (int i = 2; i <= n; i++){
        if(i != 2 && isSame(tempOri, changed)){ //中间步骤与目标相同且不是初始序列 
            flag = true;
        }
        sort(tempOri, tempOri + i + 1); //插入部分直接用sort代替
        if(flag == true){
            return true;
        }
    }
    return false;
}

void downAdjust(int low, int high){//[i,n]
    int i = low, j = 2 * i;
    while(j <= high){
        if(j + 1 <= high && tempOri[j + 1] > tempOri[j]){
            j = j + 1;
        }
        if(tempOri[j] > tempOri[i]){
            swap(tempOri[j], tempOri[i]);
            i = j;
            j = 2 * i;
        }else{
            break;
        }
    }
}

void heapSort()
{
    bool flag = false;
    for (int i = n / 2; i > 0; i--){ //建堆
        downAdjust(i, n);
    }
    for (int i = n; i >= 1; i--){
        if(i != n && isSame(changed,tempOri)){  //中间步骤与目标相同且不是初始序列
            flag = true;
        }
        swap(tempOri[i], tempOri[1]);//交换heap[i]与堆顶
        downAdjust(1, i - 1);//调整堆顶
        if(flag == true){
            showArray(tempOri);
            return;
        }
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d",&origin[i]);
        tempOri[i] = origin[i];
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &changed[i]);
    }
    if(insert()){
        printf("Insertion Sort\n");
        showArray(tempOri);
    }else{
        printf("Heap Sort\n");
        for (int i = 1; i <= n; i++)
        {
            tempOri[i] = origin[i]; // 还tempOro数组
        }
        heapSort();
    }
    return 0;
}