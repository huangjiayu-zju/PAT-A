#include<cstdio>
#include<cstring>

int main(){
    char str[10000];
    scanf("%s", str);
    int len = strlen(str);
    if(str[0] == '-'){//如果是负数，输出负号
        printf("-");
    }

    int pos = 0;//pos存放字符串中E的位置
    while(str[pos] != 'E'){
        pos++;
    }

    int exp = 0;//exp存放指数的值，先不考虑正负
    for (int i = pos + 2; i < len; i++)//指数的起点是E后面的第二位
    {
        exp = exp * 10 + (str[i] - '0');
    }
    if (exp == 0){//特判指数为0的情况
        for (int i = 1; i < pos; i++){
            printf("%c", str[i]);
        }
    }

    if (str[pos + 1] == '-'){//如果指数为负，一定是输出0.00...0XXX,小数点后0的个数为exp-1
        printf("0.");
        for (int i = 0; i < exp - 1; i++){
            printf("0");
        }
        printf("%c", str[1]);//输出除了小数点以外的数字
        for (int i = 3; i < pos; i++){
            printf("%c", str[i]);
        }
    }else{//如果指数为正，主要考虑小数点移动后的位置。当exp非零时，小数点添加在原标号为exp+2的数字后
        for (int i = 1; i < pos; i++){//输出小数点移动之后的数
            if(str[i] == '.'){//略过原小数点
                continue;
            }
            printf("%c", str[i]);
            if(i == exp + 2 && pos - 3 != exp){ //小数点加在位置(exp + 2)上
                printf(".");//原小数点和E之间的数字个数(pos - 3)不能等于小数点后移位数exp
            }
        }
        //如果指数exp较大，输出多余的0
        for (int i = 0; i < exp - (pos - 3); i++){
            printf("0");
        }
    }
    return 0;
}