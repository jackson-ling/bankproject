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

// 函数声明
int queue_init(queue *q, elemtype e);

// 队列的初始化
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

// 获取队列长度
int get_queue_size(queue *q)
{
    int length;
    length = ((q->rear - q->front + maxsize) % maxsize);
    return length;
}

// 入队
int enqueue(queue *q, elemtype e)
{
    if ((q->rear + 1) % maxsize == q->front)
    {
        printf("队列已满，无法入队\n");
    }

    q->base[q->rear] = e;
    q->rear = (q->rear + 1) % maxsize;
    return ok;
}

// 出队
int dequeue(queue *q)
{
    if (q->front == q->rear)
    {
        printf("队列为空，无法出队\n");
        return error;
    }
    // 队列用来保存排队人数，无需输出信息，出队后，把对应位置的值置为0即可
    q->base[q->front] = 0;
    q->front = (q->front + 1) % maxsize;
    return ok;
}

// 取队头元素
int getheed(queue *q)
{
    if (q->front != q->rear)
    {
        printf("队头元素为%d\n", q->base[q->front]);
        return ok;
    }
}

#endif /* QUEUE_H */
