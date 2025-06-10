#include <stdio.h>
#include "sqlist_service.h"       // ʵ��ҵ����Ϣ�Ĺ��ܣ������ġ���
#include "linklist_window_info.h" // ʵ�ִ�����Ϣ�Ĺ��ܣ�����ɾ���ġ���

// ������������������ں����еĵ��ñ���
int main_menu();
int config_interface();

int confirmExit()
{
    char confirm;
    printf("ȷ���˳�ϵͳ��(y/n)��");
    scanf(" %c", &confirm); // ʹ�� " %c" �������������еĻ��з�

    if (confirm == 'y' || confirm == 'Y') // ����û����� y �� Y
    {
        printf("�˳�ϵͳ\n");
        return 1; // ���� 1 ��ʾ�˳�
    }
    else if (confirm == 'n' || confirm == 'N') // ����û����� n �� N
    {
        printf("ȡ���˳�\n");
        return 0; // ���� 0 ��ʾ���˳�
    }
    else
    {
        printf("��Ч���룬������ 'y' �� 'n'��\n");
        return confirmExit(); // �ݹ���ã�ֱ���û�������Ч�� y �� n
    }
}

void clear()
{
    system("cls");
    printf("\n\n-----------���ù������-----------\n\n");
    printf("�����\t����\n");
    printf("1\tҵ������\n");
    printf("2\tҵ���޸�\n");
    printf("3\tҵ���ѯ\n\n");
    printf("4\t��������\n");
    printf("5\t����ɾ��\n");
    printf("6\t�����޸�\n");
    printf("7\t���ڲ�ѯ\n\n");
    printf("c\t����\n");
    printf("h\t����\n");
    printf("q\t�˳�\n");
}

int config_interface()
{
    printf("\n\n-----------���ù������-----------\n\n");
    printf("�����\t����\n");
    printf("1\tҵ������\n");
    printf("2\tҵ���޸�\n");
    printf("3\tҵ���ѯ\n\n");
    printf("4\t��������\n");
    printf("5\t����ɾ��\n");
    printf("6\t�����޸�\n");
    printf("7\t���ڲ�ѯ\n\n");
    printf("c\t����\n");
    printf("h\t����\n");
    printf("q\t�˳�\n");

    char choice;

    // ���ݽṹ��������

    // ҵ����Ϣ���ܲ���
    sqlist l;        // ˳���Ķ���
    sqlist_init(&l); // ��ʼ��˳���

    // ������Ϣ���ܲ���
    lnode *link_list;      // ����Ķ���
    init_list(&link_list); // ��ʼ������

    while (1)
    {
        printf("\n����������ţ�");

        if (scanf(" %c", &choice) != 1) // ʹ�� " %c" �������������еĻ��з�
        {
            printf("��Ч���룬���������롣\n");
            while (getchar() != '\n')
                ; // ������뻺�����еĻ��з�
            continue;
        }

        switch (choice)
        {
        case '1':
            insert_num(&l); // ����ָ��
            break;
        case '2':
            modify(&l); // ����ָ��
            break;
        case '3':
            show_service_info(&l); // ����ָ��
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
            printf("������Ϣ...\n");
            break;
        case 'q':
            if (confirmExit())
            {
                printf("-----------�˳������ù������-----------\n\n");
                printf("-----------��������ҵ���Ŷӹ���ϵͳ-----------\n");
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
                return 0; // ���ص��ô�
            }
            break;
        default:
            printf("��Ч������ţ����������롣\n");
            break;
        }
    }
}
