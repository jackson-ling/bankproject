#include <stdio.h>
#include "config_interface.h" // 作用：进入配置界面，调用相应的功能
#include "service.h"          // 业务的暂停，恢复，办结，统计功能（基于窗口 / 业务类型）
#include "queue.h"
#include "service_user.h";
#include "sqlist_service.h"
#include "time_service.h"
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

    queue q;
    queue_init(&q);

    linklist l;
    init_list(&l);

    char service_type[100]; // 存储办理的业务类型，用于记录办理时间

    int show_info_called = 0;

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
            if (!show_info_called)
            {
                show_service_info(&service_list);
                show_info_called = 1;
            }
            printf("\n请输入需要办理的业务类型: ");
            scanf("%s", service_type); // 输入字符串入字符串
            getchar();
            min_number_window();       // 找到一个人数最少的窗口办理，并提示用户到哪排队
            get_num(&q, service_type); // 给用户分配排队号码
            break;
        case '2':

            printf("请输入需要结束的业务类型: ");
            scanf("%s", service_type);
            getchar();

            printf("请输入排队编号: ");
            int queue_number;
            char window_char;
            scanf("%c%d", &window_char, &queue_number);
            while (getchar() != '\n')
                ; // 清空输入缓冲区

            finish(&q, service_type, window_char, queue_number); // 传递排队编号给 finish 函数
            break;
        case '3':
            pause_service(&service_list); // 调用业务暂停功能
            break;
        case '4':
            pause_revive(&service_list); // 调用业务恢复功能
            break;
        case '5':
            char choice_stat;
            printf("-----------可查询的内容如下-----------\n");
            printf("1.基于业务类型的统计（平均排队时间 -- 平均业务办理时间）\n");
            printf("2.基于窗口的统计（平均排队时间 -- 平均业务办理时间）\n");

            while (1)
            {
                printf("\n请输入序号选择功能（输入q退出查询）：");
                // 使用 " %c" 以跳过缓冲区中的换行符
                if (scanf(" %c", &choice_stat) != 1)
                {
                    printf("\n无效输入，请重新输入。\n");
                    while (getchar() != '\n')
                        ; // 清空输入缓冲区
                    continue;
                }

                if (choice_stat == 'q')
                {
                    printf("\n返回主菜单！！！\n\n");
                    break;
                }

                if (choice_stat == '1')
                {
                    printf("\n-----------part 1 : 平均业务办理时间如下-----------\n");
                    calculate_average_times_from_file();
                    printf("\n--------------part 2 : 平均排队时间如下--------------\n");
                }
                else if (choice_stat == '2')
                {
                    printf("\n您选择了：基于窗口的统计\n\n");
                }
                else
                {
                    printf("\n输入有误，请重新输入！\n\n");
                }
            }
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
