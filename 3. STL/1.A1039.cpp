#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 40010;//总人数
const int M = 26 * 26 * 26 * 10;//由姓名组成的散列上界
vector<int> selectCourse[M]; //每个学生选择的课程编号

int getID(char name[]){//字符串hash
    int id = 0;
    for (int i = 0; i < 3; i++)
    {
        id = id * 26 + (name[i] - 'A');
    }
    id = id * 10 + (name[3] - '0');
    return id;
}

int main(){
    char name[5];
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; i++)
    {
        int course, x;
        scanf("%d%d", &course, &x);
        for (int j = 0; j < x; j++){
            scanf("%s", name);
            selectCourse[getID(name)].push_back(course);
        }
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%s", name);
        int id = getID(name);
        sort(selectCourse[id].begin(), selectCourse[id].end());//从小到大排序
        printf("%s %d", name, selectCourse[id].size());//姓名，选课数
        for (int j = 0; j < selectCourse[id].size(); j++)
        {
            printf(" %d", selectCourse[id][j]);
        }
        printf("\n"); 
    }
    return 0;
}