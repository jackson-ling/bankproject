#ifndef SERVICE_USER_H
#define SERVICE_USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "sqlist_service.h"
#include "time_service.h"

// 假设分配的号码从 1 开始，递增分配号码
static int current_number = 1; // 记录当前分配的号码

// 函数声明
void get_num(queue *q, const char *service_type); // 分配号码并提示排队
void finish(queue *q, char *service_type, char window_char, int queue_number);

void pause_service();  // 暂停服务
void resume_service(); // 恢复服务
// 队列辅助函数
int is_queue_empty(queue *q); // 检查队列是否为空
int peek(queue *q);           // 获取队列中下一个元素，但不移除

// 分配号码并入队
void get_num(queue *q, const char *service_type)
{
    char min_num_window_char;        // 保存不同窗口的编号
    lnode *p = get_min_num_window(); // 获取最少排队人数的窗口节点

    /* 这里是为了实现分配功能，所以以10个窗口为例 */
    // 给最少人数的窗口分配编号，避免不同窗口分配的号码相同发生冲突
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

    // 分配的号码
    printf("\t分配的号码是：%c%d\t", min_num_window_char, current_number);

    start_service_timer(service_type, min_num_window_char, current_number); // 对需要办理的业务类型开始计时

    // 分配号码并入队
    enqueue(q, current_number);

    // 号码递增
    current_number++;

    // 更新窗口信息
    update_window_num();
}

// 结束业务并计算办理时间
void finish(queue *q, char *service_type, char window_char, int queue_number)
{
    // 同一个窗口可以有多个编号，为了实现独立计时，传入编号来区分
    stop_service_timer(service_type, window_char, queue_number);

    // 打印该业务类型的办理时间
    print_service_times(service_type, window_char, queue_number);

    // 队列操作
    dequeue(q);       // 从队列中取出一个业务编号
    current_number--; // 减少号码，确保下一个业务的号码正确

    // 更新窗口信息
    subtract_window_num(); // 假设这是结束一个窗口后需要调用的函数

    // 检查队列是否还有元素
    if (!is_queue_empty(q))
    {
        // 如果队列不为空，则获取下一个排队的号码
        int next_queue_number = peek(q); // 获取队列中下一个元素

        // 根据下一个排队的号码找到对应的窗口名称（假设窗口名称是根据队列顺序来分配的）
        const char *window_names[] = {
            "窗口一", "窗口二", "窗口三", "窗口四", "窗口五",
            "窗口六", "窗口七", "窗口八", "窗口九", "窗口十"};

        // 根据队列顺序选择窗口
        int window_index = (next_queue_number - 1) % 10; // 假设每个窗口轮流接待
        const char *window_name = window_names[window_index];

        // 提示用户下一个人的信息
        printf("\n\t\t\t\t\t请 %c%d 到 %s 办理 %s 业务！！！\n", window_char, next_queue_number, window_name, service_type);
    }
    else
    {
        printf("\n该窗口没有其他排队业务。\n");
    }
}

// 检查队列是否为空
int is_queue_empty(queue *q)
{
    return q->front == q->rear; // 假设你有一个指向队列头部的 front 指针
}

// 获取队列头部元素但不移除
int peek(queue *q)
{
    if (!is_queue_empty(q))
    {
        return q->base[q->front]; // 从队列的 base 数组中获取队头元素
    }
    return -1; // 如果队列为空，返回 -1
}

#endif
