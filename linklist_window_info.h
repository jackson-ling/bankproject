#ifndef LINKLIST_WINDOW_INFO_H
#define LINKLIST_WINDOW_INFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // �����ַ�������
#include "define.h"

#define max_length 30                                                                      // ����ÿ��������Ϣ����󳤶�Ϊ30
#define FILE_PATH "C:\\Users\\jackson\\Desktop\\bankproject_vscode\\file\\window_info.txt" // �ļ�·��

typedef struct lnode
{
    char data[max_length]; // ʹ���ַ�����洢������Ϣ�����ƣ�
    int person_num;        // ��¼�Ŷӵ�����
    char status[10];       // ��¼����״̬���� "����" �� "�ر�"��
    struct lnode *next;
} lnode, *linklist;

// ��������
int insert_window_info(linklist l);
int delete_num(linklist l);
int modify_info(linklist l);
int find_elem(linklist l);
int load_from_file(linklist l);
int save_to_file(linklist l);
lnode *get_min_num_window();
void min_number_window();
int init_list(linklist *l);
void update_window_num();
void subtract_window_num();

// ��ʼ��
int init_list(linklist *l)
{
    *l = (linklist)malloc(sizeof(lnode)); // ��ȷ��ָ�����
    if (!*l)
    {
        printf("�ڴ����ʧ��\n");
        return error;
    }
    (*l)->next = NULL;
    load_from_file(*l); // ���ļ���������
    return ok;
}

// ���ļ����ش�����Ϣ
int load_from_file(linklist l)
{
    FILE *file = fopen(FILE_PATH, "r");
    if (!file)
    {
        printf("�޷����ļ�\n");
        return error;
    }

    lnode *p = l;
    while (!feof(file))
    {
        lnode *new_node = (lnode *)malloc(sizeof(lnode));
        if (fscanf(file, " %[^,], %d, %s", new_node->data, &new_node->person_num, new_node->status) == 3) // ��ȡ "��������, �Ŷ�����, ״̬"
        {
            new_node->next = NULL;
            p->next = new_node;
            p = new_node; // ����ָ��p��ָ���½ڵ�
        }
        else
        {
            // �ļ���ʽ����ʱ����������
            char buffer[100];
            fgets(buffer, sizeof(buffer), file); // ��ȡ��������ǰ��
        }
    }
    fclose(file);

    // ����ļ�Ϊ�գ�����ҲӦ��Ϊ��
    if (l->next == NULL)
    {
        printf("�ļ�Ϊ�գ�δ�����κδ�����Ϣ��\n");
    }

    return ok;
}

// ���洰����Ϣ���ļ�
int save_to_file(linklist l)
{
    FILE *file = fopen(FILE_PATH, "w");
    if (!file)
    {
        printf("�޷����ļ�\n");
        return error;
    }

    lnode *p = l->next; // ����ͷ�ڵ�
    while (p)
    {
        fprintf(file, "%s, %d, %s\n", p->data, p->person_num, p->status); // ����ʽ���洰����Ϣ���Ŷ�������״̬
        p = p->next;
    }
    fclose(file);
    return ok;
}

// ���Ӵ�����Ϣ
int insert_window_info(linklist l)
{
    lnode *p = l;

    // �ҵ������ĩβ
    while (p && p->next)
    {
        p = p->next;
    }

    // �����½ڵ�
    lnode *s = (lnode *)malloc(sizeof(lnode));
    if (!s)
    {
        printf("�ڴ����ʧ��\n");
        return error;
    }

    // �û�����Ĵ�������
    printf("��������Ҫ�����Ĵ�����Ϣ��");
    scanf(" %s", s->data); // ע��ո�������뻺����
    getchar();             // ������뻺�����еĻ��з������������ʽ��������

    s->person_num = 0;         // ��ʼ���Ŷ�����Ϊ 0
    strcpy(s->status, "����"); // ��ʼ������״̬Ϊ "����"
    s->next = NULL;
    p->next = s; // ���½ڵ����ӵ�����ĩβ

    save_to_file(l); // ���浽�ļ�
    return ok;
}

// ɾ��������Ϣ
int delete_num(linklist l)
{
    int i;
    find_elem(l); // ��ʾ���д�����Ϣ
    getchar();
    printf("��������Ҫɾ���Ĵ�����ţ�");
    scanf("%d", &i);
    getchar();

    lnode *p = l;
    int j = 0;
    while (p->next && j < i - 1) // �ҵ��� i - 1 ���ڵ�
    {
        p = p->next;
        j++;
    }

    if (!p->next || j > i - 1)
    {
        printf("��Ų��Ϸ����޷�ɾ��\n");
        return error;
    }

    lnode *q = p->next;
    p->next = q->next; // ɾ���ڵ�
    free(q);

    save_to_file(l); // ���浽�ļ�
    printf("������Ϣɾ���ɹ���\n");

    return ok;
}

// �޸Ĵ�����Ϣ
int modify_info(linklist l)
{
    int i;
    find_elem(l);
    getchar();
    printf("��������Ҫ�޸ĵĴ�����ţ�");
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
        printf("��Ч����ţ��޷��޸�\n");
        return error;
    }

    printf("�������޸���Ϣ��");
    scanf(" %s", p->data); // ������뻺�������ȡ��������

    save_to_file(l); // ���浽�ļ�
    return ok;
}

// ��ѯ������Ϣ
int find_elem(linklist l)
{
    lnode *p = l->next;
    int j = 1;

    if (!p)
    {
        printf("����Ϊ��\n");
        return error;
    }

    getchar(); // ���������еĻ��з�
    printf("\n---------------������Ϣ����---------------\n");
    while (p)
    {
        printf("%d. %s, �Ŷ�������%d, ״̬��%s\n", j, p->data, p->person_num, p->status);
        p = p->next;
        j++;
    }
    printf("\n");
    return ok;
}

// ������빦�ܵ�ʵ�֣��ҵ��������ٵĴ��ڷ��䣬����ָ��ڵ��ָ��
lnode *get_min_num_window()
{
    linklist l;
    init_list(&l); // ���ļ����ش�����Ϣ

    lnode *least_queue_window = NULL;
    int least_queue_num = INT_MAX; // ��ʼ��Ϊ���ֵ��ȷ�����ҵ���С���Ŷ�����

    lnode *p = l->next; // ����ͷ�ڵ�
    while (p)
    {
        if (strcmp(p->status, "����") == 0 && p->person_num < least_queue_num) // �ŶӵĴ���Ӧ���ǿ��ŵ�
        {
            least_queue_num = p->person_num;
            least_queue_window = p; // ��¼�Ŷ��������ٵĴ���
        }
        p = p->next;
    }
    return least_queue_window; // ����ָ�������ŶӴ��ڵ�ָ��
}

// �����Ŷ��������ٵĴ��ڲ���ʾ�û����ĸ������Ŷ���Ϣ��ʹ���ļ�������,��ʾ�Ŷ�����ʹ�õ��Ƕ��е�����
void min_number_window()
{
    // ���ò����������ٴ��ڵĺ�����ʹ���ļ�������
    lnode *least_queue_window = get_min_num_window();

    // ��ʾ��Ϣ
    if (least_queue_window)
    {
        if (least_queue_window->person_num == 0)
        {
            // ����Ŷ�����Ϊ0��ֱ����ʾ����ҵ��
            printf("\t�뵽<%s>����ҵ��\t", least_queue_window->data);
        }
        else
        {
            // ����Ŷ�������Ϊ0����ʾ�Ŷ������������Ϣ
            printf("\t�뵽<%s>�Ŷ�\t�Ŷ�������%d\t", least_queue_window->data, least_queue_window->person_num);
        }
    }
    else
    {
        printf("�ļ���û����Ч�Ĵ�����Ϣ\n");
    }
}

// �����ļ��д��ڵ�����
void update_window_num()
{
    linklist l;
    init_list(&l); // ���ļ����ش�����Ϣ

    lnode *least_queue_window = NULL;
    int least_queue_num = INT_MAX; // ��ʼ��Ϊ���ֵ��ȷ�����ҵ���С���Ŷ�����

    lnode *p = l->next; // ����ͷ�ڵ�
    while (p)
    {
        if (strcmp(p->status, "����") == 0 && p->person_num < least_queue_num)
        {
            least_queue_num = p->person_num;
            least_queue_window = p; // ��¼�Ŷ��������ٵĴ���
        }
        p = p->next;
    }

    // ����ҵ��������ŶӵĴ���
    if (least_queue_window != NULL)
    {
        least_queue_window->person_num++; // �����Ŷ�����

        // ���±�����º�����ݵ��ļ�
        FILE *file = fopen(FILE_PATH, "w");
        if (!file)
        {
            printf("�޷����ļ�\n");
            return; // �ļ���ʧ��ʱֱ�ӷ���
        }

        // �����º���������ݱ��浽�ļ�
        p = l->next; // ����ͷ�ڵ�
        while (p)
        {
            fprintf(file, "%s, %d, %s\n", p->data, p->person_num, p->status); // ���洰����Ϣ���Ŷ�������״̬
            p = p->next;
        }

        fclose(file); // �ر��ļ�
    }
}

// �û���ӣ����´����е�����
void subtract_window_num()
{
    linklist l;
    init_list(&l); // ���ļ����ش�����Ϣ

    lnode *least_queue_window = NULL;
    int least_queue_num = INT_MAX; // ��ʼ��Ϊ���ֵ��ȷ�����ҵ���С���Ŷ�����

    lnode *p = l->next; // ����ͷ�ڵ�
    while (p)
    {
        if (strcmp(p->status, "����") == 0 && p->person_num < least_queue_num)
        {
            least_queue_num = p->person_num;
            least_queue_window = p; // ��¼�Ŷ��������ٵĴ���
        }
        p = p->next;
    }

    // ����ҵ��������ŶӵĴ���
    if (least_queue_window != NULL)
    {
        least_queue_window->person_num--; // �����Ŷ�����

        // ���±�����º�����ݵ��ļ�
        FILE *file = fopen(FILE_PATH, "w");
        if (!file)
        {
            printf("�޷����ļ�\n");
            return; // �ļ���ʧ��ʱֱ�ӷ���
        }

        // �����º���������ݱ��浽�ļ�
        p = l->next; // ����ͷ�ڵ�
        while (p)
        {
            fprintf(file, "%s, %d, %s\n", p->data, p->person_num, p->status); // ���洰����Ϣ���Ŷ�������״̬
            p = p->next;
        }

        fclose(file); // �ر��ļ�
    }
}

#endif
