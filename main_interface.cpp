#include <stdio.h>
#include "config_interface.h" // ���ã��������ý��棬������Ӧ�Ĺ���
#include "service.h"          // ҵ�����ͣ���ָ�����ᣬͳ�ƹ��ܣ����ڴ��� / ҵ�����ͣ�
#include "queue.h"
#include "service_user.h";
#include "sqlist_service.h"
#include "time_service.h"
void clear_main()
{
    system("cls");
    printf("-----------����ҵ���Ŷӹ���ϵͳ-----------\n\n");
    printf("�����\t����\n");
    printf("1\tȡ���Ŷ�\n");
    printf("2\t������\n\n");
    printf("3\tҵ����ͣ\n");
    printf("4\tҵ��ָ�\n");
    printf("5\tҵ��ͳ��\n");
    printf("6\t���Ȳ�ѯ\n\n");
    printf("7\t���ù���...\n");
    printf("8\t������Ϣ\n\n");
    printf("c\t����\n");
    printf("h\t����\n");
    printf("q\t�˳�\n");
}

int main()
{
    printf("-----------����ҵ���Ŷӹ���ϵͳ-----------\n\n");
    printf("�����\t����\n");
    printf("1\tȡ���Ŷ�\n");
    printf("2\t������\n\n");
    printf("3\tҵ����ͣ\n");
    printf("4\tҵ��ָ�\n");
    printf("5\tҵ��ͳ��\n");
    printf("6\t���Ȳ�ѯ\n\n");
    printf("7\t���ù���...\n");
    printf("8\t������Ϣ\n\n");
    printf("c\t����\n");
    printf("h\t����\n");
    printf("q\t�˳�\n");

    char choice;

    sqlist service_list;
    sqlist_init(&service_list); // ��ʼ��ҵ����Ϣ�б�

    queue q;
    queue_init(&q);

    linklist l;
    init_list(&l);

    char service_type[100]; // �洢�����ҵ�����ͣ����ڼ�¼����ʱ��

    int show_info_called = 0;

    while (1)
    {
        printf("\n����������ţ�");

        // ʹ�� " %c" �������������еĻ��з�
        if (scanf(" %c", &choice) != 1)
        {
            printf("��Ч���룬���������롣\n");
            while (getchar() != '\n')
                ; // ������뻺����
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
            printf("\n��������Ҫ�����ҵ������: ");
            scanf("%s", service_type); // �����ַ������ַ���
            getchar();
            min_number_window();       // �ҵ�һ���������ٵĴ��ڰ�������ʾ�û������Ŷ�
            get_num(&q, service_type); // ���û������ŶӺ���
            break;
        case '2':

            printf("��������Ҫ������ҵ������: ");
            scanf("%s", service_type);
            getchar();

            printf("�������Ŷӱ��: ");
            int queue_number;
            char window_char;
            scanf("%c%d", &window_char, &queue_number);
            while (getchar() != '\n')
                ; // ������뻺����

            finish(&q, service_type, window_char, queue_number); // �����Ŷӱ�Ÿ� finish ����
            break;
        case '3':
            pause_service(&service_list); // ����ҵ����ͣ����
            break;
        case '4':
            pause_revive(&service_list); // ����ҵ��ָ�����
            break;
        case '5':
            char choice_stat;
            printf("-----------�ɲ�ѯ����������-----------\n");
            printf("1.����ҵ�����͵�ͳ�ƣ�ƽ���Ŷ�ʱ�� -- ƽ��ҵ�����ʱ�䣩\n");
            printf("2.���ڴ��ڵ�ͳ�ƣ�ƽ���Ŷ�ʱ�� -- ƽ��ҵ�����ʱ�䣩\n");

            while (1)
            {
                printf("\n���������ѡ���ܣ�����q�˳���ѯ����");
                // ʹ�� " %c" �������������еĻ��з�
                if (scanf(" %c", &choice_stat) != 1)
                {
                    printf("\n��Ч���룬���������롣\n");
                    while (getchar() != '\n')
                        ; // ������뻺����
                    continue;
                }

                if (choice_stat == 'q')
                {
                    printf("\n�������˵�������\n\n");
                    break;
                }

                if (choice_stat == '1')
                {
                    printf("\n-----------part 1 : ƽ��ҵ�����ʱ������-----------\n");
                    calculate_average_times_from_file();
                    printf("\n--------------part 2 : ƽ���Ŷ�ʱ������--------------\n");
                }
                else if (choice_stat == '2')
                {
                    printf("\n��ѡ���ˣ����ڴ��ڵ�ͳ��\n\n");
                }
                else
                {
                    printf("\n�����������������룡\n\n");
                }
            }
            break;
        case '6':
            printf("��ѡ���ˣ����Ȳ�ѯ\n");
            break;
        case '7':
            config_interface();
            break;
        case '8':
            printf("��ѡ���ˣ�������Ϣ\n");
            break;
        case 'c':
            clear_main();
            break;
        case 'h':
            printf("������Ϣ...\n");
            break;
        case 'q':
            if (confirmExit())
            {
                return 0;
            }
            break;
        default:
            printf("��Ч������ţ����������롣\n");
            break;
        }
    }

    return 0;
}
