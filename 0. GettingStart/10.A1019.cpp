#include<cstdio>

bool Judge(int z[], int num){//判断数组z所存的数是否为回文数，num为位数
    for (int i = 0; i < num / 2; i++){
        if(z[i] != z[num - 1 -i]){//如果位置i与其对称位置num-i-i不相同
            return false;
        }
    }
    return true;
}

int main(){
    int n, b, z[40], num = 0;
    scanf("%d%d", &n, &b);
    do{
        z[num++] = n % b;
        n /= b;
    } while (n != 0);//do-while是防止特殊情况n=0时要有z[0]=0。
    bool flag = Judge(z, num);
    if(flag == true){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
    for (int i = num - 1; i >= 0; i--)//数组z中存储的是b进制的逆序，要倒着输出
    {
        printf("%d", z[i]);
        if(i != 0){
            printf(" ");
        }
    }
    return 0;
}