#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist_window_info.h"
#include "queue.h"

// 提示用户到哪里排队（找窗口中排队人数最少）
void min_number_window();

int update_load(lnode *p)
{
    FILE *file = fopen(FILE_PATH, "r");
    if (!file)
    {
        printf("无法打开文件\n");
        return error;
    }

    while (!feof(file))
    {
        lnode *new_node = (lnode *)malloc(sizeof(lnode));
        if (fscanf(file, " %[^,], %d, %s", new_node->data, &new_node->person_num, new_node->status) == 3) // 读取 "窗口名称, 排队人数, 状态"
        {
            new_node->next = NULL;
            p->next = new_node; // 将新节点连接到传入的节点 p
            p = new_node;       // 更新指针 p，指向新节点
        }
        else
        {
            // 文件格式错误时，跳过该行
            char buffer[100];
            fgets(buffer, sizeof(buffer), file); // 读取并丢弃当前行
        }
    }
    fclose(file);

    // 如果文件为空，链表也应该为空
    if (p->next == NULL)
    {
        printf("文件为空，未加载任何窗口信息。\n");
    }

    return ok;
}

// 使用原来的方式保存文件出现问题：在找到最少窗口的人数后，分配号码会把相应的信息删除，重写方法保存文件
// 保存窗口信息到文件
int add_save_file(lnode *p)
{
    FILE *file = fopen(FILE_PATH, "w");
    if (!file)
    {
        printf("无法打开文件\n");
        return error;
    }

    while (p)
    {
        fprintf(file, "%s, %d, %s\n", p->data, p->person_num++, p->status); // 按格式保存窗口信息、排队人数和状态
        p = p->next;                                                        // 移动到下一个节点
    }
    fclose(file);
    return ok;
}

// 取号功能实现
void get_num()
{
    // 初始化一个队列
    queue q;
    queue_init(&q);

    char min_num_window_char;        // 保存不同窗口的编号
    lnode *p = get_min_num_window(); // 获取最少排队人数的窗口节点

    /*

                        说明
    1.这里是为了实现分配功能，所以以10个窗口为例
    2.实际上窗口数量可能更多，如果需要，可以再次基础上开发

    */
    if (p)
    {
        // 定义包含十个窗口名称的字符串数组
        const char *window_names[] = {
            "窗口一", "窗口二", "窗口三", "窗口四", "窗口五",
            "窗口六", "窗口七", "窗口八", "窗口九", "窗口十"};

        // 遍历字符串数组，比较窗口名称并分配编号
        for (int i = 0; i < 10; i++)
        {
            if (strcmp(p->data, window_names[i]) == 0)
            {
                min_num_window_char = 'a' + i; // 'a' + 索引位置，获得字符 'a' 到 'j'
                break;                         // 找到对应的窗口名称后，退出循环
            }
        }
    }

    // 假设分配的号码从 1 开始，递增分配号码
    static int current_number = 1; // 记录当前分配的号码

    // 分配号码并入队
    enqueue(&q, current_number);

    /*
       和void min_number_window()函数中显示的信息做拼接
    */
    printf("\t分配的号码是：%c%d\n", min_num_window_char, current_number);

    // 号码递增
    current_number++;

    // 设置更新文件中的窗口信息功能
    update_load(p);
    add_save_file(p);
    // 设置时间统计功能（入队开始，离队结束）
    // 设置离队功能
}