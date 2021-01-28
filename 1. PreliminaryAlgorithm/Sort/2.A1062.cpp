#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//根据题意添加sum与flag变量
struct Student
{
    char id[10];
    int tal, vir, sum;
    int flag;//考生类别：第1~5类
} stu[100010];

bool cmp(Student a, Student b)
{
    if (a.flag != b.flag)
        return a.flag < b.flag; //类别小的在前
    else if (a.sum != b.sum)
        return a.sum > b.sum;   //类别相同时，总分大的在前
    else if (a.vir != b.vir)
        return a.vir > b.vir;   //总分相同时，德分大的在前
    else
        return strcmp(a.id, b.id) < 0;//德分相同时，准考证小的在前
}

int main()
{
    int n, l, h;
    scanf("%d%d%d", &n, &l, &h);
    int m = n; //题目要求输出及格人数
    for (int i = 0; i < n; i++)
    {
        scanf("%s%d%d", stu[i].id, &stu[i].vir, &stu[i].tal);
        stu[i].sum = stu[i].vir + stu[i].tal;
        if (stu[i].vir < l || stu[i].tal < l)
        {
            stu[i].flag = 5;
            m--;
        }
        else if (stu[i].vir >= h && stu[i].tal >= h)
            stu[i].flag = 1;
        else if (stu[i].vir >= h && stu[i].tal < h)
            stu[i].flag = 2;
        else if (stu[i].vir >= stu[i].tal)
            stu[i].flag = 3;
        else
            stu[i].flag = 4;
    }
    sort(stu, stu + n, cmp); //注意这里是将所有n个都排序而后面输出前m个
    printf("%d\n", m);
    for (int i = 0; i < m; i++)
    {
        printf("%s %d %d\n", stu[i].id, stu[i].vir, stu[i].tal);
    }
    return 0;
}