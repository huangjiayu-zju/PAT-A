#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;

//先将所有人排序，然后进行预处理，将每个年龄中财富前100内的人全部存到另一个数组中，后面的查询操作均在这个新数组中进行
int Age[200] = {0}; //某年龄的人数
struct People
{
    char name[10];
    int age;
    int worth;
} people[maxn], valid[maxn]; //所有人，valid排除了在各自年龄中财富值在100名以外的人

bool cmp(People a, People b)
{
    if (a.worth != b.worth)
        return a.worth > b.worth;
    else if (a.age != b.age)
        return a.age < b.age;
    else
        return strcmp(a.name, b.name) < 0;
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
    {
        scanf("%s%d%d", people[i].name, &people[i].age, &people[i].worth);
    }
    sort(people, people + n, cmp);

    int validNum = 0; //存放到valid数组中的人数

    for (int i = 0; i < n; i++)
    { //对于按财富值排好序的数组，将每一年龄的前100人记录在新数组valid中
        if (Age[people[i].age] < 100)
        {                                  //如果某一年龄的人数小于100
            Age[people[i].age]++;          //该年龄的人数加一
            valid[validNum++] = people[i]; //将people[i]加入新数组中，新数组同样是排好序的
        }
    }

    //接下来进行K次查询，输出在给定区间[ageL,ageR]内的财富值
    int m, ageL, ageR;
    for (int i = 1; i <= k; i++) //以1开始因为要输出casei
    {
        scanf("%d%d%d", &m, &ageL, &ageR);
        printf("Case #%d:\n", i);
        int printNum = 0; //已输出的人数
        for (int j = 0; j < validNum && printNum < m; j++)
        { //遍历新数组找出符合条件的前m人
            if (valid[j].age >= ageL && valid[j].age <= ageR)
            {
                printf("%s %d %d\n", valid[j].name, valid[j].age, valid[j].worth);
                printNum++;
            }
        }
        if (printNum == 0)
            printf("None\n");
    }
    return 0;
}