#include <stdio.h>
#include "config_interface.h" // 作用：进入配置界面，调用相应的功能
#include "service.h"          // 业务的暂停，恢复，办结，统计功能（基于窗口 / 业务类型）

void clear_main()
{
    system("cls");
    printf("-----------银行业务排队管理系统-----------\n\n");
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
}

int main()
{
    printf("-----------银行业务排队管理系统-----------\n\n");
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

    char choice;

    sqlist service_list;
    sqlist_init(&service_list); // 初始化业务信息列表

    while (1)
    {
        printf("\n请输入命令号：");

        // 使用 " %c" 以跳过缓冲区中的换行符
        if (scanf(" %c", &choice) != 1)
        {
            printf("无效输入，请重新输入。\n");
            while (getchar() != '\n')
                ; // 清空输入缓冲区
            continue;
        }

        switch (choice)
        {
        case '1':
            printf("您选择了：取号排队\n");
            break;
        case '2':
            printf("您选择了：办结离队\n");
            break;
        case '3':
            pause_service(&service_list); // 调用业务暂停功能
            break;
        case '4':
            pause_revive(&service_list); // 调用业务恢复功能
            break;
        case '5':
            printf("您选择了：业务统计\n");
            break;
        case '6':
            printf("您选择了：进度查询\n");
            break;
        case '7':
            config_interface();
            break;
        case '8':
            printf("您选择了：调试信息\n");
            break;
        case 'c':
            clear_main();
            break;
        case 'h':
            printf("帮助信息...\n");
            break;
        case 'q':
            if (confirmExit())
            {
                return 0;
            }
            break;
        default:
            printf("无效的命令号，请重新输入。\n");
            break;
        }
    }

    return 0;
}
