#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn = 10010;
struct Person{
    char name[10];
    int height;
} person[maxn];

bool cmp(Person a, Person b){
    if(a.height != b.height){
        return a.height > b.height;
    }else{
        return strcmp(a.name, b.name) < 0;
    }
}

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
    {
        scanf("%s%d", person[i].name, &person[i].height);
    }
    sort(person, person + n, cmp);
    int num = n - (k - 1) * (n / k), leftPos = 0;//num为最后一排人数，leftPos为当前排的最左端为止
    while(leftPos < n){ 
        deque<int> personInDeque;
        for (int i = leftPos; i <= leftPos + num - 1; i++){
            if ((i - leftPos) % 2 == 0){
                personInDeque.push_back(i); //偶号插入队尾
            }else{
                personInDeque.push_front(i);//奇号插入队首
            }
        }
        while(!personInDeque.empty()){
            printf("%s", person[personInDeque.front()].name);
            personInDeque.pop_front();  //  弹出队首
            if(!personInDeque.empty()){
                printf(" ");
            }else{
                printf("\n");
            }
        }
        leftPos += num;
        num = n / k;
    }

    return 0;
}











