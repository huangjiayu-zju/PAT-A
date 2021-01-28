#include<cstdio>
#include<cmath>
const int maxn = 20;

int n, count = 0;//n为棋盘大小，count记录合法的方案数
int P[maxn]; //p[i]记录第i列皇后的行号
bool hashTable[maxn] = {false};//hashTable[i]=false表示第i行没有皇后

void generateP(int index){
    if (index == n + 1){ //设置递归边界
        count++; //能达到这里说明是符合条件的
        return;
    }
    for (int x = 1; x <= n; x++){ //第x行
        if (hashTable[x] == false){  //如果第x行没有皇后
            bool flag = true; //表示和之前的皇后不会有冲突
            for(int pre = 1; pre < index; pre++){   //遍历之前的皇后
                //第index列皇后的行号为x，第pre列皇后的行号为P[pre]
                if (abs(index - pre) == abs(x - P[pre])){
                    flag = false; //与之前一个皇后的一条对角线冲突
                    break;
                }
            }
            if (flag){                //如果可以把皇后放在第x行
                P[index] = x;         //令第index列皇后的行号为x
                hashTable[x] = true;  //第x行已经被占用
                generateP(index + 1); //递归处理第index+1行皇后
                hashTable[x] = false; //递归完毕，还原第x行为未占用
            }
        }
    }
}

int main(){
    n = 8;
    generateP(1);
    printf("%d\n", count);
    return 0;
}