#include<cstdio>
#include<algorithm>
using namespace std;
int num[5];

bool cmp(int a, int b){//递减排序
    return a > b;
}

void to_array(int n){//将n的每一位存入num中
    for (int i = 0; i <4 ; i++)
    {
        num[i] = n % 10;
        n /= 10;
    }
}

int to_number(){
    int sum = 0;
    for (int i = 0; i < 4; i++)
    {
        sum = sum * 10 + num[i];
    }
    return sum;
}

int main(){
    int n, min, max;
    scanf("%d", &n);
    while(1){
        to_array(n);
        sort(num, num + 4);//默认递增排序
        min = to_number();
        sort(num, num + 4, cmp);
        max = to_number();
        n = max - min;
        printf("%04d - %04d = %04d\n", max, min, n);
        if(n==0||n==6174){
            break;
        }
    }
    return 0;
}
