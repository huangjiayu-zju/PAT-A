#include<cstdio>
#include<cstring>
char num[10][5] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
char wei[5][5] = {"Shi", "Bai", "Qian", "Wan", "Yi"};

int main(){
    char str[15];
    scanf("%s", str);
    int len = strlen(str);
    int left = 0, right = len - 1;//left和right来处理数字的每一个节（个节、万节、亿节）的输出
    if(str[0] == '-'){
        printf("Fu");
        left++;
    }
    while(left + 4 <= right){//left指向当前需要输出的位，而right指向与left同节的个位
        right -= 4;//right每次左移4位直到left与right在同一节
    }
    while (left < len){         //循环每次处理数字的一节（4位或小于4位）
        bool flag = false;      //false表示没有累积的0
        bool isPrint = false;   //false表示该节没有输出过其中的位
        while(left <= right){   //从左至右处理数字中某节的每一位
            if(left > 0 && str[left] == '0'){//如果当前位为0
                flag = true;
            }else{  //如果当前位不为0
                if(flag == true){//如果存在累积的0
                    printf(" ling");
                    flag = false;
                }
                //只要不是首位（包括负号），后面的每一位前都要输出空格
                if(left > 0){
                    printf(" ");
                }
                printf("%s", num[str[left] - '0']);//输出当前位数字
                isPrint = true;     //该节至少有一位被输出
                if(left != right){  //某节中除了个位外，都要输出十百千
                    printf(" %s", wei[right - left - 1]);
                }
            }
            left++;//left右移一位
        }
        if (isPrint == true && right != len - 1){//主要不是个位，就输出万或亿
            printf(" %s", wei[(len - 1 - right) / 4 + 2]);
        }
        right += 4;
    }
    return 0;
}






