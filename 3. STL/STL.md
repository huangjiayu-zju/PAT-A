## vector  1,2
- vector\<typename> name
- vector\<typename>::iterator it;
- push_back(x)
- pop_back()
- size()
- clear()
- insert(it,x)
- erase(it),erase(first,last)
## set 3
元素内部自动递增排序，且自动去除了重复元素
- insert(x)
- find(value)
- erase(it),erase(value),erase(first,last)
- size()
- clear()
处理元素不唯一的情况使用multiset,处理只去重但不排序的用unordered_set，速度比set快得多
## string 4
- string::iterator it;
- str1 += str2, str1 > str2
- length(),size()
- insert(pos,string),insert(it,it2,it3);
- erase(it),erase(first,last),erase(pos.length)
- clear()
- substr(pos, len)
- string::npos
- find(str2),find(str2,pos)
- replace(pos,len,str2),replace(it1,it2,str2)
## map 5-8
map的键是唯一的，map会以键从小到大的顺序自动排序(红黑树)，map的键值是唯一的，multimap处理一个键对应多个值
- it->first,it->second
- find(key)
- erase(it),erase(key),erase(first,last)
- size()
- clear()
## queue
- push(x)
- front(),back()
- pop()
- empty()
- size()
使用front和pop函数前，必须用empty()判断队列非空
## priority_queue
优先队列底层的数据结构堆(heap)会随时调整结构，使每次的队首元素都是优先级最大的。
- push(x)
- top() 使用前，必须用empty()判断队列非空
- pop()
- empty()
- size()
### priority_queue内优先级的设置
1. 基本数据类型的优先级设置
    ```c
    priority_queue<int> q;
    priority_queue<int, vector<int>, less<int> > q;
    ```
    less\<int>表示数字大的优先级越大，而greater\<int>表示数字小的优先级越大
2. 结构体优先级设置
    ```c
    struct fruit{
        string name;
        int price;
        friend bool operator < (fruit f1, fruit f2){
            return f1.price < f2.price;
        }
    }
    priority_queue<fruit> q;
    ```
    上面是按价格高的的优先级高，优先队列的这个函数与sort中的cmp函数的效果是相反的。也可以下面这么写
    ```c
    struct fruit{
        string name;
        int price;
    }
    struct cmp{
        bool operator () (fruit f1, fruit f2){
            return f1.price < f2.price;
        }
    }
    priority_queue<fruit, vector<fruit>, cmp> q;
    ```
## stack
常用函数与priority_queue相同
## pair
- pair\<string int> p("haha",5);
- make_pair("haha",5)
- p.first,p.second
## include<algorithm>
- max(x,y)参数必须是两个(可以是浮点数),max(x,max(y,z))，abs(x)中x必须是整数，浮点数用math中的fabs(x)
- swap(x,y)
- reverse(it,it2)
- next_permutation(it,it2)
- fill(it,it2,num)
- sort(begin,end,cmp)，默认递增排序，从小到大排列就用"<"；容器中只有vector、string、deque是可以使用sort的
- lower_bound(first,last,val)返回指针或者迭代器
- upper_bound(first,last,val)返回值减去数组首地址即元素下标