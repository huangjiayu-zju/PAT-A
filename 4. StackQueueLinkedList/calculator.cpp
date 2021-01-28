#include<iostream>
#include<cstdio>
#include<string>
#include<stack>
#include<queue>
#include<map>
using namespace std;

struct node{
    double num; //操作数
    char op;    //操作符
    bool flag;  //true表示操作数，false表示操作符
};

string str;
stack<node> s;  //操作符栈
queue<node> q;  //后缀表达式序列
map<char, int> op;

void change(){  //中缀表达式转换为后缀表达式
    node temp;
    for (int i = 0; i < str.length(); ){
        if(str[i] >= '0' && str[i] <= '9'){ //如果是数字
            temp.flag = true;
            temp.num = str[i++] - '0';  //记录这个操作数的第一个数位
            while (i < str.length() && str[i] >= '0' && str[i] <= '9'){
                temp.num = temp.num * 10 + (str[i] - '0');  //更新这个操作数
                i++;
            }
            q.push(temp);   
        }else{  
            temp.flag = false;
            while(!s.empty() && op[str[i]] <= op[s.top().op]){
                q.push(s.top());
                s.pop();
            }
            temp.op = str[i];
            s.push(temp);
            i++;
        }
    }
    while(!s.empty()){
        q.push(s.top());
        s.pop();
    }
}

double cal(){   //计算后缀表达式
    double temp1, temp2;
    node cur, temp;
    while(!q.empty()){
        cur = q.front();//cur记录队首元素
        q.pop();
        if(cur.flag == true){   //如果是操作数，直接压入栈
            s.push(cur);
        }else{
            temp2 = s.top().num;
            s.pop();
            temp1 = s.top().num;
            s.pop();
            temp.flag = true;   //临时记录操作数
            if(cur.op == '+'){
                temp.num = temp1 + temp2;
            }else if(cur.op == '-'){
                temp.num = temp1 - temp2;
            }else if(cur.op == '*'){
                temp.num = temp1 * temp2;
            }else{
                temp.num = temp1 / temp2;
            }
            s.push(temp);   //把该操作数压入栈
        }
    }
    return s.top().num; //栈顶元素就是后缀表达式的值
}

int main(){
    op['+'] = op['-'] = 1;  //设定操作符的优先级,‘(’默认为0了，优先级最低
    op['*'] = op['/'] = 2;
    while (getline(cin, str), str != "0"){  //题目要求当一行中只有0时输入结束
        for (string::iterator it = str.end(); it != str.begin(); it--){
            if (*it == ' '){
                str.erase(it);  //把表达式中的空格全部去掉
            }
        }
        while(!s.empty()){  //初始化栈
            s.pop();
        }
        change();
        printf("%.2f\n", cal());
        return 0;
    }
}






