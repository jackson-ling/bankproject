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
    time_t start_time; // ��¼ҵ��ʼ��ʱ��
    time_t end_time;   // ��¼ҵ�������ʱ��
    double duration;   // ��¼ÿ��ҵ�����ĳ���ʱ��
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
void start_service_timer(const char *service_type);

// ��¼ҵ��Ľ���ʱ�䲢�������ʱ�䣨����ӡ�κ���Ϣ��
void stop_service_timer(const char *service_type);

// ��ӡָ��ҵ�����͵İ���ʱ��
void print_service_times(const char *service_type);

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

// ��¼ҵ��Ŀ�ʼʱ��
void start_service_timer(const char *service_type)
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

    // ��ȡ��ǰʱ�䲢��¼
    time_t current_time = time(NULL);
    record->times[record->count].start_time = current_time; // ��ȡ��ǰʱ���

    // ʹ�� strftime ��ʽ��ʱ��Ϊ "ʱ:��:��"
    struct tm *start_tm = localtime(&current_time);
    char start_time_str[9]; // ��ʽ�����ʱ���ַ�����ʱ:��:�룩
    strftime(start_time_str, sizeof(start_time_str), "%H:%M:%S", start_tm);

    printf("\nҵ������: %s\t��ʼʱ��: %s\t", service_type, start_time_str);
}

// ��¼ҵ��Ľ���ʱ�䲢�������ʱ�䣨����ӡ�κ���Ϣ��
void stop_service_timer(const char *service_type)
{
    ServiceRecord *record = find_service_record(service_type);
    if (record != NULL)
    {
        // ��ȡ��ǰ����ʱ��
        time_t current_time = time(NULL);
        record->times[record->count].end_time = current_time;

        // ���㿪ʼʱ��ͽ���ʱ��Ĳ�ֵ
        record->times[record->count].duration = difftime(record->times[record->count].end_time, record->times[record->count].start_time);

        // ���浽�ļ���
        FILE *file = fopen(FILE_PATH, "a");
        if (file != NULL)
        {
            fprintf(file, "%s\t�������: %d\t����ʱ��: %.2f��\n", record->service_type, record->count + 1, record->times[record->count].duration);
            fclose(file);
        }

        record->count++; // ��¼��ҵ�����Ͱ������
    }
}

// ��ӡָ��ҵ�����͵İ���ʱ��
void print_service_times(const char *service_type)
{
    ServiceRecord *record = find_service_record(service_type);
    if (record != NULL)
    {
        for (int i = 0; i < record->count; i++)
        {
            // ʹ�� strftime ��ʽ��ʱ��Ϊ "ʱ:��:��"
            struct tm *end_tm = localtime(&record->times[i].end_time);
            char end_time_str[9]; // ��ʽ�����ʱ���ַ�����ʱ:��:�룩
            strftime(end_time_str, sizeof(end_time_str), "%H:%M:%S", end_tm);

            // ��ӡÿ�ΰ����ʱ��ͽ���ʱ�䣨ֻ��ʾʱ���룩
            printf("\n%s�������\t����ʱ��: %.2f��\t����ʱ��: %s\t�� %d ��\n",
                   record->service_type, record->times[i].duration, end_time_str, i + 1);
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
        int count;
        double duration;

        // �����ļ��е�ÿһ�У���ȡҵ�����͡������Ͱ���ʱ��
        if (sscanf(line, "%s\t�������: %d\t����ʱ��: %lf��", service_type, &count, &duration) == 3)
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
