#ifndef SQLIST_SERVICE_H
#define SQLIST_SERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // ��Ҫ������������ַ���
#include "define.h"

#define maxsize 100
#define max_length 30 // ����ÿ��ҵ����Ϣ����󳤶�Ϊ30

// �����ļ�·������
#define FILENAME "C:\\Users\\jackson\\Desktop\\bankproject_vscode\\file\\service_info.txt"

// ���� Business �ṹ��
typedef struct
{
    char service[max_length]; // �洢ҵ������
    char status[10];          // �洢ҵ���״̬��Ϣ
} Business;

// ���� sqlist �ṹ��
typedef struct
{
    Business elem[maxsize]; // ʹ������洢ҵ����Ϣ
    int length;             // ��ǰҵ����
} sqlist;

// ��������
int sqlist_init(sqlist *l);
int insert_num(sqlist *l);
int modify(sqlist *l);
void show_service_info(sqlist *l);
int save_to_file(sqlist *l);
int load_from_file(sqlist *l);

// ��ʼ��
int sqlist_init(sqlist *l)
{
    l->length = 0; // ʹ�� '->' �����ʽṹ���Ա
    return ok;
}

// ����ҵ����Ϣ����ĩβ����
int insert_num(sqlist *l)
{
    if (l->length == maxsize)
    {
        printf("�ռ��������޷�����\n");
        return error;
    }

    // ����ҵ������
    printf("��������Ҫ������ҵ��");
    scanf("%s", l->elem[l->length].service); // ����һ���ַ������洢

    // ��ʼ��ҵ��״̬Ϊ "����"
    strcpy(l->elem[l->length].status, "����");

    l->length++;

    // ���浽�ļ�
    save_to_file(l);

    return ok;
}

// ҵ���ѯ����ʾȫ����Ϣ
void show_service_info(sqlist *l)
{
    // �����ļ�����
    load_from_file(l);

    printf("\n-----------ҵ���ѯ�������-----------\n");
    for (int i = 0; i < l->length; i++)
    {
        printf("%d. %s  ҵ��״̬��%s\n", i + 1, l->elem[i].service, l->elem[i].status);
    }
}

// �޸�ҵ����Ϣ
int modify(sqlist *l)
{
    printf("\n-----------����ҵ���޸Ĺ���-----------\n");
    show_service_info(l); // ��ʾ��ǰ��Ϣ

    printf("��������Ҫ�޸ĵ�ҵ�����: ");
    int n;
    scanf("%d", &n);

    if (n < 1 || n > l->length)
    {
        printf("��Ч�����\n");
        return error;
    }

    // �����޸ĵ���Ϣ
    printf("�����޸���Ϣ��");
    char new_info[max_length + 1]; // ��ʱ�洢�޸ĵ�����
    scanf("%s", new_info);

    // ֱ�Ӹ���ԭʼ����
    strcpy(l->elem[n - 1].service, new_info); // ����ҵ������

    // ���浽�ļ�
    save_to_file(l);

    printf("\n-----------�޸Ľ������-----------\n");
    show_service_info(l); // ��ʾ�޸ĺ����Ϣ

    return ok;
}

// ����ҵ����Ϣ���ļ�
int save_to_file(sqlist *l)
{
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL)
    {
        printf("�޷����ļ�\n");
        return error;
    }

    for (int i = 0; i < l->length; i++)
    {
        fprintf(file, "%s %s\n", l->elem[i].service, l->elem[i].status);
    }

    fclose(file);
    return ok;
}

// ���ļ�����ҵ����Ϣ
int load_from_file(sqlist *l)
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("�޷����ļ�\n");
        return error;
    }

    l->length = 0; // ���ó���
    while (fscanf(file, "%s %s", l->elem[l->length].service, l->elem[l->length].status) == 2)
    {
        l->length++;
        if (l->length >= maxsize)
        {
            printf("�Ѵﵽ������������޷����ظ���\n");
            break;
        }
    }

    fclose(file);
    return ok;
}

#endif // SQLIST_SERVICE_H
