#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

/*
分数据处理与输出两部分
数据处理：要求我们先计算并存储每个学生在每门课中的排名
数据输出：难点在于优先级的设定
- 很巧妙的用Rank[id][4]来存储特定学号的学生四门课的排名
- 定义变量now在cmp函数针对不同学科输出排序结果
- 优先级的设定
*/

//对每个学生来说的各科优先级
struct Student
{
    int id;       //id较小可以用int型
    int grade[4]; //存放A,C,M,E成绩
} stu[2010];

char course[4] = {'A', 'C', 'M', 'E'};
int Rank[1000000][4] = {0};
int now; //cmp函数中使用，表示当前按now号的分数排序stu数组

bool cmp(Student a, Student b)
{
    return a.grade[now] > b.grade[now]; //stu数组按now号分数递减排序
}

int main()
{
    int n, m;
    //先输入数据
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d%d%d", &stu[i].id, &stu[i].grade[1], &stu[i].grade[2], &stu[i].grade[3]);
        stu[i].grade[0] = (stu[i].grade[1] + stu[i].grade[2] + stu[i].grade[3]) / 3;
    }
    //分别处理学生各科的排名
    for (now = 0; now < 4; now++)
    {
        sort(stu, stu + n, cmp);
        Rank[stu[0].id][now] = 1;
        for (int i = 1; i < n; i++)
        {
            if (stu[i].grade[now] == stu[i - 1].grade[now])
                Rank[stu[i].id][now] = Rank[stu[i - 1].id][now];
            else
                Rank[stu[i].id][now] = i + 1;
        }
    }

    //查询（要解决分数相同优先显示的问题）
    int query; //待查询的学生id
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &query);
        //处理id不存在的情况
        if (Rank[query][0] == 0)
        {
            printf("N/A\n");
        }
        else //选出Rank[query][0-3]中最小的
        {
            int k = 0;
            for (int j = 1; j < 4; j++)
            {
                if (Rank[query][k] > Rank[query][j])
                    k = j;
            }
            printf("%d %c\n", Rank[query][k], course[k]);
        }
    }
    return 0;
}