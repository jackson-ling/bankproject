#ifndef TIME_SERVICE_H
#define TIME_SERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SERVICES 100                                                                    // 假设最多支持100种业务类型
#define FILE_PATH "C:\\Users\\jackson\\Desktop\\bankproject_vscode\\file\\service_time.txt" // 文件路径

// 定义一个结构体来保存每个业务类型的时间信息
typedef struct
{
    time_t start_time; // 记录业务开始的时间
    time_t end_time;   // 记录业务结束的时间
    double duration;   // 记录每次业务办理的持续时间
} ServiceTime;

// 定义一个数组来存储不同业务类型的办理时间信息
typedef struct
{
    char service_type[100];          // 业务类型名称
    ServiceTime times[MAX_SERVICES]; // 对应业务类型的所有办理时间
    int count;                       // 当前业务类型的办理次数
} ServiceRecord;

ServiceRecord service_records[MAX_SERVICES]; // 存储所有业务类型的记录
int service_type_count = 0;                  // 当前支持的业务类型数

// 函数声明部分

// 找到对应的业务类型记录
ServiceRecord *find_service_record(const char *service_type);

// 记录业务的开始时间
void start_service_timer(const char *service_type);

// 记录业务的结束时间并计算持续时间（不打印任何信息）
void stop_service_timer(const char *service_type);

// 打印指定业务类型的办理时间
void print_service_times(const char *service_type);

// 统计文件中的不同业务类型的平均办理时间
void calculate_average_times_from_file();

// 找到对应的业务类型记录
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

// 记录业务的开始时间
void start_service_timer(const char *service_type)
{
    ServiceRecord *record = find_service_record(service_type);
    if (record == NULL)
    {
        // 如果没有找到该业务类型，则创建新的记录
        strcpy(service_records[service_type_count].service_type, service_type);
        record = &service_records[service_type_count];
        record->count = 0;
        service_type_count++;
    }

    // 获取当前时间并记录
    time_t current_time = time(NULL);
    record->times[record->count].start_time = current_time; // 获取当前时间戳

    // 使用 strftime 格式化时间为 "时:分:秒"
    struct tm *start_tm = localtime(&current_time);
    char start_time_str[9]; // 格式化后的时间字符串（时:分:秒）
    strftime(start_time_str, sizeof(start_time_str), "%H:%M:%S", start_tm);

    printf("\n业务类型: %s\t开始时间: %s\t", service_type, start_time_str);
}

// 记录业务的结束时间并计算持续时间（不打印任何信息）
void stop_service_timer(const char *service_type)
{
    ServiceRecord *record = find_service_record(service_type);
    if (record != NULL)
    {
        // 获取当前结束时间
        time_t current_time = time(NULL);
        record->times[record->count].end_time = current_time;

        // 计算开始时间和结束时间的差值
        record->times[record->count].duration = difftime(record->times[record->count].end_time, record->times[record->count].start_time);

        // 保存到文件中
        FILE *file = fopen(FILE_PATH, "a");
        if (file != NULL)
        {
            fprintf(file, "%s\t办理次数: %d\t办理时间: %.2f秒\n", record->service_type, record->count + 1, record->times[record->count].duration);
            fclose(file);
        }

        record->count++; // 记录该业务类型办理次数
    }
}

// 打印指定业务类型的办理时间
void print_service_times(const char *service_type)
{
    ServiceRecord *record = find_service_record(service_type);
    if (record != NULL)
    {
        for (int i = 0; i < record->count; i++)
        {
            // 使用 strftime 格式化时间为 "时:分:秒"
            struct tm *end_tm = localtime(&record->times[i].end_time);
            char end_time_str[9]; // 格式化后的时间字符串（时:分:秒）
            strftime(end_time_str, sizeof(end_time_str), "%H:%M:%S", end_tm);

            // 打印每次办理的时间和结束时间（只显示时分秒）
            printf("\n%s办理结束\t办理时间: %.2f秒\t结束时间: %s\t第 %d 次\n",
                   record->service_type, record->times[i].duration, end_time_str, i + 1);
        }
    }
}

// 统计文件中的不同业务类型的平均办理时间
void calculate_average_times_from_file()
{
    FILE *file = fopen(FILE_PATH, "r");
    if (file == NULL)
    {
        printf("无法打开文件: %s\n", FILE_PATH);
        return;
    }

    char line[256];
    ServiceRecord service_records[MAX_SERVICES]; // 用于存储各个业务类型的记录
    int service_count = 0;

    // 初始化服务记录数组
    for (int i = 0; i < MAX_SERVICES; i++)
    {
        service_records[i].count = 0;
    }

    while (fgets(line, sizeof(line), file))
    {
        char service_type[100];
        int count;
        double duration;

        // 解析文件中的每一行，获取业务类型、次数和办理时间
        if (sscanf(line, "%s\t办理次数: %d\t办理时间: %lf秒", service_type, &count, &duration) == 3)
        {
            // 检查该业务类型是否已经存在
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

            // 如果没有找到该业务类型，则新建一条记录
            if (!found)
            {
                strcpy(service_records[service_count].service_type, service_type);
                service_records[service_count].times[0].duration = duration;
                service_records[service_count].count = 1;
                service_count++;
            }
        }
    }

    // 处理完所有行后，计算并打印每个业务类型的平均办理时间
    for (int i = 0; i < service_count; i++)
    {
        double total_time = 0.0;
        for (int j = 0; j < service_records[i].count; j++)
        {
            total_time += service_records[i].times[j].duration;
        }
        double average_time = total_time / service_records[i].count;
        printf("业务类型: %s\t办理次数: %d\t平均办理时间: %.2f秒\n",
               service_records[i].service_type, service_records[i].count, average_time);
    }

    fclose(file);
}
#endif
