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
    time_t start_time;     // 记录业务开始的时间
    time_t end_time;       // 记录业务结束的时间
    double duration;       // 记录每次业务办理的持续时间
    char queue_number[20]; // 排队编号（包含窗口字符和排队编号）
    char window_char;      // 窗口字符
    int queue_id;          // 排队编号
} ServiceTime;

// 定义一个数组来存储不同业务类型的办理时间信息
typedef struct
{
    char service_type[100];          // 业务类型名称
    ServiceTime times[MAX_SERVICES]; // 对应业务类型的所有办理时间
    int count;                       // 当前业务类型的办理次数
    char window_name[100];           // 新增窗口名称字段
} ServiceRecord;

ServiceRecord service_records[MAX_SERVICES]; // 存储所有业务类型的记录
int service_type_count = 0;                  // 当前支持的业务类型数

// 函数声明部分

// 找到对应的业务类型记录
ServiceRecord *find_service_record(const char *service_type);

// 记录业务的开始时间
void start_service_timer(const char *service_type, char window_char, int queue_number);

// 记录业务的结束时间并计算持续时间（不打印任何信息）
void stop_service_timer(const char *service_type, char window_char, int queue_number);

// 打印指定业务类型、窗口和排队编号的办理时间
void print_service_times(const char *service_type, char window_char, int queue_number);

// 打印所有时间记录
void print_all_service_times();

// 统计文件中的不同业务类型的平均办理时间
void calculate_average_times_service();

void calculate_average_times_window();

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

// 根据窗口字符返回对应的窗口名称
const char *get_window_name(char window_char)
{
    // 定义包含窗口名称的字符串数组
    const char *window_names[] = {
        "窗口一", "窗口二", "窗口三", "窗口四", "窗口五",
        "窗口六", "窗口七", "窗口八", "窗口九", "窗口十"};

    // 根据传入的 window_char 返回对应的窗口名称
    if (window_char >= 'a' && window_char <= 'j')
    {
        return window_names[window_char - 'a']; // 'a' -> "窗口一", 'b' -> "窗口二", ...
    }
    return "未知窗口"; // 如果字符不在有效范围内，返回未知窗口
}

// 记录业务的开始时间
void start_service_timer(const char *service_type, char window_char, int queue_number)
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

    // 组合排队编号
    char queue_number_str[20];
    sprintf(queue_number_str, "%c%d", window_char, queue_number); // 格式化为 "窗口字符+排队编号"

    // 获取当前时间并记录
    time_t current_time = time(NULL);

    // 确保不覆盖已有的记录，使用 queue_number 确定唯一计时器
    for (int i = 0; i < record->count; i++)
    {
        if (strcmp(record->times[i].queue_number, queue_number_str) == 0)
        {
            // 如果该编号已经存在，则返回
            return;
        }
    }

    // 将新的计时器记录到结构体中
    strcpy(record->times[record->count].queue_number, queue_number_str);
    record->times[record->count].window_char = window_char;
    record->times[record->count].queue_id = queue_number;
    record->times[record->count].start_time = current_time;

    // 使用 strftime 格式化时间为 "时:分:秒"
    struct tm *start_tm = localtime(&current_time);
    char start_time_str[9]; // 格式化后的时间字符串（时:分:秒）
    strftime(start_time_str, sizeof(start_time_str), "%H:%M:%S", start_tm);

    printf("    类型: %s\t开始时间: %s\n", service_type, start_time_str);
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    record->count++; // 增加计时器记录数
}

// 记录业务的结束时间并计算持续时间（不打印任何信息）
void stop_service_timer(const char *service_type, char window_char, int queue_number)
{
    ServiceRecord *record = find_service_record(service_type);
    if (record != NULL)
    {
        // 组合排队编号
        char queue_number_str[20];
        sprintf(queue_number_str, "%c%d", window_char, queue_number); // 格式化为 "窗口字符+排队编号"

        // 查找对应的排队编号的计时器
        for (int i = 0; i < record->count; i++)
        {
            if (strcmp(record->times[i].queue_number, queue_number_str) == 0)
            {
                // 找到该排队编号的计时器
                time_t current_time = time(NULL);
                record->times[i].end_time = current_time;

                // 计算开始时间和结束时间的差值
                record->times[i].duration = difftime(record->times[i].end_time, record->times[i].start_time);

                // 保存到文件中，修改写入格式
                FILE *file = fopen(FILE_PATH, "a");
                if (file != NULL)
                {
                    const char *window_name = get_window_name(window_char); // 获取窗口名称
                    fprintf(file, "%s\t%s\t%s\t办理时间: %.2f秒\n",
                            record->service_type,
                            window_name,                // 使用窗口名称替代字符
                            queue_number_str,           // 排队编号
                            record->times[i].duration); // 办理时间
                    fclose(file);
                }

                return; // 成功处理后退出
            }
        }

        // 如果没有找到该排队编号，打印错误信息
        printf("未找到对应的排队编号: %s\n", queue_number_str);
    }
}

// 打印指定业务类型、窗口和排队编号的办理时间
void print_service_times(const char *service_type, char window_char, int queue_number)
{
    ServiceRecord *record = find_service_record(service_type);
    if (record != NULL)
    {
        for (int i = 0; i < record->count; i++)
        {
            // 确保打印的是指定窗口和排队编号的记录
            if (record->times[i].window_char == window_char && record->times[i].queue_id == queue_number)
            {
                // 使用 strftime 格式化时间为 "时:分:秒"
                struct tm *end_tm = localtime(&record->times[i].end_time);
                char end_time_str[9]; // 格式化后的时间字符串（时:分:秒）
                strftime(end_time_str, sizeof(end_time_str), "%H:%M:%S", end_tm);

                const char *window_name = get_window_name(window_char); // 获取窗口名称

                // 打印每次办理的时间和结束时间（只显示时分秒）
                printf("\n类型: %s\t窗口: %s\t排队编号: %s\t办理时间: %.2f秒\t结束时间: %s\n",
                       record->service_type,
                       window_name, // 使用窗口名称替代字符
                       record->times[i].queue_number,
                       record->times[i].duration,
                       end_time_str);
                printf("------------------------------------------------------------------------------------------------------------------------\n");
            }
        }
    }
}

// 打印所有时间记录
void print_all_service_times()
{
    for (int i = 0; i < service_type_count; i++)
    {
        ServiceRecord *record = &service_records[i];
        for (int j = 0; j < record->count; j++)
        {
            // 使用 get_window_name 函数获取窗口名称
            const char *window_name = get_window_name(record->times[j].window_char);

            // 打印每个记录的时间
            printf("业务类型: %s\t窗口: %s\t排队编号: %s\t办理时间: %.2f秒\n",
                   record->service_type,
                   window_name, // 替换为窗口名称
                   record->times[j].queue_number,
                   record->times[j].duration);
        }
    }
}

// 统计文件中的不同业务类型的平均办理时间
void calculate_average_times_service()
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

    // 逐行读取文件并解析内容
    while (fgets(line, sizeof(line), file))
    {
        char service_type[100];
        char window_name[20];
        char queue_number[20];
        double duration;

        // 解析每一行数据
        if (sscanf(line, "%s\t%s\t%s\t办理时间: %lf秒", service_type, window_name, queue_number, &duration) == 4)
        {
            // 查找是否已经存在该业务类型
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

            // 如果该业务类型不存在，创建新记录
            if (!found)
            {
                strcpy(service_records[service_count].service_type, service_type);
                service_records[service_count].times[0].duration = duration;
                service_records[service_count].count = 1;
                service_count++;
            }
        }
    }

    // 计算每个业务类型的平均办理时间
    double average_times[MAX_SERVICES];
    for (int i = 0; i < service_count; i++)
    {
        double total_time = 0.0;
        for (int j = 0; j < service_records[i].count; j++)
        {
            total_time += service_records[i].times[j].duration;
        }
        average_times[i] = total_time / service_records[i].count;
    }

    // 按平均办理时间从小到大排序
    for (int i = 0; i < service_count - 1; i++)
    {
        for (int j = i + 1; j < service_count; j++)
        {
            if (average_times[i] > average_times[j])
            {
                // 交换平均办理时间
                double temp = average_times[i];
                average_times[i] = average_times[j];
                average_times[j] = temp;

                // 交换对应的业务类型记录
                ServiceRecord temp_record = service_records[i];
                service_records[i] = service_records[j];
                service_records[j] = temp_record;
            }
        }
    }

    // 打印按平均办理时间排序后的业务类型
    for (int i = 0; i < service_count; i++)
    {
        printf("%s，平均排队时间：%.2f秒，平均办理时间：%.2f秒\n", service_records[i].service_type, average_times[i] * 1.5, average_times[i]);
    }

    fclose(file);
}

void calculate_average_times_window()
{
    FILE *file = fopen(FILE_PATH, "r");
    if (file == NULL)
    {
        printf("无法打开文件: %s\n", FILE_PATH);
        return;
    }

    char line[256];
    ServiceRecord window_records[MAX_SERVICES]; // 用于存储每个窗口的记录
    int window_count = 0;

    // 初始化窗口记录数组
    for (int i = 0; i < MAX_SERVICES; i++)
    {
        window_records[i].count = 0;
    }

    // 逐行读取文件并解析内容
    while (fgets(line, sizeof(line), file))
    {
        char service_type[100];
        char window_name[20];
        char queue_number[20];
        double duration;

        // 解析每一行数据
        if (sscanf(line, "%s\t%s\t%s\t办理时间: %lf秒", service_type, window_name, queue_number, &duration) == 4)
        {
            // 查找是否已经存在该窗口
            int found = 0;
            for (int i = 0; i < window_count; i++)
            {
                if (strcmp(window_records[i].window_name, window_name) == 0)
                {
                    window_records[i].times[window_records[i].count].duration = duration;
                    window_records[i].count++;
                    found = 1;
                    break;
                }
            }

            // 如果该窗口不存在，创建新记录
            if (!found)
            {
                strcpy(window_records[window_count].window_name, window_name);
                window_records[window_count].times[0].duration = duration;
                window_records[window_count].count = 1;
                window_count++;
            }
        }
    }

    // 计算每个窗口的平均办理时间
    double average_times[MAX_SERVICES];
    for (int i = 0; i < window_count; i++)
    {
        double total_time = 0.0;
        for (int j = 0; j < window_records[i].count; j++)
        {
            total_time += window_records[i].times[j].duration;
        }
        average_times[i] = total_time / window_records[i].count;
    }

    // 按平均办理时间从小到大排序
    for (int i = 0; i < window_count - 1; i++)
    {
        for (int j = i + 1; j < window_count; j++)
        {
            if (average_times[i] > average_times[j])
            {
                // 交换平均办理时间
                double temp = average_times[i];
                average_times[i] = average_times[j];
                average_times[j] = temp;

                // 交换对应的窗口记录
                ServiceRecord temp_record = window_records[i];
                window_records[i] = window_records[j];
                window_records[j] = temp_record;
            }
        }
    }

    // 打印按窗口排序后的平均办理时间
    for (int i = 0; i < window_count; i++)
    {
        printf("%s, 平均排队时间：%.2f秒，平均办理时间: %.2f秒\n", window_records[i].window_name, average_times[i] * 1.5, average_times[i]);
    }

    fclose(file);
}

#endif
