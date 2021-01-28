#include<cstdio>
#include<iostream>
#include<string>
using namespace std;

bool isLegal(string input){
    if(input[0] == '-'){
        input.erase(input.begin());
    }
    if(input.length() == 0){
        return false;   //去掉负号后如果长度为0则不合法
    }
    int dotPos = -1;//记录小数点的下标
    for (int i = 0; i < input.length(); i++){
        if (!(input[i] == '.' || (input[i] >= '0' && input[i] <= '9'))){
            return false;   //如果出现了小数点或者0到9以外的字符，那么不合法
        }
        if(input[i] == '.'){
            if(dotPos != -1){//如果前面已经出现过小数点，那么不合法
                return false;
            }else{
                dotPos = i;
            }
        }
    }
    if(dotPos != -1 && dotPos + 3 < input.length()){
        return false;   //存在小数点且小数点后超过2位小数时，不合法
    }
    double tempNumber;
    sscanf(input.c_str(), "%lf", &tempNumber);//将字符串转换为double型
    return tempNumber <= 1000;
}

int main(){
    int n, num = 0;//n为输入数的个数，num为合法的数的个数
    cin >> n;
    double sum = 0, tempNumber;//sum为合法数的和，tempNumber临时存放数字
    string input;
    for (int i = 0; i < n; i++)
    {
        cin >> input;
        if(isLegal(input)){
            sscanf(input.c_str(), "%lf", &tempNumber);
            sum += tempNumber;
            num++;
        }else{
            printf("ERROR: %s is not a legal number\n", input.c_str());
        }
    }
    if(num == 0){
        printf("The average of 0 numbers is Undefined\n");
    }else if(num == 1){
        printf("The average of 1 number is %.2f\n", sum);
    }else{
        printf("The average of %d numbers is %.2f\n", num, sum / num);
    }
    return 0;
}