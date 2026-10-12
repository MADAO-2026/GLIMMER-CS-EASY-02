#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>

//定义节点 
typedef struct Node
{
	int data;
	struct Node *next;
} Node;

//函数，传入数据，返回存储这个数据的节点。
Node *createNode (int n)
{
	Node *node = malloc(sizeof(Node));
	node -> data = n;
	node -> next = NULL;
	
	return node;
}

//头插函数
//*head 表示取出 head 所指向的那个变量 
//感觉这一块有点搞不太懂，现在简记为了有可能修改头节点就用Node **head，否则就用Node *head 
void add_to_head (Node ** head,int n)
{
	Node *node = createNode(n);
	node -> next = *head;
	*head = node;
}

//尾插函数 
void add_to_tail(Node **head, int n)
{
	Node *node = createNode(n);
	if(*head == NULL)
	{
		*head = node;
		return;
	}
	//找到最后一个节点 
    Node *p = *head;
    while (p->next != NULL)
    {
        p = p->next;
    }

    p->next = node;
}
//遍历函数
void tra (Node *head)
{
	for(Node *p = head;p != NULL;p = p -> next)
	{
		printf("%d",p -> data);
	}
} 
//查询函数 
bool query (Node *head,int n)
{
    int d = 0;	
	for (Node *p = head;p != NULL; p = p->next)
	{
		d++; 
		if(p -> data == n) 
		{
			printf("%d",d);
			return true;
		}		
		
	}
	return false;
}

//删除第n个节点
bool removeNode(Node **head, int n)
{
	if(n <= 0 || *head == NULL) return false;
    // 删除第一个节点
    if (n == 1)
    {
        Node *q = *head;
        *head = q->next;
        free(q);
        return true;
    }

    // 找到第 n-1 个节点
    Node *p = *head;

    for (int i = 1; i < n - 1; i++)
    {
        if (p->next == NULL)
            return false;

        p = p->next;
    }

    // 判断第n个节点是否存在 
    Node *q = p->next;
    if (q == NULL)
        return false;

    // 删除第 n 个节点
    p->next = q->next;
    free(q);

    return true;
}

//链表的反转函数
void reverse(Node **head)
{
	Node *p = *head;
	Node *q = NULL;
	
	while (p != NULL)
	{
		Node *temp = p->next;
		
		p->next = q;
		q = p;
		p = temp; 
	}
	
	*head = q;
} 

int main()
{
	//链表的初始化
    Node *head = malloc(sizeof(Node));
	head -> data = 0;
	head -> next = NULL;
	 
	return 0;
}