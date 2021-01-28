#include<cstdio>
int num[10];
int main(){
    int a, b, sum;
    scanf("%d%d",&a, &b);
    sum = a + b;//将a+b赋值给sum
    if(sum < 0){//sum为负数时，输出负号并取相反数
        printf("-");
        sum = -sum;
    }
    int len = 0;//len存放sum长度
    if(sum == 0){
        num[len++] = 0; //因为用的是while写法而不是do..while写法，在sum=0时len会等于0，实际上是等于1的
    }
    //将sum数组存入数组num中，其中sum的低位存放到num[]的低位
    while(sum){
        num[len++] = sum % 10;
        sum /= 10;
    }
    for (int k = len - 1; k >= 0; k--){//数组逆序存储，从高位开始输出
        printf("%d", num[k]);
        if (k > 0 && k % 3 == 0){//最低位后面不需要输出逗号，故k不能为0
            printf(",");
        }
    }
    return 0;
}
