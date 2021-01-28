#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10010;

//如果某位考生全场都没有提交记录，或者没有通过编译的提交，则该考生的信息不输出
//对需要输出的考生，如果某道题的提交编译无法通过，提交记录为-1，但分数显示应该记为0分；如果某道题没有提交记录，应该输出"-"
//分数显示为0分有两种情况，一种是无法通过编译，另一种是通过编译但是得分为0

struct Student
{
    int id;
    int score[6];    //每道题的得分
    int total_score; //总分
    int solve;       //完美解题数
    bool flag;       //是否有能通过编译的提交
} stu[maxn];

int n, k, m;
int points[6] = {0};    //每道题的满分

bool cmp(Student a, Student b)
{
    if (a.flag != b.flag)
        return a.flag > b.flag; //需要输出的考生排前面
    else if (a.total_score != b.total_score)
        return a.total_score > b.total_score;
    else if (a.solve != b.solve)
        return a.solve > b.solve;
    else
        return a.id < b.id;
}

void init()
{ //初始化
    for (int i = 0; i <= n; i++)
    {
        stu[i].id = i;
        stu[i].total_score = 0;
        stu[i].solve = 0;
        stu[i].flag = false;
        memset(stu[i].score, -1, sizeof(stu[i].score)); //初始化为-1表示该题没有提交，当该题出现无法通过编译时，将得分记为0分，表示有过提交
    }
}

int main()
{
    scanf("%d%d%d", &n, &k, &m);
    init();
    for (int i = 1; i <= k; i++)
    {
        scanf("%d", &points[i]);
    }

    int u_id, p_id, score_obtained; //考生id，题目id，所获分值
    for (int i = 0; i < m; i++)
    { //对每个提交记录的处理方式(按顺序执行)
        scanf("%d%d%d", &u_id, &p_id, &score_obtained);
        if (score_obtained != -1)
        {//1.当前提交能通过编译，则令该考生的flag为true
            stu[u_id].flag = true;
        }            
        if (stu[u_id].score[p_id] == -1 && score_obtained == -1)
        {//2.当前提交是第一次编译错误，则将得分从-1修改为0分
            stu[u_id].score[p_id] = 0;
        }            
        if (score_obtained == points[p_id] && stu[u_id].score[p_id] < points[p_id])
        {//3.当前提交是第一次对该题获得满分，完美解题数加1
            stu[u_id].solve++;
        }            
        if (score_obtained > stu[u_id].score[p_id])
        {//4.当前提交获得更高分，则覆盖
            stu[u_id].score[p_id] = score_obtained;
        }            
    }
    for (int i = 1; i <= n; i++)
    { //计算总分
        for (int j = 1; j <= k; j++)
        {
            if (stu[i].score[j] != -1)
            { //排除未提交的题目(分值仍为-1)
                stu[i].total_score += stu[i].score[j];
            }
        }
    }

    sort(stu + 1, stu + n + 1, cmp); //u_id从1开始
    int r = 1;
    for (int i = 1; i <= n && stu[i].flag == true; i++) //不输出flag为false的学生
    {
        if (i > 1 && stu[i].total_score != stu[i - 1].total_score)
        {
            r = i;
        }
        printf("%d %05d %d", r, stu[i].id, stu[i].total_score);
        for (int j = 1; j <= k; j++)
        {
            if (stu[i].score[j] == -1)
            {
                printf(" -");
            }
            else
            {
                printf(" %d", stu[i].score[j]);
            }
        }
        printf("\n");
    }
    return 0;
}