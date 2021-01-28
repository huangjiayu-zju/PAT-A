#include<cstdio>
#include<map>
using namespace std;

int main(){
    int m, n, col;
    scanf("%d %d", &m,&n);
    map<int, int> count;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++){
            scanf("%d", &col);
            if(count.find(col)!=count.end()){//在map中查找val，如果找到则count+1
                count[col]++;
            }
            else{
                count[col] = 1;
            }
        }
    }
    int k = 0, max = 0;
    for (map<int, int>::iterator it = count.begin(); it != count.end(); it++){
        if(it->second > max){
            k = it->first;
            max = it->second;
        }
    }
    printf("%d\n",k);
    return 0;
}