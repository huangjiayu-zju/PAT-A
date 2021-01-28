//字典序全排列
#include<cstdio>
const int maxn = 11;
int n, P[maxn], hashTable[maxn] = {false}; //P为当前排列，hashTable记录整数x是否已经在P中

//当前处理排列的第index号位
void generateP(int index){
    if(index == n + 1){	//递归边界，已经处理完排列的1~n位
        for(int i = 1; i <= n; i++){
            printf("%d", P[i]);
        }
        printf("\n");
        return;
    }
    for(int x = 1; x <= n; x++){	//枚举1~n，试图将x填入P[index]
        if(hashTable[x] == false){	//如果x不在P[1]~P[index-1]之中
            P[index] = x;	
            hashTable[x] = true;	//记x已在P中
            generateP(index + 1);	//处理排列的第index+1位
            hashTable[x] = false;	//已处理完P[index]为x的子问题，还原状态
        }
    }  
}
    
int main(){
    n = 4;	//输出1~4的全排列
    generateP(1);	//从P[1]开始填
    return 0;
}