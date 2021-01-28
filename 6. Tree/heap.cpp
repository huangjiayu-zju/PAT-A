#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 110;

int heap[maxn], n = 10; //heap为堆，n为元素个数

//向下调整，时间复杂度为O(logn)
//对heap数组在[low,high]范围进行向下取整,low为欲调整结点的数组下标，high一般为堆的最后一个元素的数组下标
void downAdjust(int low, int high){
    int i = low, j = i * 2; //i为欲调整结点，j为其左孩子
    while(j <= high){   //存在孩子结点
        //如果右孩子存在，且右孩子值大于左孩子
        if(j + 1 <= high && heap[j+1] > heap[j]){
            j = j + 1;
        }
        //如果孩子中最大的权值比欲调整结点i大
        if(heap[j] > heap[i]){
            swap(heap[j], heap[i]); //交换
            i = j;  //保持i为欲调整结点，j为i的左孩子,进入下一循环      
            j = i * 2;
        }else{
            break;
        }
    }
}

//建堆,时间复杂度O(n)
void createHeap(){
    for (int i = n / 2; i >= 1; i--)//倒着枚举保证每个结点都是以其为根结点的子树中的权值最大的点
    {
        downAdjust(i, n);
    }    
}
//删除堆顶元素，时间复杂度O(logn)
void deleteTop(){
    heap[1] = heap[n--];    //用最后一个元素覆盖堆顶元素，并让元素个数减1
    downAdjust(1, n);
}

//向上调整，时间复杂度为O(logn)
//对heap数组在[low,high]范围进行向下取整,low一般设置为1，high欲调整结点的数组下标
void upAdjust(int low, int high){
    int i = high, j = i / 2;    //i为欲调整结点，j为其父亲
    while(j >= low){    //父亲在[low,high]内
        if(heap[j] < heap[i]){  //父亲权值小于欲调整结点的权值
            swap(heap[j], heap[i]);
            i = j;
            j = i / 2;
        }else{
            break;
        }
    }
}

//添加元素
void insert(int x){
    heap[++n] = x;
    upAdjust(1, n);
}

//堆排序
void heapSort(){
    createHeap();//建堆
    for (int i = n; i > 1; i--){    //倒着枚举直到堆中只有一个元素
        swap(heap[1], heap[i]); //交换heap[i]与堆顶
        downAdjust(1, i - 1);   //调整堆顶
    }
    
}