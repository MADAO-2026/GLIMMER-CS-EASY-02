## C-EASY-2：指针

### Step 1. 指针与结构体

#### 1.指针

**1.定义语法：**数据类型 * 指针变量名

   **变量大小：** 指针变量的大小**不是固定**的，其大小**与运行环境有关，**与指针类型无关

* 在**32**位操作系统下，任何类型的指针都占**4**个字节
* 在**64**位操作系统下，任何类型的指针都占**8**个字节

**2.输出结果：**20 10

原因：

```c
int x = 10;
int* p = &x;//定义一个int类型的指针p，让它存储x的地址
*p = 20;//访问p指向的变量，并将20赋值给它

int arr[3] = {3, 6, 9};
int *q = arr;//定义一个int类型的指针q，此处它存储的是数组第一个元素的地址
int y = ++*arr  +  *++q;
/*
++*arr 相当于++arr[0]——此处为4
*++q 先移动指针，向后移动一个元素，再使用它指向的值——此处为arr[1],即6
最终结果 4 + 6 = 10
*/

printf("%d %d", x, y);
```

**3.**

**定义：指针变量指向了一个无效的、未知的或已经不能使用的内存地址**

**危害：**

- 程序崩溃
- 修改不属于自己的内存
- 程序运行结果异常

**避免方法：**

- 指针变量定义后立即初始化

- 指针暂时不用时初始化为NULL（使用之前判断）

  ```c
  if (p != NULL) *p = 10;
  ```

  

- 避免使用已经失效的指针（例如在循环外使用循环中定义的指针）

**4.实现swap函数**

```c
void swap(int *a,int *p)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
```



#### 2.结构体

**1.结构体定义**

```c
typedef struct
{
    char name[10];   
    char sex; 
    int age;        
    double height;  
} PerInfo;
```

**2：结构体指针**

**定义：指向结构体变量地址的指针变量,它存储结构体变量的地**

**址**

利用指针访问结构体成员：p->age

**3.结构体的内存对齐**

**定义：**结构体中的成员变量，**不一定紧挨着存放**，中间可能会有“**空白字节**（填充）”，目的是让每个成员的**地址满足对齐要求**。

**对齐规则：**

- 每个成员的起始地址（从0开始）必须是其自身**对齐数**的整数倍。

- 结构体最终大小必须是**最大对齐数的整数倍**

- 成员顺序会影响大小

  ```c
  #include <stdio.h> 
  
  typedef struct
  {
      char name[10];   
      char sex; 
      int age;        
      double height;  
  } PerInfo;
  
  int main()
  {
  	PerInfo person;
  	size_t a = sizeof(person);
  	
  	printf("%zu",a);//结果为24，若更换顺序，结构体所占字节大小可能会发生变化
  	
  }
  ```



### step 2.链操作

#### 1.什么是链表

**1.数组与链表的区别：**

| 对比      | 数组               | 链表             |
| --------- | ------------------ | ---------------- |
| 存储方式  | **连续存储**       | **不一定连续**   |
| 元素之间  | 靠下标确定位置     | 靠指针/地址连接  |
| 插入/删除 | 需要移动元素，较慢 | 直接修改指针，快 |
| 内存空间  | 需要一块连续空间   | 可以利用零散空间 |

**2.单向链表的结构特点：**

每个节点包括两个部分：

- **数据域：**存储数据

- **指针域：**存储下一个结点的地址

**3.定义一个只存储一个整数的单向链表节点：**

```c
typedef struct Node
{
    int data;          // 存储一个整数
    struct Node *next; // 指向下一个节点的地址
} Node;
```

#### 2.实现基本的链操作



```c
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
```

### 后记

关于单链表，我觉得用数组模拟的话会比用指针简洁的多，链表的定义及相关操作如下:

```c
#include <stdio.h>

#define N 100010

/*
head表示头指针
e[i]存储i节点的数据，i代表节点下标
ne[i]代表节点i指向的下一个节点 
idx 表示下一个新节点要使用的数组下标
*/ 
int head,e[N],ne[N],idx;

//初始化
void init()
{
	head = -1,idx = 0;
} 

//头插函数 
void add_to_head(int x)
{
    e[idx] = x,ne[idx] = head,head = idx++;
}

//在下标为k的节点右侧插入一个节点 （包含尾插） 
void add(int k,int x)
{
    e[idx] = x,ne[idx] = ne[k],ne[k] = idx++;
    //最终的idx是下一个要插入的节点的下标 ，不能让k接受idx的值 
}

//删除下标为k的点后面的节点 
void remove (int k)
{  
    ne[k] = ne[ne[k]];    
}

//更改的话直接修改数组e[N]的值即可 

//单链表的倒置
void reverse()
{
    int p = head;
    int q = -1;

    while (p != -1)
    {
        int temp = ne[p];

        ne[p] = q;
        q = p;
        p = temp;
    }

    head = q;
}

int main()
{
    int m;
    scanf("%d",&m);
   
    //遍历查找 
    for (int i = head;i != -1;i = ne[i]) printf("%d ",e[i]);
    
    return 0;
}
```



#### **Ps:**

- 这种写法有点小问题，它不太方便直接删除下标为k的节点，需要通过循环找到节点k前一个结点下标，我觉得也可以用数组模拟一个双链表，这样找他前后的下标要方便很多

- 另外，删除是有潜在的**越界风险，**如果要删除最后一个节点，那么ne[ne[k]]这个东西是不在单链表里面的。

- ```c
  //删除最后一个节点的操作
  while (ne[ne[k]] != -1)
      {
          k = ne[k];
      }
  
      // 删除最后一个节点
      ne[k] = -1;
  ```

- 关于单链表的倒置，没想到啥好办法。。。。。。感觉只能像指针那样整

  
