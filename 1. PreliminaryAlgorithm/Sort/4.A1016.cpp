#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

/*
步骤1：以结构体类型存放数据，并根据题目要求写出cmp函数
步骤2：用户记录在数组中已经连续且按照时间顺序排列，于是确定每个用户是否存在有效通话记录(只能确定有无，不能确定有几对)
步骤3：输出所有有效通话记录：online数组下标与off-line的数组下标只相差1才能进行配对，这一步确定具体配对数目
步骤4：计算时长
*/

int toll[25]; //资费
struct Record
{
    char name[24];
    int month, dd, hh, mm;
    bool status; //status为true表示online
} record[1010], temp;

bool cmp(Record a, Record b)
{
    int s = strcmp(a.name, b.name);
    if (s != 0)
        return s < 0;
    else if (a.month != b.month)
        return a.month < b.month;
    else if (a.dd != b.dd)
        return a.dd < b.dd;
    else if (a.hh != b.hh)
        return a.hh < b.hh;
    else
        return a.mm < b.mm;
}

//时长的计算方法
void get_ans(int on, int off, int &time, int &money)
{
    temp = record[on];
    while (temp.dd < record[off].dd || temp.hh < record[off].hh || temp.mm < record[off].mm)
    {
        time++;                 //总时间增加1
        money += toll[temp.hh]; //话费增加temp.hh
        temp.mm++;              //当前时间增加1min
        if (temp.mm >= 60)
        {                //当前分钟数到达60
            temp.mm = 0; //进入下一小时
            temp.hh++;
        }
        if (temp.hh >= 24)
        {
            temp.hh = 0;
            temp.dd++;
        }
    }
}

int main()
{
    //输出数据
    for (int i = 0; i < 24; i++)
    {
        scanf("%d", &toll[i]);
    }
    int n;
    scanf("%d", &n);
    char line[10]; //临时存放on-line与off-line
    for (int i = 0; i < n; i++)
    {
        scanf("%s %d:%d:%d:%d %s", record[i].name, &record[i].month, &record[i].dd, &record[i].hh, &record[i].mm, line);
        if (strcmp(line, "on-line") == 0)
            record[i].status = true;
        else
            record[i].status = false;
    }

    sort(record, record + n, cmp);

    int on = 0, off, next; //on和off是配对的两条记录，next为下一个用户下标
    while (on < n)
    { //每次循环处理单个用户的所有记录
        int needPrint = 0;
        next = on; //从当前位置开始寻找下一个用户
        while (next < n && strcmp(record[next].name, record[on].name) == 0)
        {
            if (needPrint == 0 && record[next].status == true)
                needPrint = 1;
            else if (needPrint == 1 && record[next].status == false)
                needPrint = 2;
            next++; //next自增直到找到不同名字即下一个用户
        }
        if (needPrint < 2)
        { //该用户没有配对的on-off，则继续
            on = next;
            continue;
        }
        int AllMoney = 0; //该用户总共花费的钱
        printf("%s %02d\n", record[on].name, record[on].month);
        while (on < next)
        { //寻找该用户的所有配对
            //过滤不符合条件的配对
            while (on < next - 1 && !(record[on].status == true && record[on + 1].status == false))
            {
                on++;
            }
            off = on + 1; //off一定是on的下一个
            if (off == next)
            { //已经输出完毕所有配对的on和off
                on = next;
                break;
            }
            //如果走到这一步说明存在一个配对，及时进行输出
            printf("%02d:%02d:%02d %02d:%02d:%02d ", record[on].dd, record[on].hh, record[on].mm, record[off].dd, record[off].hh, record[off].mm);
            int time = 0, money = 0; //时间、单次记录花费的钱
            get_ans(on, off, time, money);
            AllMoney += money;
            printf("%d $%.2f\n", time, money / 100.0);
            on = off + 1; //完成一个配对，从off+1开始找下一对
        }
        printf("Total amount: $%.2f\n", AllMoney / 100.0);
    }
    return 0;
}
