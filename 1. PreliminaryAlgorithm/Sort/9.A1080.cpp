#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Student
{
    int ge, gi, sum;
    int stuID, rank; //排名，考生编号
    int choice[6];   //K个选择学校的编号
} stu[40010];

struct School
{
    int quota;     //招生人数总额度
    int stuNum;    //当前实际招收人数
    int id[40010]; //招收的考生编号
    int lastAdmit; //记录最后一个招收的考生编号，因为如果和最后一个录取的排名相同，可以不受招生人数的限制
} sch[110];

bool cmpStu(Student a, Student b)
{ //按照题目要求排序
    if (a.sum != b.sum)
        return a.sum > b.sum;
    else
        return a.ge > b.ge;
}

bool cmpID(int a, int b)
{ //按考生编号从小到大排序
    return stu[a].stuID < stu[b].stuID;
}

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; i++) //初始化每个学校
    {
        scanf("%d", &sch[i].quota);
        sch[i].stuNum = 0;
        sch[i].lastAdmit = -1; //最后一个招生的学生编号为-1，表示不存在
    }
    for (int i = 0; i < n; i++) //初始化每个考生
    {
        stu[i].stuID = i;
        scanf("%d%d", &stu[i].ge, &stu[i].gi);
        stu[i].sum = stu[i].ge + stu[i].gi;
        for (int j = 0; j < k; j++)
        {
            scanf("%d", &stu[i].choice[j]);
        }
    }
    sort(stu, stu + n, cmpStu); //按成绩排名考生
    for (int i = 0; i < n; i++) //给n位考生按成绩排序
    {
        if (i > 0 && stu[i].sum == stu[i - 1].sum && stu[i].ge == stu[i - 1].ge)
        {
            stu[i].rank = stu[i - 1].rank;
        }
        else
        {
            stu[i].rank = i;
        }
    }
    for (int i = 0; i < n; i++) //对每个考生判断其被哪所学校录取
    {
        for (int j = 0; j < k; j++)
        {
            int choice = stu[i].choice[j];    //当前学校编号
            int num = sch[choice].stuNum;     //当前学校实际招收人数
            int last = sch[choice].lastAdmit; //当前学校最后一位录取考生编号
            if (num < sch[choice].quota || (last != -1 && stu[last].rank == stu[i].rank))
            {
                sch[choice].id[num] = i;   //录取该考生
                sch[choice].lastAdmit = i; //更新最后一个录取考生的编号i
                sch[choice].stuNum++;      //当前招生人数加1
                break;                     //此考生已被录取，跳出循环到下一个考生
            }
        }
    }
    for (int i = 0; i < m; i++) //输出m所学校的录取信息
    {
        if (sch[i].stuNum > 0)
        { //如果招到学生
            //按ID从小到大排序
            sort(sch[i].id, sch[i].id + sch[i].stuNum, cmpID);
            for (int j = 0; j < sch[i].stuNum; j++)
            {
                printf("%d", stu[sch[i].id[j]].stuID);
                if (j != sch[i].stuNum - 1)
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    return 0;
}