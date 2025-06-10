#ifndef SQLIST_SERVICE_H
#define SQLIST_SERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // 需要这个库来处理字符串
#include "define.h"

#define maxsize 100
#define max_length 30 // 假设每个业务信息的最大长度为30

// 定义文件路径常量
#define FILENAME "C:\\Users\\jackson\\Desktop\\bankproject_vscode\\file\\service_info.txt"

// 定义 Business 结构体
typedef struct
{
    char service[max_length]; // 存储业务名称
    char status[10];          // 存储业务的状态信息
} Business;

// 定义 sqlist 结构体
typedef struct
{
    Business elem[maxsize]; // 使用数组存储业务信息
    int length;             // 当前业务数
} sqlist;

// 函数声明
int sqlist_init(sqlist *l);
int insert_num(sqlist *l);
int modify(sqlist *l);
void show_service_info(sqlist *l);
int save_to_file(sqlist *l);
int load_from_file(sqlist *l);

// 初始化
int sqlist_init(sqlist *l)
{
    l->length = 0; // 使用 '->' 来访问结构体成员
    return ok;
}

// 新增业务信息：在末尾插入
int insert_num(sqlist *l)
{
    if (l->length == maxsize)
    {
        printf("空间已满，无法插入\n");
        return error;
    }

    // 输入业务名称
    printf("请输入需要新增的业务：");
    scanf("%s", l->elem[l->length].service); // 输入一个字符串并存储

    // 初始化业务状态为 "开放"
    strcpy(l->elem[l->length].status, "开放");

    l->length++;

    // 保存到文件
    save_to_file(l);

    return ok;
}

// 业务查询：显示全部信息
void show_service_info(sqlist *l)
{
    // 加载文件内容
    load_from_file(l);

    printf("\n-----------业务查询结果如下-----------\n");
    for (int i = 0; i < l->length; i++)
    {
        printf("%d. %s  业务状态：%s\n", i + 1, l->elem[i].service, l->elem[i].status);
    }
}

// 修改业务信息
int modify(sqlist *l)
{
    printf("\n-----------进入业务修改功能-----------\n");
    show_service_info(l); // 显示当前信息

    printf("请输入需要修改的业务序号: ");
    int n;
    scanf("%d", &n);

    if (n < 1 || n > l->length)
    {
        printf("无效的序号\n");
        return error;
    }

    // 输入修改的信息
    printf("输入修改信息：");
    char new_info[max_length + 1]; // 临时存储修改的内容
    scanf("%s", new_info);

    // 直接覆盖原始数据
    strcpy(l->elem[n - 1].service, new_info); // 更新业务名称

    // 保存到文件
    save_to_file(l);

    printf("\n-----------修改结果如下-----------\n");
    show_service_info(l); // 显示修改后的信息

    return ok;
}

// 保存业务信息到文件
int save_to_file(sqlist *l)
{
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL)
    {
        printf("无法打开文件\n");
        return error;
    }

    for (int i = 0; i < l->length; i++)
    {
        fprintf(file, "%s %s\n", l->elem[i].service, l->elem[i].status);
    }

    fclose(file);
    return ok;
}

// 从文件加载业务信息
int load_from_file(sqlist *l)
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("无法打开文件\n");
        return error;
    }

    l->length = 0; // 重置长度
    while (fscanf(file, "%s %s", l->elem[l->length].service, l->elem[l->length].status) == 2)
    {
        l->length++;
        if (l->length >= maxsize)
        {
            printf("已达到最大数据量，无法加载更多\n");
            break;
        }
    }

    fclose(file);
    return ok;
}

#endif // SQLIST_SERVICE_H
