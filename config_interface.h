#include <stdio.h>
#include "sqlist_service.h"       // 实现业务信息的功能：增、改、查
#include "linklist_window_info.h" // 实现窗口信息的功能：增、删、改、查

// 函数声明，避免后续在函数中的调用报错
int main_menu();
int config_interface();

int confirmExit()
{
    char confirm;
    printf("确定退出系统吗？(y/n)：");
    scanf(" %c", &confirm); // 使用 " %c" 来跳过缓冲区中的换行符

    if (confirm == 'y' || confirm == 'Y') // 如果用户输入 y 或 Y
    {
        printf("退出系统\n");
        return 1; // 返回 1 表示退出
    }
    else if (confirm == 'n' || confirm == 'N') // 如果用户输入 n 或 N
    {
        printf("取消退出\n");
        return 0; // 返回 0 表示不退出
    }
    else
    {
        printf("无效输入，请输入 'y' 或 'n'。\n");
        return confirmExit(); // 递归调用，直到用户输入有效的 y 或 n
    }
}

void clear()
{
    system("cls");
    printf("\n\n-----------配置管理界面-----------\n\n");
    printf("命令号\t功能\n");
    printf("1\t业务新增\n");
    printf("2\t业务修改\n");
    printf("3\t业务查询\n\n");
    printf("4\t窗口新增\n");
    printf("5\t窗口删除\n");
    printf("6\t窗口修改\n");
    printf("7\t窗口查询\n\n");
    printf("c\t清屏\n");
    printf("h\t帮助\n");
    printf("q\t退出\n");
}

int config_interface()
{
    printf("\n\n-----------配置管理界面-----------\n\n");
    printf("命令号\t功能\n");
    printf("1\t业务新增\n");
    printf("2\t业务修改\n");
    printf("3\t业务查询\n\n");
    printf("4\t窗口新增\n");
    printf("5\t窗口删除\n");
    printf("6\t窗口修改\n");
    printf("7\t窗口查询\n\n");
    printf("c\t清屏\n");
    printf("h\t帮助\n");
    printf("q\t退出\n");

    char choice;

    // 数据结构声明部分

    // 业务信息功能部分
    sqlist l;        // 顺序表的定义
    sqlist_init(&l); // 初始化顺序表

    // 窗口信息功能部分
    lnode *link_list;      // 链表的定义
    init_list(&link_list); // 初始化链表

    while (1)
    {
        printf("\n请输入命令号：");

        if (scanf(" %c", &choice) != 1) // 使用 " %c" 来跳过缓冲区中的换行符
        {
            printf("无效输入，请重新输入。\n");
            while (getchar() != '\n')
                ; // 清空输入缓冲区中的换行符
            continue;
        }

        switch (choice)
        {
        case '1':
            insert_num(&l); // 传递指针
            break;
        case '2':
            modify(&l); // 传递指针
            break;
        case '3':
            show_service_info(&l); // 传递指针
            break;
        case '4':
            insert_window_info(link_list);
            break;
        case '5':
            delete_num(link_list);
            break;
        case '6':
            modify_info(link_list);
            break;
        case '7':
            find_elem(link_list);
            break;
        case 'c':
            clear();
            break;
        case 'h':
            printf("帮助信息...\n");
            break;
        case 'q':
            if (confirmExit())
            {
                printf("-----------退出了配置管理界面-----------\n\n");
                printf("-----------进入银行业务排队管理系统-----------\n");
                printf("命令号\t功能\n");
                printf("1\t取号排队\n");
                printf("2\t办结离队\n\n");
                printf("3\t业务暂停\n");
                printf("4\t业务恢复\n");
                printf("5\t业务统计\n");
                printf("6\t进度查询\n\n");
                printf("7\t配置管理...\n");
                printf("8\t调试信息\n\n");
                printf("c\t清屏\n");
                printf("h\t帮助\n");
                printf("q\t退出\n");
                return 0; // 返回调用处
            }
            break;
        default:
            printf("无效的命令号，请重新输入。\n");
            break;
        }
    }
}
