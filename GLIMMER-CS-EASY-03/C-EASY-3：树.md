## C-EASY-3：树

### step1.什么是树

#### 1.树的定义

**树（Tree）：是一种非线性数据结构**，由若干个节点组成，节点之间通过边连接，形成一种具有**层次关系**的结构。

**二叉树：**是一种特殊的树，**其中每个节点**最多有两个子节点

**二叉树的定义：**

- 顺序表定义：

```c
int tree[100010];
/*
1代表根节点，2代表1的左孩子，3代表1的右孩子
以此类推：
节点i的左孩子为2i，右孩子为2i + 1；
```

- 个人常用：

```c
#include <stdio.h>
#define N 100010

int root;
int son[N][2];//son[i][0]表示i节点左孩子，son[i][1]表示节点i的右孩子
int main()
{
    
    return 0;
}

```



- 链表定义

```c
typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;
```

#### 2.二叉树的存储与特点

**存储方式**：**用结构体表示节点，用指针把节点连接起来**，与单链表不同的是每个节点都有**两个指针**。

**特点：**

- 每个节点**最多**有**两个子节点**
- 左右子节点并**不等价**
- 每个节点都有**唯一的父节点**（**根节点除外**）

- 没有子节点的节点被称为叶节点

#### 3.使用顺序表完成二叉树操作

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TREE_SIZE 100

/*
 * 顺序存储二叉树结点
 * - data：结点数据
 * - used：当前位置是否有结点
 */
typedef struct
{
    int data;
    bool used;
} SeqTreeNode;   //用于定义二叉树结点 

/*
 * 顺序存储二叉树
 * - nodes：结点数组
 * - size：数组最大容量
 */
typedef struct
{
    SeqTreeNode nodes[MAX_TREE_SIZE];
    int size;
} SeqBiTree;   //用于定义整个二叉树 

//1.初始化二叉树 
void init_tree(SeqBiTree *tree) //使用指针 
{
    tree->size = MAX_TREE_SIZE;//定义大小 

    for (int i = 0; i < MAX_TREE_SIZE; i++)
    {
        tree->nodes[i].data = 0;//大小为0 
        tree->nodes[i].used = false;//定义初始节点为空 
    }
}

//2.创建根节点
//引用函数时可先判断，若返回值为false，则根节点已存在，无需再运行此函数 
bool set_root(SeqBiTree *tree, int value)
{
	//如果根节点已经创建，则无需在创建 
	if(tree -> nodes[1].used) return false;
	
	tree -> nodes[1].data = value;
	tree -> nodes[1].used = true;
	
	return true;
}

//3.创建左孩子函数
bool set_left_child(SeqBiTree *tree, int parent_node, int value) 
{
    //如果父节点是否超出数组范围，无法创建
    if(parent_node < 1 || parent_node >= tree->size) return false;
	//如果父节点不存在，无法创建
	if(!tree -> nodes[parent_node].used) return false;
	//定义节点下标 
	int left = parent_node * 2;
    //如果子节点下标越界，无法创建
    if(left >= tree->size)
        return false;
    //如果子节点已存在，无法创建
    if(tree->nodes[left].used)
        return false;
	//定义节点数值
	tree -> nodes[left].data = value;
	//更新节点状态
	tree -> nodes[left].used = true;
	
	return true; 
}
//4.创建右孩子函数 
bool set_right_child(SeqBiTree *tree, int parent_node, int value)
{
    if(parent_node < 1 || parent_node >= tree->size)
        return false;

    if(!tree->nodes[parent_node].used)
        return false;

    int right = parent_node * 2 + 1;

    if(right >= tree->size)
        return false;

    if(tree->nodes[right].used)
        return false;

    tree->nodes[right].data = value;
    tree->nodes[right].used = true;

    return true;
}
//5.层序遍历函数
void level_order(SeqBiTree *tree)
{
	//第一行末尾下标为1 
	int level_end = 1;
	for(int i = 1;i < tree -> size;i++)
	{
		if(tree -> nodes[i].used) printf("%d ",tree -> nodes[i].data);
		//每打印完一行后换行 
		if(i == level_end) 
		{
			printf("\n");
			//更新行末尾下标 
			level_end = level_end * 2 + 1;
		}
	}
}//感觉会遍历很多空的节点,额。。。总共就有一百个，感觉也没必要改了

int main()
{
    SeqBiTree tree;
    init_tree(&tree);
    
    //定义一个三层二叉树
	// 第一层：根节点
    set_root(&tree, 1);

    // 第二层
    set_left_child(&tree, 1, 2);
    set_right_child(&tree, 1, 3);

    // 第三层
    set_left_child(&tree, 2, 4);
    set_right_child(&tree, 2, 5);
    set_left_child(&tree, 3, 6);
    set_right_child(&tree, 3, 7);
    
    //层级遍历
	level_order(&tree); 
	
    return 0;
}
```

### step2.链二叉树

#### 1.链二叉树的创建

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

//创建新节点的函数
TreeNode* create_node(int value)
{
	TreeNode *treenode = malloc(sizeof(TreeNode));
	treenode -> data = value;
	treenode -> left = NULL;
	treenode -> right = NULL;
	
	return treenode;
}
int main()
{
    //创建树	
	//创建节点 
	TreeNode *root = create_node(1);
	TreeNode *node2 = create_node(2);
	TreeNode *node3 = create_node(3);
	TreeNode *node4 = create_node(4);
	TreeNode *node5 = create_node(5);
	TreeNode *node6 = create_node(6);
	TreeNode *node7 = create_node(7);
	
	//连接节点
	root -> left = node2;
	root -> right = node3;
	node2 -> left = node4;
	node2 -> right = node5;
	node3 -> left = node6;
	node3 -> right = node7;
	

	return 0;
} 
```

#### 2.关于for循环无法打印函数的原因

- 链二叉树是通过指针来连接的，尽管一个指针可以有左右两个子节点，但一个指针在同一时刻只能指向其中一个节点。
- 在进行循环时，假设当前指针指向了根节点，那么再下一次循环时，他能够指向node2**或者**node3，二者不可得兼，从node2往下走也同理。
- 因此仅使用for循环打印二叉树只能只能一条路走到底，只能打印二叉树的“一根叉”。

### step3.递归

**ps：为了方便查看，我把三个函数分开写了，包含调用的完整代码在仓库中chain_tree.c中**

#### 1.前序遍历

```c
void preorder(TreeNode *root)
{
    if(root == NULL) return;
    printf("%d",root -> data);
    preorder(root -> left);
    preorder(root -> right);
}
```

##### 简述：

以题目上给的二叉树为例：

过程：

- 调用preorder（root）=> 打印root

  - 调用preorder（root -> left),即preorder（node2）打印node2

    - 调用（node2 -> left),即preorder（node4）打印node4 
      - node4两个指针均指向NULL，这个循环结束

    - 调用（node-> right),即preorder（node5）打印node5
      -  node5两个指针均指向NULL，这个循环结束

  - 调用preorder（root -> right）即preorder（ndoe3）打印node3

    - 调用（node3 -> left),即preorder（node6）打印node6 
      - node6两个指针均指向NULL，这个循环结束

    - 调用（node-> right),即preorder（node7）打印node7
      -  node7两个指针均指向NULL，这个循环结束

**ps:简单来说就是沿着左边的叉一条路走到黑，当走到头之后，就回到最近的分叉点，走之前没走过的那条，如果这个分叉点的所有分支都已经走完，再往前找最近的分叉点，直到走到根节点，依此类推，知道所有的数值都走过了，循环结束**

#### 2.中序遍历（)

```c
void inorder(TreeNode *root)
{
    if(root = NULL) return;
    
    inorder(root -> left);
    printf("%d",root -> data);
    inorder(root -> right);
}
```

#### 3.后序遍历

```c
void postorder (TreeNode *root)
{
    if(root == NULL) return;
    
    postorder(root -> left);
    postorder(root -> right);
    printf("%d",root -> data);
}
```



写完代码才发现这仨起名还怪讲究的，前中后正好对应`printf`函数的位置



#### 4.树的深度统计函数

```c
//current_depth 代表当前走到了第几层，max_depth代表走到过的最高层
int depth(TreeNode *root, int current_depth, int max_depth)
{
    if(root == NULL) return max_depth;
    
    current_depth++;
    
    if(current_depth > max_depth) 
        max_depth = current_depth;
    
    max_depth = depth(root->left, current_depth, max_depth);
    max_depth = depth(root->right, current_depth, max_depth);

    return max_depth;
    
}
```

##### 为什么后面两个int不需要使用指针变量：

首先明确什么条件下需要使用指针：**只有当你需要通过函数直接修改调用者的变量，或者需要传递对象的地址时，才需要考虑使用指针**

而current_depth和max_depth只存储整数值，不需要修改调用者的变量，可以通过函数参数传递数值，并通过 `return` 返回计算结果。

##### 递归与循环

本质上都是重复执行某个操作，直到满足结束条件

- 循环：通过`for`或`while`不断重复执行代码，需要自己控制变量的变化
- 递归：函数不断调用自身，把大问题拆分为小问题，直到满足结束条件，在逐层返回结果

**循环更像是自己一步步向前走，而递归更像是把问题交给更小的自己处理，处理完成后再返回。**

### 栈

**定义：栈（stack）是一种后进先出（区别与队列）的数据结构**

可以想象为一摞盘子，最后放上去的，最先被使用

#### 栈相关函数的注释及补全

```c
//定义一个栈结构体
typedef struct Stack {
    TreeNode **arr;//存储指向二叉树节点的指针
    int top;       //栈顶下标，-1表示栈为空
    int capacity;  //栈的最大容量
} Stack;
//创建一个栈
Stack *createStack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));    //分配结构体的内存
    stack->arr = malloc(sizeof(TreeNode *) * capacity);   //分配存储指针节点的数组
    stack->top = -1;    //初始栈为空
    stack->capacity = capacity;    //设置栈的容量
    return stack;    //返回栈指针
}
//判断栈是否为空（这里为啥不用bool）
int isEmpty(Stack *stack) {
    return stack->top == -1;
}
//将节点指针放入栈中
void push(Stack *stack, TreeNode *node) {
    if (stack->top == stack->capacity - 1) {
        return;//如果栈已满，不再放入
    }
    stack->arr[++stack->top] = node;
}
//弹出栈顶节点，并返回该节点指针
TreeNode *pop(Stack *stack) {
    if (isEmpty(stack)) {
        return NULL;//栈为空，返回NULL
    }
    return stack->arr[stack->top--];
    //top--代表一切操作结束后，更新栈顶
}

void preorderTraversal(TreeNode *root) //补全这个函数
{
    if (root == NULL)
        return;

    Stack *stack = createStack(100);
    push(stack, root);

    while (!isEmpty(stack))
    {
        TreeNode *node = pop(stack);
        printf("%d ", node->data);

        // 先压入右子树，再压入左子树
        // 因为栈是后进先出，所以左子树会先遍历
        if (node->right != NULL)
            push(stack, node->right);

        if (node->left != NULL)
            push(stack, node->left);
    }

    free(stack->arr);
    free(stack);
}
```

#### ps:

- 包含函数调用的完整版代码见仓库名为`Stack.c`的文件

### 后记：

#### 1.二叉树的数组模拟

```c
#include <stdio.h>
#include <stdbool.h>

#define N 100010

int root;          // 根节点编号
int son[N][2];     // son[i][0]：左孩子，son[i][1]：右孩子
int st[N];         // 标记节点是否存在
int e[N];          //存储节点数据
// 1. 初始化二叉树
void init_tree(void)
{
    root = 0;

    for (int i = 0; i < N; i++)
    {
        son[i][0] = 0;
        son[i][1] = 0;
        st[i] = 0;
    }
}

// 2. 创建根节点
bool set_root(int x)
{
    // 如果根节点已经存在，创建失败
    if (root != 0) return false;

    root = x;
    st[x] = 1;

    return true;
}

// 3. 创建左孩子
bool set_left_child(int parent_node, int x)
{
    // 如果父节点不存在，无法创建
    if (!st[parent_node]) return false;

    // 如果左孩子已经存在，创建失败
    if (son[parent_node][0] != 0) return false;

    son[parent_node][0] = x;
    st[x] = 1;

    return true;
}

// 4. 创建右孩子
bool set_right_child(int parent_node, int x)
{
    // 如果父节点不存在，无法创建
    if (!st[parent_node]) return false;

    // 如果右孩子已经存在，创建失败
    if (son[parent_node][1] != 0) return false;
    
    son[parent_node][1] = x;
    st[x] = 1;

    return true;
}

// 5. 层序遍历(先进先出，用到了队列)
void level_order()
{
    int q[N];
    int hh = 0, tt = 0;
    if(st[root]) return;  //如果根节点不存在，就没必要遍历了
    
    q[tt++] = root;  // 根节点入队

    while (hh < tt)
    {
        int u = q[hh++];  // 取出队头节点
        printf("%d ", u);

        if (son[u][0] != 0) q[tt++] = son[u][0];  // 左孩子入队
        if (son[u][1] != 0) q[tt++] = son[u][1];  // 右孩子入队
    }
}
int main(void)
{
    init_tree();

    // 第一层：根节点
    set_root(1);

    // 第二层
    set_left_child(1, 2);
    set_right_child(1, 3);

    // 第三层
    set_left_child(2, 4);
    set_right_child(2, 5);
    set_left_child(3, 6);
    set_right_child(3, 7);

    // 层序遍历
    level_order();

    return 0;
}
```

ps:写完之后有点死了，之前觉得这种写法简单，后来发现是因为默认了父节点存在，子节点不越界，总之就是很多东西都没考虑

#### 2.树的两种搜索方式

##### 1.深度优先搜索（dfs）

**沿着一条路径尽可能往深处搜索，走不下去时再回退。**

（一开始跟前序遍历搞混了，查了一下才知道前序遍历、中序遍历、后序遍历都属于深度优先搜索（DFS）在二叉树上的典型遍历方式）

##### 2.广度优先搜索（bfs）

**一层一层地搜索，先访问离根节点近的节点**，也就是上面的层序遍历，通常用**队列**实现

#### 3.栈的数组模拟

```c
//那啥，懒得写函数了，把常见的操作写到主函数里了
#include <stdio.h>
#include <string.h>

#define N 100010

int st[N], tt;

int main(void)
{
    int m;
    scanf("%d", &m);

    while(m--)
    {
        char op[10];
        scanf("%9s", op);

        //插入
        if(strcmp(op, "push") == 0)
        {
            int x;
            scanf("%d", &x);
            st[++tt] = x;
        }
        //弹出
        else if(strcmp(op, "pop") == 0)
        {
            if(tt > 0)
                tt--;
        }
        //判断是否为空
        else if(strcmp(op, "empty") == 0)
        {
            if(tt)
                printf("NO\n");
            else
                printf("YES\n");
        }
        //打印栈顶
        else if(strcmp(op, "query") == 0)
        {
            if(tt > 0)
                printf("%d\n", st[tt]);
        }
    }

    return 0;
}
```

#### 4.队列

**定义：队列（queue）是一种先进先出（区别与队列）的数据结构**

可以想象点外卖，先下单，先到货（预约的不算！！！）

##### 队列的数组模拟（之前没用指针和结构体写过，懒得折腾了）

```c
#include <stdio.h>
#include <string.h>

#define N 100010

int q[N], hh, tt = -1;

int main(void)
{
    int m, x;
    scanf("%d", &m);

    while(m--)
    {
        char op[10];
        scanf("%9s", op);
        
        //在队尾插入
        if(strcmp(op, "push") == 0)
        {
            scanf("%d", &x);
            q[++tt] = x;
        }
        //弹出队头
        else if(strcmp(op, "pop") == 0)
            hh++;
        //判断是否为空
        else if(strcmp(op, "empty") == 0)
            printf("%s\n", hh <= tt ? "NO" : "YES");
        
        else if(strcmp(op, "query") == 0)
            printf("%d\n", q[hh]);
    }

    return 0;
}
```

