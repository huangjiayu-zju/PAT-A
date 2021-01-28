#include<cstdio>
#include<stack>
using namespace std;
const int maxn = 1010;
int arr[maxn];//保存题目给的出栈序列
stack<int> st;

int main(){
    int m, n, k;
    scanf("%d%d%d", &m, &n, &k);
    while(k--){
        while(!st.empty()){//处理完上一个出栈序列，应清空栈
            st.pop();
        }
        for (int i = 1; i <= n; i++)//读入出栈序列，注意从1开始
        {
            scanf("%d", &arr[i]);
        }
        int current = 1;//指向出栈序列中的待出栈元素
        bool flag = true;//表示出栈序列合法
        for (int i = 1; i <= n; i++)
        {
            st.push(i);
            if(st.size() > m){//先判断栈内元素数量是否越界
                flag = false;
                break;
            }
            while(!st.empty() && st.top() == arr[current]){//这里要用while而不是if，因为要反复判断
                st.pop();
                current++;
            }            
        }
        if(st.empty()&&flag){
            printf("YES\n");
        }        
        else{
            printf("NO\n");
        }
    }
}