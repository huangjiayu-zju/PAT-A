#include<cstdio>
#include<string.h>
struct bign{
    int d[21];
    int len;
    bign(){
        memset(d, 0, sizeof(d));
        len = 0;
    }
};

bign change(char str[]){
    bign a;
    a.len = strlen(str);
    for (int i = 0; i < a.len; i++)
    {
        a.d[i] = str[a.len - i - 1] - '0';
    }
    return a;
}

bign multi(bign a, int b){
    bign c;
    int carry = 0;
    for (int i = 0; i < a.len; i++)
    {
        int temp = a.d[i] * b + carry;
        c.d[c.len++] = temp % 10;
        carry = temp / 10;
    }
    while(carry != 0){
        c.d[c.len++] = carry % 10;
        carry /= 10;
    }
    return c;
}

bool Judge(bign a, bign b){//判断b的所有位是否是a的某个排列
    if(a.len != b.len){
        return false;
    }
    int count[10] = {0}; //计算0~9的出现次数
    for (int i = 0; i < a.len; i++)
    {
        count[a.d[i]]++;
        count[b.d[i]]--;
    }
    for (int i = 0; i < 10; i++)//枚举完所有数位后，所有count数组元素的值应该均为0则返回true
    {
        if(count[i] != 0){
            return false;
        }
    }
    return true;
}

void print(bign a){
    for (int i = a.len-1; i >= 0; i--)
    {
        printf("%d", a.d[i]);
    }
}

int main(){
    char str[21];
    scanf("%s", str);
    bign a = change(str);
    bign mul = multi(a, 2);
    if(Judge(a, mul) == true){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
    print(mul);
    return 0;
}