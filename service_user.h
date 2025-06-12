#ifndef SERVICE_USER_H
#define SERVICE_USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "sqlist_service.h"
#include "time_service.h"

// �������ĺ���� 1 ��ʼ�������������
static int current_number = 1; // ��¼��ǰ����ĺ���

// ��������
void get_num(queue *q, const char *service_type); // ������벢��ʾ�Ŷ�
void finish(queue *q, char *service_type, char window_char, int queue_number);

void pause_service();  // ��ͣ����
void resume_service(); // �ָ�����
// ���и�������
int is_queue_empty(queue *q); // �������Ƿ�Ϊ��
int peek(queue *q);           // ��ȡ��������һ��Ԫ�أ������Ƴ�

// ������벢���
void get_num(queue *q, const char *service_type)
{
    char min_num_window_char;        // ���治ͬ���ڵı��
    lnode *p = get_min_num_window(); // ��ȡ�����Ŷ������Ĵ��ڽڵ�

    /* ������Ϊ��ʵ�ַ��书�ܣ�������10������Ϊ�� */
    // �����������Ĵ��ڷ����ţ����ⲻͬ���ڷ���ĺ�����ͬ������ͻ
    if (p)
    {
        // �������ʮ���������Ƶ��ַ�������
        const char *window_names[] = {
            "����һ", "���ڶ�", "������", "������", "������",
            "������", "������", "���ڰ�", "���ھ�", "����ʮ"};

        // �����ַ������飬�Ƚϴ������Ʋ�������
        for (int i = 0; i < 10; i++)
        {
            if (strcmp(p->data, window_names[i]) == 0)
            {
                min_num_window_char = 'a' + i; // 'a' + ����λ�ã�����ַ� 'a' �� 'j'
                break;                         // �ҵ���Ӧ�Ĵ������ƺ��˳�ѭ��
            }
        }
    }

    // ����ĺ���
    printf("\t����ĺ����ǣ�%c%d\t", min_num_window_char, current_number);

    start_service_timer(service_type, min_num_window_char, current_number); // ����Ҫ�����ҵ�����Ϳ�ʼ��ʱ

    // ������벢���
    enqueue(q, current_number);

    // �������
    current_number++;

    // ���´�����Ϣ
    update_window_num();
}

// ����ҵ�񲢼������ʱ��
void finish(queue *q, char *service_type, char window_char, int queue_number)
{
    // ͬһ�����ڿ����ж����ţ�Ϊ��ʵ�ֶ�����ʱ��������������
    stop_service_timer(service_type, window_char, queue_number);

    // ��ӡ��ҵ�����͵İ���ʱ��
    print_service_times(service_type, window_char, queue_number);

    // ���в���
    dequeue(q);       // �Ӷ�����ȡ��һ��ҵ����
    current_number--; // ���ٺ��룬ȷ����һ��ҵ��ĺ�����ȷ

    // ���´�����Ϣ
    subtract_window_num(); // �������ǽ���һ�����ں���Ҫ���õĺ���

    // �������Ƿ���Ԫ��
    if (!is_queue_empty(q))
    {
        // ������в�Ϊ�գ����ȡ��һ���Ŷӵĺ���
        int next_queue_number = peek(q); // ��ȡ��������һ��Ԫ��

        // ������һ���Ŷӵĺ����ҵ���Ӧ�Ĵ������ƣ����贰�������Ǹ��ݶ���˳��������ģ�
        const char *window_names[] = {
            "����һ", "���ڶ�", "������", "������", "������",
            "������", "������", "���ڰ�", "���ھ�", "����ʮ"};

        // ���ݶ���˳��ѡ�񴰿�
        int window_index = (next_queue_number - 1) % 10; // ����ÿ�����������Ӵ�
        const char *window_name = window_names[window_index];

        // ��ʾ�û���һ���˵���Ϣ
        printf("\n\t\t\t\t\t�� %c%d �� %s ���� %s ҵ�񣡣���\n", window_char, next_queue_number, window_name, service_type);
    }
    else
    {
        printf("\n�ô���û�������Ŷ�ҵ��\n");
    }
}

// �������Ƿ�Ϊ��
int is_queue_empty(queue *q)
{
    return q->front == q->rear; // ��������һ��ָ�����ͷ���� front ָ��
}

// ��ȡ����ͷ��Ԫ�ص����Ƴ�
int peek(queue *q)
{
    if (!is_queue_empty(q))
    {
        return q->base[q->front]; // �Ӷ��е� base �����л�ȡ��ͷԪ��
    }
    return -1; // �������Ϊ�գ����� -1
}

#endif
