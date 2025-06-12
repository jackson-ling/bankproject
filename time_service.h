#ifndef TIME_SERVICE_H
#define TIME_SERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SERVICES 100                                                                    // �������֧��100��ҵ������
#define FILE_PATH "C:\\Users\\jackson\\Desktop\\bankproject_vscode\\file\\service_time.txt" // �ļ�·��

// ����һ���ṹ��������ÿ��ҵ�����͵�ʱ����Ϣ
typedef struct
{
    time_t start_time;     // ��¼ҵ��ʼ��ʱ��
    time_t end_time;       // ��¼ҵ�������ʱ��
    double duration;       // ��¼ÿ��ҵ�����ĳ���ʱ��
    char queue_number[20]; // �Ŷӱ�ţ����������ַ����Ŷӱ�ţ�
    char window_char;      // �����ַ�
    int queue_id;          // �Ŷӱ��
} ServiceTime;

// ����һ���������洢��ͬҵ�����͵İ���ʱ����Ϣ
typedef struct
{
    char service_type[100];          // ҵ����������
    ServiceTime times[MAX_SERVICES]; // ��Ӧҵ�����͵����а���ʱ��
    int count;                       // ��ǰҵ�����͵İ������
} ServiceRecord;

ServiceRecord service_records[MAX_SERVICES]; // �洢����ҵ�����͵ļ�¼
int service_type_count = 0;                  // ��ǰ֧�ֵ�ҵ��������

// ������������

// �ҵ���Ӧ��ҵ�����ͼ�¼
ServiceRecord *find_service_record(const char *service_type);

// ��¼ҵ��Ŀ�ʼʱ��
void start_service_timer(const char *service_type, char window_char, int queue_number);

// ��¼ҵ��Ľ���ʱ�䲢�������ʱ�䣨����ӡ�κ���Ϣ��
void stop_service_timer(const char *service_type, char window_char, int queue_number);

// ��ӡָ��ҵ�����͡����ں��Ŷӱ�ŵİ���ʱ��
void print_service_times(const char *service_type, char window_char, int queue_number);

// ��ӡ����ʱ���¼
void print_all_service_times();

// ͳ���ļ��еĲ�ͬҵ�����͵�ƽ������ʱ��
void calculate_average_times_from_file();

// �ҵ���Ӧ��ҵ�����ͼ�¼
ServiceRecord *find_service_record(const char *service_type)
{
    for (int i = 0; i < service_type_count; i++)
    {
        if (strcmp(service_records[i].service_type, service_type) == 0)
        {
            return &service_records[i];
        }
    }
    return NULL;
}

// ���ݴ����ַ����ض�Ӧ�Ĵ�������
const char *get_window_name(char window_char)
{
    // ��������������Ƶ��ַ�������
    const char *window_names[] = {
        "����һ", "���ڶ�", "������", "������", "������",
        "������", "������", "���ڰ�", "���ھ�", "����ʮ"};

    // ���ݴ���� window_char ���ض�Ӧ�Ĵ�������
    if (window_char >= 'a' && window_char <= 'j')
    {
        return window_names[window_char - 'a']; // 'a' -> "����һ", 'b' -> "���ڶ�", ...
    }
    return "δ֪����"; // ����ַ�������Ч��Χ�ڣ�����δ֪����
}

// ��¼ҵ��Ŀ�ʼʱ��
void start_service_timer(const char *service_type, char window_char, int queue_number)
{
    ServiceRecord *record = find_service_record(service_type);
    if (record == NULL)
    {
        // ���û���ҵ���ҵ�����ͣ��򴴽��µļ�¼
        strcpy(service_records[service_type_count].service_type, service_type);
        record = &service_records[service_type_count];
        record->count = 0;
        service_type_count++;
    }

    // ����Ŷӱ��
    char queue_number_str[20];
    sprintf(queue_number_str, "%c%d", window_char, queue_number); // ��ʽ��Ϊ "�����ַ�+�Ŷӱ��"

    // ��ȡ��ǰʱ�䲢��¼
    time_t current_time = time(NULL);
    record->times[record->count].start_time = current_time;              // ��ȡ��ǰʱ���
    strcpy(record->times[record->count].queue_number, queue_number_str); // �����Ŷӱ��
    record->times[record->count].window_char = window_char;              // ���洰�ڱ��
    record->times[record->count].queue_id = queue_number;                // �����Ŷӱ��

    // ʹ�� strftime ��ʽ��ʱ��Ϊ "ʱ:��:��"
    struct tm *start_tm = localtime(&current_time);
    char start_time_str[9]; // ��ʽ�����ʱ���ַ�����ʱ:��:�룩
    strftime(start_time_str, sizeof(start_time_str), "%H:%M:%S", start_tm);

    printf("    ����: %s\t��ʼʱ��: %s\n", service_type, start_time_str);
}

// ��¼ҵ��Ľ���ʱ�䲢�������ʱ�䣨����ӡ�κ���Ϣ��
void stop_service_timer(const char *service_type, char window_char, int queue_number)
{
    ServiceRecord *record = find_service_record(service_type);
    if (record != NULL)
    {
        // ����Ŷӱ��
        char queue_number_str[20];
        sprintf(queue_number_str, "%c%d", window_char, queue_number); // ��ʽ��Ϊ "�����ַ�+�Ŷӱ��"

        // ��ȡ��ǰ����ʱ��
        time_t current_time = time(NULL);
        record->times[record->count].end_time = current_time;

        // ���㿪ʼʱ��ͽ���ʱ��Ĳ�ֵ
        record->times[record->count].duration = difftime(record->times[record->count].end_time, record->times[record->count].start_time);

        // ���浽�ļ��У��޸�д���ʽ
        FILE *file = fopen(FILE_PATH, "a");
        if (file != NULL)
        {
            const char *window_name = get_window_name(window_char); // ��ȡ��������
            fprintf(file, "%s\t%s\t%s\t����ʱ��: %.2f��\n",
                    record->service_type,
                    window_name,                            // ʹ�ô�����������ַ�
                    queue_number_str,                       // �Ŷӱ��
                    record->times[record->count].duration); // ����ʱ��
            fclose(file);
        }

        record->count++; // ��¼��ҵ�����Ͱ������
    }
}

// ��ӡָ��ҵ�����͡����ں��Ŷӱ�ŵİ���ʱ��
void print_service_times(const char *service_type, char window_char, int queue_number)
{
    ServiceRecord *record = find_service_record(service_type);
    if (record != NULL)
    {
        for (int i = 0; i < record->count; i++)
        {
            // ȷ����ӡ����ָ�����ں��Ŷӱ�ŵļ�¼
            if (record->times[i].window_char == window_char && record->times[i].queue_id == queue_number)
            {
                // ʹ�� strftime ��ʽ��ʱ��Ϊ "ʱ:��:��"
                struct tm *end_tm = localtime(&record->times[i].end_time);
                char end_time_str[9]; // ��ʽ�����ʱ���ַ�����ʱ:��:�룩
                strftime(end_time_str, sizeof(end_time_str), "%H:%M:%S", end_tm);

                const char *window_name = get_window_name(window_char); // ��ȡ��������

                // ��ӡÿ�ΰ����ʱ��ͽ���ʱ�䣨ֻ��ʾʱ���룩
                printf("\n����: %s\t����: %s\t�Ŷӱ��: %s\t����ʱ��: %.2f��\t����ʱ��: %s\n",
                       record->service_type,
                       window_name, // ʹ�ô�����������ַ�
                       record->times[i].queue_number,
                       record->times[i].duration,
                       end_time_str);
            }
        }
    }
}

// ��ӡ����ʱ���¼
void print_all_service_times()
{
    for (int i = 0; i < service_type_count; i++)
    {
        ServiceRecord *record = &service_records[i];
        for (int j = 0; j < record->count; j++)
        {
            // ʹ�� get_window_name ������ȡ��������
            const char *window_name = get_window_name(record->times[j].window_char);

            // ��ӡÿ����¼��ʱ��
            printf("ҵ������: %s\t����: %s\t�Ŷӱ��: %s\t����ʱ��: %.2f��\n",
                   record->service_type,
                   window_name, // �滻Ϊ��������
                   record->times[j].queue_number,
                   record->times[j].duration);
        }
    }
}

// ͳ���ļ��еĲ�ͬҵ�����͵�ƽ������ʱ��
void calculate_average_times_from_file()
{
    FILE *file = fopen(FILE_PATH, "r");
    if (file == NULL)
    {
        printf("�޷����ļ�: %s\n", FILE_PATH);
        return;
    }

    char line[256];
    ServiceRecord service_records[MAX_SERVICES]; // ���ڴ洢����ҵ�����͵ļ�¼
    int service_count = 0;

    // ��ʼ�������¼����
    for (int i = 0; i < MAX_SERVICES; i++)
    {
        service_records[i].count = 0;
    }

    while (fgets(line, sizeof(line), file))
    {
        char service_type[100];
        char queue_number[20];
        int count;
        double duration;

        // �����ļ��е�ÿһ�У���ȡҵ�����͡��Ŷӱ�š������Ͱ���ʱ��
        if (sscanf(line, "%s\t%s\t�������: %d\t����ʱ��: %lf��", service_type, queue_number, &count, &duration) == 4)
        {
            // ����ҵ�������Ƿ��Ѿ�����
            int found = 0;
            for (int i = 0; i < service_count; i++)
            {
                if (strcmp(service_records[i].service_type, service_type) == 0)
                {
                    service_records[i].times[service_records[i].count].duration = duration;
                    service_records[i].count++;
                    found = 1;
                    break;
                }
            }

            // ���û���ҵ���ҵ�����ͣ����½�һ����¼
            if (!found)
            {
                strcpy(service_records[service_count].service_type, service_type);
                service_records[service_count].times[0].duration = duration;
                service_records[service_count].count = 1;
                service_count++;
            }
        }
    }

    // �����������к󣬼��㲢��ӡÿ��ҵ�����͵�ƽ������ʱ��
    for (int i = 0; i < service_count; i++)
    {
        double total_time = 0.0;
        for (int j = 0; j < service_records[i].count; j++)
        {
            total_time += service_records[i].times[j].duration;
        }
        double average_time = total_time / service_records[i].count;
        printf("ҵ������: %s\t�������: %d\tƽ������ʱ��: %.2f��\n",
               service_records[i].service_type, service_records[i].count, average_time);
    }

    fclose(file);
}

#endif
