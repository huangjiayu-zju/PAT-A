#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
using namespace std;
const int maxn = 10010;

struct Car
{
    char id[8];            //车牌号
    int time;              //记录的时刻(以s为单位)
    char status[4];        //in或者out
} all[maxn], valid[maxn];  //all为所有记录，valid为有效记录
int num = 0;               //有效记录的条数
map<string, int> parkTime; //车牌号->总停留时间

int timeToInt(int hh, int mm, int ss)
{ //时间转换，以s为单位
    return hh * 3600 + mm * 60 + ss;
}

bool cmpByIdAndTime(Car a, Car b)
{ //先按车牌号字典序排序，如果相同按照时间从小到大排序
    if (strcmp(a.id, b.id))
        return strcmp(a.id, b.id) < 0;
    else
        return a.time < b.time;
}

bool cmpByTime(Car a, Car b)
{ //按时间排序
    return a.time < b.time;
}

int main()
{
    int n, k, hh, mm, ss;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
    {
        scanf("%s %d:%d:%d %s", all[i].id, &hh, &mm, &ss, all[i].status);
        all[i].time = timeToInt(hh, mm, ss);
    }
    sort(all, all + n, cmpByIdAndTime);
    int maxTime = -1;               //最长停留时间
    for (int i = 0; i < n - 1; i++) //遍历所有记录，查找有效记录，将其存入valid数组，计算停留时间
    {
        if (!strcmp(all[i].id, all[i + 1].id) && //i和i+1是同一辆车
            !strcmp(all[i].status, "in") &&      //i是in记录
            !strcmp(all[i + 1].status, "out"))   //i+1是out记录
        { 
            valid[num++] = all[i];
            valid[num++] = all[i + 1];
            int inTime = all[i + 1].time - all[i].time;
            if (parkTime.count(all[i].id) == 0)
            { //map中没有这个车牌号，置为0
                parkTime[all[i].id] = 0;
            }
            parkTime[all[i].id] += inTime;               //增加该车牌号的总停留时间
            maxTime = max(maxTime, parkTime[all[i].id]); //更新最大总停留时间
        }
    }
    sort(valid, valid + num, cmpByTime); //有效记录按时间顺序递增，进入查询阶段
    int now = 0, nowCar = 0;             //now指向不超过当前查询时间的记录，numCar为当前校园内车辆数
    for (int i = 0; i < k; i++)
    {
        scanf("%d:%d:%d", &hh, &mm, &ss);
        int time = timeToInt(hh, mm, ss);
        while (now < num && valid[now].time <= time) //让now处理至当前查询时间
        {
            if (!strcmp(valid[now].status, "in"))
            { //车辆进入
                nowCar++;
            }
            else
            { //车辆离开
                nowCar--;
            }
            now++; //now指向下一条记录
        }
        printf("%d\n", nowCar);
    }

    map<string, int>::iterator it; //遍历parkTime，输出总停留时间等于maxTime的车辆车牌号和对应的时间
    for (it = parkTime.begin(); it != parkTime.end(); it++)
    {
        if (it->second == maxTime)
        { //输出所有最长总停留时间的车牌号
            printf("%s ", it->first.c_str());
        }
    }
    printf("%02d:%02d:%02d\n", maxTime / 3600, maxTime % 3600 / 60, maxTime % 60);
    return 0;
}
