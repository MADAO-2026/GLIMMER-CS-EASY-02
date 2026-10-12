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