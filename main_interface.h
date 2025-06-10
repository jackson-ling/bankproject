#include <stdio.h>
#include "config_interface.h"

int main_interface()
{
    printf("银行业务排队管理系统\n\n");
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
            printf("您选择了：业务暂停\n");
            break;
        case '4':
            printf("您选择了：业务恢复\n");
            break;
        case '5':
            printf("您选择了：业务统计\n");
            break;
        case '6':
            printf("您选择了：进度查询\n");
            break;
        case '7':
            printf("---------------进入配置管理界面---------------\n");
            config_interface();
            break;
        case '8':
            printf("您选择了：调试信息\n");
            break;
        case 'c':
            printf("清屏...\n");
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
