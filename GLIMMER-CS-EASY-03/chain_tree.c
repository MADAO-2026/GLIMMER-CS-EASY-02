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

//前序遍历
void preorder(TreeNode *root)
{
    if(root == NULL) return;

    printf("%d ", root -> data);
    preorder(root -> left);
    preorder(root -> right);
}

//中序遍历
void inorder(TreeNode *root)
{
    if(root == NULL) return;

    inorder(root -> left);
    printf("%d ", root -> data);
    inorder(root -> right);
}

//后序遍历
void postorder(TreeNode *root)
{
    if(root == NULL) return;

    postorder(root -> left);
    postorder(root -> right);
    printf("%d ", root -> data);
}

//current_depth 代表当前走到了第几层，max_depth代表走到过的最高层
int depth(TreeNode *root, int current_depth, int max_depth)
{
    if(root == NULL) return max_depth;

    current_depth++;

    if(current_depth > max_depth)
        max_depth = current_depth;

    max_depth = depth(root -> left, current_depth, max_depth);
    max_depth = depth(root -> right, current_depth, max_depth);

    return max_depth;
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

    //前序遍历
    printf("前序遍历：");
    preorder(root);
    printf("\n");

    //中序遍历
    printf("中序遍历：");
    inorder(root);
    printf("\n");

    //后序遍历
    printf("后序遍历：");
    postorder(root);
    printf("\n");

    //统计树的深度
    printf("树的深度：%d\n", depth(root, 0, 0));

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