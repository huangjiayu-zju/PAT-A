# [PAT]2. 算法初步
 
## 1. 排序
**1.1 冒泡排序**

冒泡的本质在于**交换**，即每次通过交换的方式把当前剩余元素的最大值移动到一端

**1.2 选择排序**

简单选择排序：对一个序列A中的元素`A[1]~A[n]`，令i从`1~n`枚举，进行n趟操作，每趟从待排序部分[1,n]中选择最小的元素，令其与待排序部分的第一个元素A[i]交换。时间复杂度为$O(N^2)$

**1.3 插入排序**

直接插入排序：对序列A的n个元素`A[1]~A[n]`，令i从`2~n`枚举，进行n-1趟操作，假设某一趟时，序列A的前i-1个元素`A[i]~A[i-1]`已经有序，而范围`[i,n]`还未有序，那么该趟从范围`[1,i-1]`中寻找某个位置j，使得`A[i]`插入位置j后(此时`A[j]~A[i-1]`会后移一位至A[j+1]~A[i])，范围`A[1,i]`有序。具体做法一般时**从后往前枚举已有序部分**来确定插入位置。

```c
int A[maxn], n;							//n为元素个数，数组下标为0~n-1
void insertSort(){
	for (int i = 1; i < n; ++i){		//进行n-1趟排序
		int temp = A[i], j = i;			//temp临时存放A[i]，j从i开始往前枚举
		while(j > 0&& temp < A[j-1]){	//只要temp小于前一个元素A[j-1]
			A[j] = A[j-1];				//把A[j-1]后移一位至A[j]
			j--;
		}
		A[j] = temp;					//插入位置为j
	}
}
```
**1.4 排序题型常用解题步骤（利用C++sort函数）**

1. 定义相关结构体
	

	```c
	struct Student{
		char name[10];	//姓名
		char id[10];	//学号
		ubt score;	//分数
		int r;	//排名
	}stu[100010];
	```

2. cmp函数的编写：使用sort进行排序时，需要提供cmp函数实现的排序规则，比如题目要求：对所有学生先按分数从高到低排序，分数相同的按姓名的字典序从小到大排序。
	
	```c
	bool cmp(Student a, Student b){
		if(a.score != b.score) return a.score > b.score	//分数不相同，那么高的在前面
		else return strcmp(a.name, b.name) < 0	//否则将姓名字典序小的排在前面
	}
	```

3. 排名的实现：一般规则是：**分数不同的排名不同，分数相同的排名相同但占用一个排位**。例如五个学生分数分别为90、88、88、88、86，那么排名分别为1、2、2、2、5。一般需要在结构体类型定义时把排名这一项加到结构体中，在数组排序完成后有两种方法来实现排名的计算。

	①先将数组第一个个体（假设数组下标从0开始）的排名记为1，然后遍历剩余个体：如果当前个体分数等于上一个个体的分数，那么当前个体的排名等于上一个个体的排名；否则，当前个体的排名等于数组下标加1.
	```c
	stu[0].r = 1;
	for (int i = 1; i < n; ++i)
	{
		if (stu[i].score == stu[i-1].score){
			stu[i].r = stu[i-1].r;
		}else{
			stu[i].r = i + 1;
		}
	}
	```
	②不需要定义排名这一项，直接令int型变量r初值为1，然后遍历所有个体：如果当前个体不是第一个个体且当前个体的分数不等于上一个个体的分数，那么令r等于数组下标加1，这时r就是当前个体的排名，直接输出即可。
	```c
	int r = 1;
	for (int i = 1; i < n; ++i)
	{
		if (i > 0 && stu[i].score != stu[i-1].score)
		{
			r = i + 1;
		}
		//输出当前个体信息，或者令stu[i].r = r
	}
	```

## 2. 散列
**2.1 整数散列**


给出N个正整数，再给出M个正整数，求M个欲查询的数中每个数在N个数中出现的次数，其中N，M与所有正整数都小于100000。

- 设定一个int型数组hashTable[100010]，在输入N个数时进行预处理，即当输入的数为x时，就令hashTable[x]++，时间复杂度为O(N+M)。

- 特点：直接把输入的数作为数组的下标来对这个数的性质进行统计
- 问题：输入整数过大(如11111111)或者是字符串，就不能直接作为数组下标。
- 散列(hash)函数H：将元素key通过一个函数转换为整数H(key)，使得该整数可尽量唯一的代表这个元素。
	- 直接定址（H (key)=a*key+b)
	- 平方取中：取key的平方的中间若干位作为hash值
	- 除留余数 (H (key)=key% mod)(mod 取不大于表长最大素数)，不同的 key 的 hash 值相同即冲突
		- 	线性探测
		- 平方探测：$(H(key)+k^2) \% mod$
		- 链地址法
- 可以使用标准库模板库中的map来直接使用hash的功能(unordered_map速度更快)


**2.2 字符串散列**

将 A-Z 对应 0-25，将 26 个大写字母对应到了 26 进制中，再将26进制转换成10进制的思路进行转换，即将字符串转换成了整数（转换成的整数最大是$26^{len}-1$，len为字符串长度）

```c
int hashFunc(char S[],int len){	//hash函数，将字符串S转换为整数
    int id = 0;
    for(int i = 0; i < len; i++){
        id = id * 26 + (S[i] - 'A');	//十进制转换为26进制
    }
    return id;
}
```
小写字母可以对应 26-51，然后再将 52 进制转换成 10 进制

```c
int hashFunc(char S[],int len){
    int id = 0;
    for(int i = 0; i < len; i++){
        if(s[i]>='A'&&S[i]<='Z'){
            id = id*52 + (S[i] - 'A');
        }
        else if(S[i]>='a'&&S[i]<='z'){
        	id = id*52 + (S[i]-'a') + 26;
        }
    }
    return id;
}
```
如果出现数字，有两种处理的方法
- 按照小写字母的处理方法，增大进制数至62
- 如果保证是在字符串的末尾是确定个数的数字，可以把前面英文字母的部分按上面的思路转换成整数，再将末尾的数字直接拼接上去。如“BCD4”可以先将BCD转换为整数731，然后拼接上末位的4变为7314。即在for循环后面添加`id = id * 10 + (S[len - 1] - '0');`
## 3. 递归
**3.1 分治**

将原问题划分成 n 个规模较小，并且结构与原问题相似的子问题，递归地解决这些子问题，然后再合并其结果，就得到原问题的解。
① 分解：将原问题分解成一系列子问题；
② 解决：递归地求解各个子问题，若子问题足够小，则直接求解；
③ 合并：将子问题的结果合并成原问题；
原问题分解成的子问题可以独立求解，子问题之间相互独立、没有交叉，这个是与动态规划明显的区别；

**3.2 递归**

递归很适合来实现分治思想，递归有两个关键点：**递归边界和递归式**

① 求解n的阶乘：递归式`F(n) = F(n-1) * n`，递归边界`F(0) = 1`

② 求Fibonacci数列的第n项：递归式`F(n) = F(n-1) + F(n-2)`，递归边界`F(0)=1, F(1)=1`。

③ 按字典序从小到大的顺序输出1~n的全排列(Full Permutation)

- 从递归的角度考虑，把问题分解为若干个子问题：输出以1开头的全排列，输出以2开头的全排列 ... 输出以n开头的全排列，于是不妨设定数组 P用来存放当前排列，设定散列数组hashTable，其中hashTable[x]当整数 x 已经在数组 P 中时候值为 true。
- 现在按顺序往 P 的第 1 位到第 n 位中填入数字。假设 P[1] ~ P[index-1]都已经填好了，正准备填 P[index]。显然需要枚举 1 ~ n，如果当前枚举值 x 不在 P[1] ~ P[index-1] 之中，则将其填入 P[index]，同时 hashTable[x] 为 true。然后去处理P的第 index+1 位，即进行递归；而当递归完成时，将hashTable[x] 还原为false，让 P[index]填入下一个数字
- 递归边界是 index = n + 1，此时说明P的第1~n位都已经填好了，输出数组P，表示生成了一个排列，然后直接return即可


④ n皇后问题：在一个n*n的国际象棋棋盘上放置n个皇后，使得这n个皇后两两均不在同一行、同一列、同一对角线上，求合法的方案数。

如果把n列皇后所在的行号依次写出，那么就会是 1 ~ n 的一个排列，于是枚举1 ~ n 的所有排列，查看每个排列对应的放置方案是否合法，即遍历每两个皇后，判断它们是否在同一条对角线上（因为显然不在同一行同一列）。
```c
if(index == n + 1){					//递归边界，生成一个排列
	bool flag = true;				//flag==true时表示当前排列是一个合法方案
	for(int i = 1; i <= n; i++){	//遍历任意两个皇后  所有的两两都要判断（不用相互重复）
		for(int j = i + 1; j <= n; j++){
			if(abs(i - j) == abs(P[i] - P[j])){	//若在同一条对角线上
				flag = false;		//不合法
			}
		}
	}
	if(flag) count++;
	return;
}
```
回溯法：当已经放置了一部分皇后时，可能剩余的皇后无论怎样防止都不可能合法，此时没必要往下递归了，直接返回上层即可。

## 4. 贪心

贪心是用来解决一类最优化问题，并希望由**局部最优策略来推的全局最优结果**的算法思想。贪心算法适用的问题一定满足**最优子结构**的性质。

**区间不相交问题**：给出 N 个开区间(x,y)，从中选择尽可能多的开区间，使得这些开区间两两之间没有交集
例如：(1,3)、(2,4)、(3,5)、(6,7) 最多选 3 个：(1,3)，(3,5)、(6,7)

考虑最简单的情况，开区间$I_1$被开区间$I_2$包含，显然选择$I_1$。接着把所有开区间按左端点$x$从大到小排序，那么去除掉区间包含的情况，一定有$y_1>y_2>...>y_n$成立；然后考虑选取区间。观察发现左端点最大的区间$I_1$的右边有一段是一定不会和其他区间重叠的，如果去掉它，那么$I_1$的左边剩余部分就会被$I_2$包含，这就回到了简单情况，应当要选取$I_1$。

所以当按照左端点从大到小排序后，就算是出现了区间包含的情况，我们仍然是选择左端点最大的那个，所以算法流程就是：
1. 按左端点从大到小排序，左端点相同的按右端点从小到大排序
2. 排好序后，从左端点最大的区间$I_1$出发往前面的区间$I_k$遍历，找到第一个右端点值**小于等于**$I_1$左端点值的区间$I_k$，并且将$I_k$作为新选中的区间，同时不相交区间个数加1
3. 遍历到左端点最小的区间为终点，即可得到最多的不相交区间个数


**区间选点问题**：给出 N 个闭区间 [x,y]，求最少需要确定多少个点，才能使每个闭区间都至少存在一个点。例如：对闭区间 [1,4]、[2,6]、[5,7] 来说，需要两个点（例如 3,5）。

还是先考虑开区间$I_1$被开区间$I_2$包含，那么在$I_1$中取点可以保证这个点一定在$I_2$内；然后把所有区间按左端点从大到小排序，因此对左端点最大的区间来说，显然取左端点可以使得它尽可能多地覆盖其他区间。因此策略与区间不相交问题一致，唯一地区别是在第二步中，找到第一个右端点值**小于**左端点值的区间。

## 5. 二分
**5.1 二分查找**


二分查找是基于**有序**序列的查找算法


**如何在一个严格递增序列 A 中找到给定的数 x**

令`[left,right]`为整个序列的下标区间，然后每次测试当前中间位置`mid = (left+right)/2`，判断A[mid]与欲查询元素x的大小。这里的循环终止条件是 `while(left <= right)`

注意如果二分上界超过int型数据范围的一半，那么当欲查询元素在序列较靠右的位置时，语句`mid = (left+right)/2`中的`left+right`可能超过int而导致溢出。可以使用`mid = left + (right - left) / 2`这条语句作为代替避免溢出。

如果递增序列 A 中的元素可能重复，那么如何对给定的欲查询元素 x，求**出序列中第一个大于等于 x 的元素的位置 L 以及第一个大于 x 的元素的位置 R，这样元素 x 在序列中的存在区间就是左闭右开区间 [L，R）**。

如果序列中没有x，那么L和R也可以理解成假设序列中存在x，则x应当在的位置。

先求区间[left, right]序列中的第一个大于等于 x 的元素的位置
1. 如果A[mid] > x，说明第一个大于等于x的元素的位置一定在mid处或mid的左侧，即[left, mid]
2. 如果A[mid]  == x，说明第一个大于等于x的元素的位置一定在mid的左侧
3. 如果A[mid] < x，说明第一个大于等于x的元素的位置一定在mid的右侧。即[mid+1, right]
4. 第1，2条可以合并成：如果A[mid] >= x，说明第一个大于等于x的元素的位置一定在mid处或mid的左侧
5. 注意这里是`while(left < right)`，且循环终止条件是left==right，因此最后返回值可以是left或right
6. 二分的下界是0，上界是n（考虑到欲查询元素有可能比序列中所有的元素都要大，此时应当返回n，即假设它存在，它该在的位置）。

然后求序列中第一个大于x的元素的位置

1. 如果A[mid] > x，说明第一个大于x的元素的位置一定在mid处或mid的左侧，即[left, mid]
2. 如果A[mid] <= x，说明第一个大于x的元素的位置一定在mid的右侧。即[mid+1, right]

可以总结出一个问题模板：**寻找有序序列中第一个满足条件的元素的位置**。
```c
//二分区间为左闭右闭的[left,right]，初值必须能覆盖解的所有取值
int solve(int left, int right){
    int mid;
    while(left < right){//对[left,right]来说，left==right意味着找到唯一位置
        mid = (left + right) / 2;
        if(条件成立){	//条件成立，第一个满足条件的元素的位置<=mid
            right = mid;
        }else{			//条件不成立，第一个满足条件的元素的位置>mid
            left = mid + 1;
        }
    }
    return left;
}
```
如果想要寻找最后一个满足"条件C"的元素的位置，则可以先求第一个满足“条件!C”的元素的位置，然后将该位置减1即可。


如果是左开右闭的区间(left,right]，则left的初值是-1，right的初值是n。写法上有三点不同：
1. 循环条件应该是while(left + 1 < right)。
2. 语句left = mid + 1要改为left = mid;
3. 返回的应当是right而不是left
```c
//二分区间为左闭右闭的(left,right]，初值必须能覆盖解的所有取值，并且left比最小取值小1
int solve(int left, int right){
    int mid;
    while(left + 1< right){//对(left,right]来说，left+1 == right意味着找到唯一位置
        mid = (left +  right) / 2;
        if(条件成立){	//条件成立，第一个满足条件的元素的位置<=mid
            right = mid;
        }else{			//条件不成立，第一个满足条件的元素的位置>mid
            left = mid;
        }
    }
    return right;
}
```

**5.2 快速幂**

给定三个正整数a、b、m($a<10^9,b<10^{18},1<m<10^9$)，求$a^b\%m$。

快速幂（二分幂）的做法基于以下事实：
1. 如果b是奇数，那么有$a^b= a*a^{b-1}$ 
2. 如果b是偶数，那么有$a^b=a^{b/2}*a^{b/2}$

显然b是奇数的情况总是可以在下一步转换为b是偶数的情况，而b是偶数的情况总可以在下一步转换为b/2的情况，这样在log(b)级别次数的转换后，就可以把b变为0，任何正整数的0次方都是1。

**快速幂的递归写法**
```c
typedef long long LL;
LL binaryPow(LL a, LL b, LL m){
    if(b == 0){     //如果b为0，则a^0=1
        return 1;
    }
    if(b % 2 == 1){ //b为奇数，转换为b-1
        return a * binaryPow(a, b - 1, m) % m;
    }
    else{
        LL mul = binaryPow(a, b / 2, m);
        return mul * mul % m;
    }
}
```
条件if(b % 2 == 1)可以用`if(b & 1)`代替，b和1进行位与操作，判断b的末位是否为1，当b为奇数时b & 1会返回1。

当b % 2 == 0时不要返回直接返回`binaryPow(a, b / 2, m) * binaryPow(a, b / 2, m)`，而是应计算出单个`binaryPow(a, b / 2, m)`之后再乘起来。因为前者每次都会调用两个binaryPow函数，导致复杂度变成$O(2^{log(b)})=O(b)$。

对于不同的题目，有两个细节需要注意：
1. 如果初始时a有可能大于等于m，那么需要再进入函数前就让a对m取模。
2. 如果m为1，可以用直接在函数外部特判为0

**快速幂的迭代写法**

对$a^b$来说，如果把b写成二进制，则b可以写成若干二次幂之和，因此 我们可以把任意的$a^b$表示成$a^{2k},...,a^8,a^4,a^2,a^1$中若干项的乘积。于是可以枚举b的二进制的每一位，如果当前位为1，则累积$a^{2i}$，最后更新a为$a^2$，并将b右移一位（也可以理解为将b除以2）

```c
typedef long long LL;
LL binaryPow(LL a, LL b, LL m){
    LL ans = 1;
    while(b > 0){
        if(b & 1){  //如果b的二进制末尾为1
            ans = ans * a % m;  //令ans累积上a
        }
        a = a * a % m;  //令a平方
        b >>= 1;    //将b的二进制右移一位
    }
    return ans;
}
```






## 6. 双指针
给定一个递增的正整数序列和一个正整数M，求序列中的两个不同位置的数a和b，使它们的和恰好为M。输出所有满足条件的方案。

令i、j分别指向序列的第一个元素和最后一个元素，接下来根据`a[i]+a[j]`与M的大小来进行下面三种选择，使i不断向右移动、使j不断向左移动，直到i>=j成立。时间复杂度为O(n)
- 如果`a[i]+a[j] == M`，说明找到了一组方案，剩下的方案只可能在`[i + 1, j - 1]`的区间内产生。
- 如果`a[i]+a[j] > M`，则剩余的方案只可能在`[i, j - 1]`区间内产生
- 如果`a[i]+a[j] < M`，则剩余的方案只可能在`[i + 1, j ]`区间内产生

**序列合并问题**：假设有两个递增序列A与B，要求将它们合并为一个递增序列C

设置两个下标i和j，初值均为0，表示分别指向序列A的第一个元素和序列B的第一个元素，然后根据A[i]与B[j]的大小来决定哪一个放入序列C
```c
int merge(int A[], int B[], int C[], int n, int m){
    int i = 0, j = 0, index = 0;
    while (i < n && j < m){
        if(A[i] <= B[j]){
            C[index++] = A[i++];
        }else{
            C[index++] = B[i++];
        }
    }
    while(i < n){
        C[index++] = A[i++];
    }
    while(j < m){
        C[index++] = B[j++];
    }
    return index;
}
```

**6.1 归并排序**

2-路归并排序的原理是，将序列两两分组，将序列归并为$\left \lceil \frac{n}{2} \right \rceil$个组，组内单独排序；然后将这些组再两两归并，生成$\left \lceil \frac{n}{4} \right \rceil$个组，组内再单独排序；以此类推，直到只剩下一个组位置。其核心在于如何将两个有序序列合并为一个有序序列，即上面的序列合并问题。时间复杂度为$O(nlogn)$

1. 递归实现：反复将当前区间[left,right]分为两半，对两个子区间[left,mid]与[mid+1,right]分别递归进行归并排序，然后将两个已经有序的子区间合并为有序序列即可。
2. 非递归实现：考虑到每次分组时组内元素个数上限都是2的幂次。于是令步长step的初值为2，然后将数组每step个元素作为一组，将其内部进行排序；再令step乘以2，重复上面的操作，直到 step/2 超过元素个数n。



**6.2 快速排序**

先解决这样一个问题：对一个序列A[1]、A[2]、…、A[n]，调整序列中元素的位置，使得A[1]（原序列的A[1]，下同）的左侧所有元素都不超过A[1]、右侧所有元素都大于A[1]。下面给出速度最快的做法：思想就是双指针
1. 先将A[1]存至某个临时变量temp，并令下标left、right分别指向序列首尾（如令left=1、right=n）
2. 只要right指向的元素A[right]大于temp，就将right不断左移；当某个时候A[right]<=temp时，将元素A[right]挪到left指向的元素A[left]处
3. 只要left指向的元素A[left]小于temp，就将left不断右移；当某个时候A[left]>temp时，将元素A[left]挪到right指向的元素A[right]处
4. 重复2，3，直到left与right相遇，把temp（即原A[1]）放到相遇的地方。


快速排序的思路是：
1. 调整序列中的元素，使当前序列最左端的元素在调整后满足左侧所有元素均不超过该元素、右侧所有元素均大于该元素
2. 对该元素的左侧和右侧分别递归进行步骤1的调整，直到当前调整区间的长度不超过1。


把用以划分区间的元素A[left] 称为主元。快速排序算法当序列中元素的排列比较随机时效率最高，但是当序列中元素接近有序时，会达到最坏时间复杂度$O(n^2)$，产生这种情况的主要原因在于主元没有把当前区间划分为两个长度接近的子区间。解决办法是随机选择主元，这样对任意输入数据的期望时间复杂度都能达到$O(nlogn)$


**6.3 随机选择算法**

**如何从一个无序的数组中求出第K大的数**

最直接的想法是对数组排序，然后直接取出第K个元素即可，时间复杂度为(nlogn)，而随机选择算法可以做到对任意输入都达到$O(n)$的期望时间复杂度

当对A[left,right]执行一次randPartition函数之后，主元左侧的元素个数就是确定的，且它们都小于主元。假设此时主元是A[p]，那么A[p]就是A[left,right]中第p-left+1大的数。不妨令M表示p-left+1，如果K\==M成立，说明第K大的数就是主元A[p]；如果K<M成立，说明第K大的数在主元左侧，即A[left…(p-1)]中的第K大，往左递归即可；如果K>M成立，则说明第K大的数在主元右侧，即即A[(p+1)…right]中的第K-M大，往右侧递归即可。算法以left==right为递归边界，返回A[left]。

可以证明虽热随机选择算法的最坏时间复杂度是$O(n^2)$，但其对任输入的期望时间复杂度确实$O(n)$

下面的问题是一个应用：给定一个由整数组成的集合，集合中的整数各不相同，现在要将它分为两个子集合，使得这两个子集合的并为原集合、交为空集，同时在两个子集合的元素个数$n_1$和$n_2$之差的绝对值尽可能小的前提下，要求它们各自的元素之和$S_1$与$S_2$之差的绝对值尽可能大，求这个$|S_1-S_2|$为多少。

最直接的思路是将原集合中的元素从小到大排序，取排序后的前n/2个元素作为其中一个子集合，剩下的元素作为另一个子集合即可，时间复杂度为O(nlogn)。

更优的做法是使用随机选择算法，上面的问题就是求原集合中元素的第n/2大，同时根据这个数把集合分为两部分，使其中一个子集合中的元素都不小于这个数，而另一个子集合中的元素都大于这个数，至于两个子集合内部元素的顺序则不需要关心。因此只需要用randSelect函数求出第n/2大的数即可。期望时间复杂度为O(n)。
