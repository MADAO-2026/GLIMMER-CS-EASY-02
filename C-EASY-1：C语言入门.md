## C-EASY-1：C语言入门

### part1_了解C语言配置文件

#### 1.GCC与MinGW

- **GCC** 就是一套编译器，负责把你写的 C/C++ 代码翻译成能跑的程序。Linux 上一般自带。

- **MinGW** 是把 GCC 搬到 Windows 上的版本。因为 GCC 原本是 Linux 那边的，Windows 用不了，MinGW 就是让它在 Windows 上能跑，还能生成 `.exe`。

  

#### 2.三个文件的作用

- **c_cpp_properties.json**
  **作用：管代码提示和报错**。告诉 VS Code 你的编译器在哪、头文件在哪、用哪个 C++ 标准。配不好就会出现红波浪线，但程序其实能编译。

- **tasks.json**
  **作用：管编译**。相当于把你在终端敲的 `gcc main.c -o main` 存成一个任务，按快捷键就能编译。

- **launch.json**
  **作用：管调试**。告诉 VS Code 怎么启动调试器（gdb），比如调试哪个程序、要不要先编译、传什么参数。

#### 3.插件

- **为什么要在编辑器里装 C 语言插件？**

  因为 VS Code 本身**只是个文本编辑器**，不是 IDE。它默认只会给文本上色，不认识什么是 `#include`、什么是函数、什么是语法错误。装插件就是让它具备写 C 语言该有的能力。

- **插件的作用：**

1. **代码提示（智能补全）**：你打 `prin`，它提示 `printf`；打 `str.`，它列出 `strlen`、`strcpy` 这些。
2. **语法检查**：写错了当场标红波浪线，不用等编译才发现。
3. **跳转和查找**：按住 Ctrl 点函数名能跳到定义，找代码方便很多。
4. **调试支持**：配合 gdb 打断点、单步执行、看变量值。
5. **格式化**：一键把代码排版弄整齐。
6. **编译运行**：有些插件直接给你个按钮，点一下就编译运行。



ps：launch.json 已完成注释及想要的更改，详情可见仓库对应文件

#### hello world

##### 内置终端：

![image-20260919134314089](C:\Users\MADAO\AppData\Roaming\Typora\typora-user-images\image-20260919134314089.png)

##### 外置终端

![image-20260919134346108](C:\Users\MADAO\AppData\Roaming\Typora\typora-user-images\image-20260919134346108.png)

### part2_C语言基础

#### 1.变量

- **是什么：**变量类型就像是内存中的一个**”盒子“**，**变量的类型决定了这个盒子有多大（占用多少字节），以及它按照什么规则来解读里面存放的 0 和 1 数据**
- **为何重要：**变量的类型**决定了内存有多大（占用多少字节）**，**以及它按照什么规则来解读里面存放的 0 和 1 数据**，此外，还与**运算规则**，**编译器检查**有关。

- **存放年龄：**用**整数**

- **存放apple：不能**只用一个char类型的字符变量，可以考虑定义一个字符数组

  ```c
  #include <stdio.h>
  
  int main()
  {
      char word[6] = "apple";//第六个位置表示\0（空字符）
      printf("%s",word);
      
      return 0;
  }
  ```

#### 2.数组的起始和边界

- 下标通常从**0**开始
- 数组越界问题
  - **读取到垃圾数据（读取越界）**，例如在读取arr[5]时，它会老老实实地去内存中 `arr` 首地址往后偏移 5 个 `int` 大小的位置，把那里的二进制数据当作一个整数读出来。
  - **篡改其他变量的值（写入越界）**，如果执行 arr[5] = 100，实际上把 arr 后面相邻的那块内存给覆盖了,原本在这片区域的变量值会被篡改。
  -  **段错误（Segmentation Fault）导致程序崩溃**

- 为何常见：
  - **循环条件写错**，以arr[5]为例，循环条件易写成 for (int i = 0; i <= 5; i++)
  - **输入不可控**，以arr[5]为例,数组大小确定，但用户输入的长度可能大于了数组的容量

- **为何危险**
  - **C 语言不检查越界**：这是 C 语言为了**运行效率**做出的妥协。
  - **隐蔽性极强**，篡改其他变量的值（写入越界）这一问题编译器不会报错，程序可能运行很久之后才因为数据错乱而崩溃。
  - **安全隐患（缓冲区溢出攻击）**：这是黑客最常用的攻击手段之一。如果程序存在数组越界写入的漏洞，黑客可以精心构造一段超长的数据，覆盖掉函数返回地址等关键内存区域，从而劫持程序的执行流程，植入病毒或获取系统权限。

#### 3.流程控制-循环结构

- 基本结构

  - for循环

    ```c
    for (初始化; 条件判断; 迭代)
    {
        // 循环体
    }
    ```

    

  - while循环

    ```c
    while (条件)
    {
        // 循环体
    }
    ```

- for循环各自作用

  - **初始化**：设置循环变量的初始值，**只执行一次**。

  - **条件判断**：

    每次循环开始前判断：

    - 条件成立 → 执行循环体
    - 条件不成立 → 结束循环

  - **迭代**：每次执行完循环体之后，改变循环变量的值，进行下一次的判断

- while 循环和 do…while 循环区别：**第一次判断条件的时机不同**
  - while循环：**先判断条件，再执行循环体。**
  - do...while循环:**先执行一次循环体，再判断条件。**

- 实现同一个任务(计算1~10的和)

  - while循环

    ```c
    #include <stdio.h>
    
    int main()
    {
        int i = 1;
        int sum = 0;
    
        while (i <= 10)
        {
            sum = sum + i;
            i++;
        }
    
        printf("%d\n", sum);
    
        return 0;
    }
    ```

    

  - do...while循环

    ```c
    #include <stdio.h>
    
    int main()
    {
        int i = 1;
        int sum = 0;
    
        do
        {
            sum = sum + i;
            i++;
        }
        while (i <= 10);
    
        printf("%d\n", sum);
    
        return 0;
    }
    ```

  

#### 4.**流程控制 - 逻辑表达式**

- 两种表达式区别
  - 运算对象方面：**算术表达式**主要对**数值**进行运算，**逻辑表达式**主要对**条件（真假）**进行判断。
  - 运算结果方面：算术表达式的结果通常是一个数值，逻辑表达式的结果是“true”或“false”。

- 三种运算符的含义

  - &&——逻辑与：

    表示：**并且**

    只有两个条件**同时为真**，结果才为真。

    

  - `||` —— 逻辑或：

    表示：**或者**

    只要两个条件中**至少有一个为真**，结果就为真。

    

  - `!` —— 逻辑非

    表示：**取反**

    把原来的真假状态反过来：

    

```c
#include <stdio.h>

int main()
{
    char name[50];
    int age;
    int count = 0;// 记录次数
    char choice;//（y or n）

    while (1)
    {
        // 1. 读取姓名和年龄
        printf("请输入姓名和年龄：");
        scanf("%s %d", name, &age);

        // 2. 按原格式打印姓名和年龄
        printf("姓名：%s，年龄：%d\n", name, age);

        // 3. 记录操作次数
        count++;

        printf("是否继续输入？(y/n)：");
        scanf(" %c", &choice);

        // 4. 判断是否继续
        if (choice == 'n')
        {
            break;
        }
    }

    // 5. 打印操作次数
    printf("一共进行了 %d 次读取输入->打印内容操作。\n", count);

    return 0;
}
```

### part3_函数

#### 1.成绩的计算与排序

```c
#include <stdio.h>

// 计算乘方
int ex(int a, int b)
{
    int result = 1;

    for (int i = 0; i < b; i++)
    {
        result *= a;
    }

    return result;
}

// 计算一个人的综合成绩
int calculate_zh(int a, int b, int c)
{
    int p = (a + b + c) / 3;

    int f = (ex(p - a, 2)
           + ex(p - b, 2)
           + ex(p - c, 2)) / 3;

    int zh = 3 * p - f / 3;

    return zh;
}

// 对三个人的综合成绩进行排序
void sort(int zh1, int zh2, int zh3)
{
    if (zh1 >= zh2 && zh2 >= zh3)
    {
        printf("小明 > 小强 > 小林");
    }
    else if (zh1 >= zh3 && zh3 >= zh2)
    {
        printf("小明 > 小林 > 小强");
    }
    else if (zh2 >= zh1 && zh1 >= zh3)
    {
        printf("小强 > 小明 > 小林");
    }
    else if (zh2 >= zh3 && zh3 >= zh1)
    {
        printf("小强 > 小林 > 小明");
    }
    else if (zh3 >= zh1 && zh1 >= zh2)
    {
        printf("小林 > 小明 > 小强");
    }
    else
    {
        printf("小林 > 小强 > 小明");
    }
}

int main()
{
    int x1, x2, x3;
    int y1, y2, y3;
    int z1, z2, z3;

    printf("请输入小明的三项成绩（顺序为A B C,以一个空格为间隔）：");
    scanf("%d %d %d", &x1, &x2, &x3);

    printf("请输入小强的三项成绩（顺序为A B C,以一个空格为间隔）：");
    scanf("%d %d %d", &y1, &y2, &y3);

    printf("请输入小林的三项成绩（顺序为A B C,以一个空格为间隔）：");
    scanf("%d %d %d", &z1, &z2, &z3);

    int zh1 = calculate_zh(x1, x2, x3);
    int zh2 = calculate_zh(y1, y2, y3);
    int zh3 = calculate_zh(z1, z2, z3);

    sort(zh1, zh2, zh3);

    return 0;
}
```

#### 2.swap（a,b）

**1**.**结果**：变量a和变量b的值发生交换

**原因**：

```c
void swap(int a, int b){
  int temp = a;//把a的值赋值给temp
  a = b;//把b的值赋值给a
  b = temp;//把temp的值（来自a）赋值给b
    //到这就实现了两个变量值的互换
}

int main(){
  int a = 10;
  int b = 20;
  swap(a, b);//调用函数
}
```



**2**.真正实现值交换

```c
#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a = 10;
    int b = 20;

    swap(&a, &b);

    printf("%d %d",a,b);

    return 0;
}
```

