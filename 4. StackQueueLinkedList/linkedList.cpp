#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    node *next;
};

//创建链表
node* create(int Array[]){
    node *p, *pre, *head;//pre保存当前结点的前驱结点，head为头结点
    head = new node;//创建头结点
    head->next = NULL;//初始化头结点
    pre = head;//记录pre为head
    for (int i = 0; i < 5; i++)
    {
        p = new node;
        p->data = Array[i];
        p->next = NULL;
        pre->next = p;
        pre = p;
    }
    return head;
}

//查找元素个数
int search(node *head, int x){
    int count = 0;
    node *p = head->next;//头结点没有数据域
    while(p != NULL){
        if(p->data == x){
            count++;
        }
        p = p->next;
    }
    return count;
}

//插入带头结点的第pos位置上
void insert(node* head, int pos, int x){
    node *p = head;
    for (int i = 0; i < pos - 1; i++)//注意是pos-1，到插入位置的前一个结点
    {
        p = p->next;
    }
    node *q = p;
    q->data = x;
    q->next = p->next;
    p->next = q;
}

//删除所有数据域为x的结点
void del(node* head, int x){
    node* p = head->next;
    node *pre = head;//pre始终保存p的前驱结点的指针
    while(p != NULL){
        if(p->data == x){
            pre->next = p->next;
            delete (p);
            p = pre->next;
        }else{
            pre = p;
            p = p->next;
        }
    }
}


int main()
{
    int Array[5] = {5, 3, 6, 1, 2};
    node *L = create(Array);
    L = L->next;//从第一个结点开始有数据域
    while(L!=NULL){
        printf("%d", L->data);
        L = L->next;
    }
    return 0;
}