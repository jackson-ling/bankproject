#include <stdio.h>
#include "config_interface.h" // ���ã��������ý��棬������Ӧ�Ĺ���
#include "service.h"          // ҵ�����ͣ���ָ�����ᣬͳ�ƹ��ܣ����ڴ��� / ҵ�����ͣ�

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
            printf("��ѡ���ˣ�ȡ���Ŷ�\n");
            break;
        case '2':
            printf("��ѡ���ˣ�������\n");
            break;
        case '3':
            pause_service(&service_list); // ����ҵ����ͣ����
            break;
        case '4':
            pause_revive(&service_list); // ����ҵ��ָ�����
            break;
        case '5':
            printf("��ѡ���ˣ�ҵ��ͳ��\n");
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
