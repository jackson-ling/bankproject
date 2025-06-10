#ifndef WINDOW_INFO_H
#define WINDOW_INFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // 用于字符串操作
#include "define.h"

#define max_length 30                                                                      // 假设每个窗口信息的最大长度为30
#define FILE_PATH "C:\\Users\\jackson\\Desktop\\bankproject_vscode\\file\\window_info.txt" // 文件路径

typedef struct lnode
{
    char data[max_length]; // 使用字符数组存储窗口信息
    struct lnode *next;
} lnode, *linklist;

// 函数声明
int insert_window_info(linklist l);
int delete_num(linklist l);
int modify_info(linklist l);
int find_elem(linklist l);
int load_from_file(linklist l);
int save_to_file(linklist l);

// 初始化
int init_list(linklist *l)
{
    *l = (linklist)malloc(sizeof(lnode)); // 正确的指针分配
    if (!*l)
    {
        printf("内存分配失败\n");
        return error;
    }
    (*l)->next = NULL;
    load_from_file(*l); // 从文件加载数据
    return ok;
}

// 从文件加载窗口信息
int load_from_file(linklist l)
{
    FILE *file = fopen(FILE_PATH, "r");
    if (!file)
    {
        printf("无法打开文件\n");
        return error;
    }

    lnode *p = l;
    while (!feof(file))
    {
        lnode *new_node = (lnode *)malloc(sizeof(lnode));
        if (fscanf(file, "%s", new_node->data) == 1)
        {
            new_node->next = NULL;
            p->next = new_node;
            p = new_node;
        }
    }
    fclose(file);
    return ok;
}

// 保存窗口信息到文件
int save_to_file(linklist l)
{
    FILE *file = fopen(FILE_PATH, "w");
    if (!file)
    {
        printf("无法打开文件\n");
        return error;
    }

    lnode *p = l->next; // 跳过头节点
    while (p)
    {
        fprintf(file, "%s\n", p->data);
        p = p->next;
    }
    fclose(file);
    return ok;
}

// 增加窗口信息
int insert_window_info(linklist l)
{
    lnode *p = l;

    // 找到链表的末尾
    while (p && p->next)
    {
        p = p->next;
    }

    // 分配新节点
    lnode *s = (lnode *)malloc(sizeof(lnode));
    if (!s)
    {
        printf("内存分配失败\n");
        return error;
    }

    // 用户输入的字符串
    printf("请输入需要新增的窗口信息：");
    scanf(" %s", s->data); // 注意空格清除输入缓冲区

    s->next = NULL;
    p->next = s; // 将新节点链接到链表末尾

    save_to_file(l); // 保存到文件
    return ok;
}

// 删除窗口信息
int delete_num(linklist l)
{
    int i;
    find_elem(l); // 显示所有窗口信息
    printf("请输入需要删除的窗口序号：");
    scanf("%d", &i);

    lnode *p = l;
    int j = 0;
    while (p->next && j < i - 1) // 找到第 i - 1 个节点
    {
        p = p->next;
        j++;
    }

    if (!p->next || j > i - 1)
    {
        printf("序号不合法，无法删除\n");
        return error;
    }

    lnode *q = p->next;
    p->next = q->next; // 删除节点
    free(q);

    save_to_file(l); // 保存到文件
    printf("窗口信息删除成功。\n");

    return ok;
}

// 修改窗口信息
int modify_info(linklist l)
{
    int i;
    find_elem(l);
    printf("请输入需要修改的窗口序号：");
    scanf("%d", &i);

    lnode *p = l->next;
    int j = 1;

    while (p && j < i)
    {
        p = p->next;
        j++;
    }

    if (!p || j != i)
    {
        printf("无效的序号，无法修改\n");
        return error;
    }

    printf("请输入修改信息：");
    scanf(" %s", p->data); // 清除输入缓冲区后读取

    save_to_file(l); // 保存到文件
    return ok;
}

// 查询窗口信息
int find_elem(linklist l)
{
    lnode *p = l->next;
    int j = 1;

    if (!p)
    {
        printf("链表为空\n");
        return error;
    }

    printf("\n---------------窗口信息如下---------------\n");
    while (p)
    {
        printf("%d.%s\n", j, p->data);
        p = p->next;
        j++;
    }
    printf("\n");
    return ok;
}

#endif
