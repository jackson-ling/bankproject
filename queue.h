#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "define.h"

#define maxsize 100

typedef int elemtype;

typedef struct
{
    elemtype *base;
    int front;
    int rear;

} queue;

// ��������
int queue_init(queue *q, elemtype e);

// ���еĳ�ʼ��
int queue_init(queue *q)
{
    q->base = (elemtype *)malloc(sizeof(elemtype) * maxsize);
    if (!q->base)
    {
        return error;
    }
    q->rear = q->front = 0;
    return ok;
}

// ��ȡ���г���
void get_queue_size(queue *q)
{
    int length;
    length = ((q->rear - q->front + maxsize) % maxsize);
    printf("���г���Ϊ%d\n", length);
}

// ���
int enqueue(queue *q, elemtype e)
{
    if ((q->rear + 1) % maxsize == q->front)
    {
        printf("�����������޷����\n");
    }

    q->base[q->rear] = e;
    q->rear = (q->rear + 1) % maxsize;
    return ok;
}

// ����
int dequeue(queue *q, elemtype *e)
{
    if (q->front == q->rear)
    {
        printf("����Ϊ�գ��޷�����\n");
        return error;
    }

    *e = q->base[q->front];
    printf("����Ԫ��Ϊ��%d", *e);
    q->front = (q->front + 1) % maxsize;
    return ok;
}

// ȡ��ͷԪ��
int getheed(queue *q)
{
    if (q->front != q->rear)
    {
        printf("��ͷԪ��Ϊ%d\n", q->base[q->front]);
        return ok;
    }
}

#endif /* QUEUE_H */
