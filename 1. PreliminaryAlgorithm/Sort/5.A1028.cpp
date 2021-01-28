#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

struct Student
{
    int id;
    char name[10];
    int score;
} stu[100010];

bool cmp1(Student a, Student b)
{
    return a.id < b.id;
}

bool cmp2(Student a, Student b)
{
    if (strcmp(a.name, b.name) != 0)
        return strcmp(a.name, b.name) < 0;
    else
        return a.id < b.id;
}

bool cmp3(Student a, Student b)
{
    if (a.score != b.score)
        return a.score < b.score;
    else
        return a.id < b.id;
}

int main()
{
    int n, c;
    scanf("%d%d", &n, &c);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%s%d", &stu[i].id, stu[i].name, &stu[i].score);
    }
    switch (c)
    {
    case 1:
        sort(stu, stu + n, cmp1);
        break;
    case 2:
        sort(stu, stu + n, cmp2);
        break;
    case 3:
        sort(stu, stu + n, cmp3);
        break;
    default:
        break;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%06d %s %d\n", stu[i].id, stu[i].name, stu[i].score);
    }
    return 0;
}