#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist_window_info.h"
#include "queue.h"

// ��ʾ�û��������Ŷӣ��Ҵ������Ŷ��������٣�
void min_number_window();

int update_load(lnode *p)
{
    FILE *file = fopen(FILE_PATH, "r");
    if (!file)
    {
        printf("�޷����ļ�\n");
        return error;
    }

    while (!feof(file))
    {
        lnode *new_node = (lnode *)malloc(sizeof(lnode));
        if (fscanf(file, " %[^,], %d, %s", new_node->data, &new_node->person_num, new_node->status) == 3) // ��ȡ "��������, �Ŷ�����, ״̬"
        {
            new_node->next = NULL;
            p->next = new_node; // ���½ڵ����ӵ�����Ľڵ� p
            p = new_node;       // ����ָ�� p��ָ���½ڵ�
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
    if (p->next == NULL)
    {
        printf("�ļ�Ϊ�գ�δ�����κδ�����Ϣ��\n");
    }

    return ok;
}

// ʹ��ԭ���ķ�ʽ�����ļ��������⣺���ҵ����ٴ��ڵ������󣬷����������Ӧ����Ϣɾ������д���������ļ�
// ���洰����Ϣ���ļ�
int add_save_file(lnode *p)
{
    FILE *file = fopen(FILE_PATH, "w");
    if (!file)
    {
        printf("�޷����ļ�\n");
        return error;
    }

    while (p)
    {
        fprintf(file, "%s, %d, %s\n", p->data, p->person_num++, p->status); // ����ʽ���洰����Ϣ���Ŷ�������״̬
        p = p->next;                                                        // �ƶ�����һ���ڵ�
    }
    fclose(file);
    return ok;
}

// ȡ�Ź���ʵ��
void get_num()
{
    // ��ʼ��һ������
    queue q;
    queue_init(&q);

    char min_num_window_char;        // ���治ͬ���ڵı��
    lnode *p = get_min_num_window(); // ��ȡ�����Ŷ������Ĵ��ڽڵ�

    /*

                        ˵��
    1.������Ϊ��ʵ�ַ��书�ܣ�������10������Ϊ��
    2.ʵ���ϴ����������ܸ��࣬�����Ҫ�������ٴλ����Ͽ���

    */
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

    // �������ĺ���� 1 ��ʼ�������������
    static int current_number = 1; // ��¼��ǰ����ĺ���

    // ������벢���
    enqueue(&q, current_number);

    /*
       ��void min_number_window()��������ʾ����Ϣ��ƴ��
    */
    printf("\t����ĺ����ǣ�%c%d\n", min_num_window_char, current_number);

    // �������
    current_number++;

    // ���ø����ļ��еĴ�����Ϣ����
    update_load(p);
    add_save_file(p);
    // ����ʱ��ͳ�ƹ��ܣ���ӿ�ʼ����ӽ�����
    // ������ӹ���
}