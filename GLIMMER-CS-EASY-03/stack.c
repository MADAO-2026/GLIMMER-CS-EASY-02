#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

//创建新节点的函数
TreeNode* create_node(int value)
{
    TreeNode *treenode = malloc(sizeof(TreeNode));

    if(treenode == NULL)
        return NULL;

    treenode -> data = value;
    treenode -> left = NULL;
    treenode -> right = NULL;

    return treenode;
}

//定义一个栈结构体
typedef struct Stack
{
    TreeNode **arr;  //存储指向二叉树节点的指针
    int top;         //栈顶下标，-1表示栈为空
    int capacity;    //栈的最大容量
} Stack;

//创建一个栈
Stack *createStack(int capacity)
{
    if(capacity <= 0)
        return NULL;

    Stack *stack = malloc(sizeof(Stack));  //分配结构体的内存

    if(stack == NULL)
        return NULL;

    stack -> arr = malloc(sizeof(TreeNode *) * capacity);  //分配存储节点指针的数组

    if(stack -> arr == NULL)
    {
        free(stack);
        return NULL;
    }

    stack -> top = -1;          //初始栈为空
    stack -> capacity = capacity;  //设置栈的容量

    return stack;               //返回栈指针
}

//判断栈是否为空
//返回1表示栈为空，返回0表示栈不为空
int isEmpty(Stack *stack)
{
    return stack == NULL || stack -> top == -1;
}

//将节点指针放入栈中
void push(Stack *stack, TreeNode *node)
{
    if(stack == NULL || node == NULL)
        return;

    if(stack -> top == stack -> capacity - 1)
    {
        return;  //如果栈已满，不再放入
    }

    stack -> arr[++stack -> top] = node;
}

//弹出栈顶节点，并返回该节点指针
TreeNode *pop(Stack *stack)
{
    if(isEmpty(stack))
    {
        return NULL;  //栈为空，返回NULL
    }

    return stack -> arr[stack -> top--];
    //top--代表弹出栈顶节点后，再更新栈顶下标
}

//非递归前序遍历
void preorderTraversal(TreeNode *root)
{
    if(root == NULL)
        return;

    Stack *stack = createStack(100);

    if(stack == NULL)
    {
        printf("栈创建失败！\n");
        return;
    }

    push(stack, root);

    while(!isEmpty(stack))
    {
        TreeNode *node = pop(stack);

        printf("%d ", node -> data);

        //先压入右子树，再压入左子树
        //因为栈是后进先出，所以左子树会先遍历
        if(node -> right != NULL)
            push(stack, node -> right);

        if(node -> left != NULL)
            push(stack, node -> left);
    }

    free(stack -> arr);
    free(stack);
}

int main(void)
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

    if(root == NULL || node2 == NULL || node3 == NULL ||
       node4 == NULL || node5 == NULL || node6 == NULL ||
       node7 == NULL)
    {
        printf("节点创建失败！\n");

        free(root);
        free(node2);
        free(node3);
        free(node4);
        free(node5);
        free(node6);
        free(node7);

        return 1;
    }

    //连接节点
    root -> left = node2;
    root -> right = node3;
    node2 -> left = node4;
    node2 -> right = node5;
    node3 -> left = node6;
    node3 -> right = node7;

    //非递归前序遍历
    printf("非递归前序遍历：");
    preorderTraversal(root);
    printf("\n");

    //释放节点内存
    free(node4);
    free(node5);
    free(node6);
    free(node7);
    free(node2);
    free(node3);
    free(root);

    return 0;
}