/*
 * map.c - 地图查询模块
 * Metro Ticket System
 * 可视化展示地铁线路图，支持按线路查询站点
 */

#include "../include/data.h"

/* 线路颜色（控制台颜色代码） */
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_CYAN "\033[36m"

/* 获取线路颜色 */
static const char *get_line_color(int line_id)
{
    switch (line_id)
    {
    case 1:
        return COLOR_GREEN; /* 1号线 - 绿色 */
    case 2:
        return COLOR_RED; /* 2号线 - 红色 */
    case 3:
        return COLOR_YELLOW; /* 3号线 - 黄色 */
    case 4:
        return COLOR_BLUE; /* 4号线 - 蓝色 */
    default:
        return COLOR_CYAN;
    }
}

/* 显示所有线路概览 */
static void show_line_overview(void)
{
    printf("\n");
    printf("========================================\n");
    printf("          线路概览                    \n");
    printf("========================================\n");

    for (int i = 0; i < line_count; i++)
    {
        printf("  %s%s%s  共%d站\n",
               get_line_color(lines[i].line_id),
               lines[i].line_name,
               COLOR_RESET,
               lines[i].station_count);
    }
    printf("========================================\n");
}

/* 显示指定线路的站点详情 */
static void show_line_detail(int line_id)
{
    /* 查找线路名称 */
    char *line_name = "未知线路";
    for (int i = 0; i < line_count; i++)
    {
        if (lines[i].line_id == line_id)
        {
            line_name = lines[i].line_name;
            break;
        }
    }

    printf("\n");
    printf("----------------------------------------\n");
    printf("  %s%s%s\n", get_line_color(line_id), line_name, COLOR_RESET);
    printf("----------------------------------------\n");

    /* 收集该线路的站点 */
    int line_stations[MAX_STATIONS];
    int count = 0;

    for (int i = 0; i < station_count; i++)
    {
        if (stations[i].line_id == line_id)
        {
            line_stations[count++] = i;
        }
    }

    /* 按站点编号排序 */
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (stations[line_stations[j]].station_id >
                stations[line_stations[j + 1]].station_id)
            {
                int temp = line_stations[j];
                line_stations[j] = line_stations[j + 1];
                line_stations[j + 1] = temp;
            }
        }
    }

    /* 绘制线路图 */
    for (int i = 0; i < count; i++)
    {
        int idx = line_stations[i];

        /* 线路连接线 */
        if (i > 0)
        {
            printf("  %s---%s", get_line_color(line_id), COLOR_RESET);
        }
        else
        {
            printf("  ");
        }

        /* 站点标记 */
        if (stations[idx].is_transfer)
        {
            printf("%s[%s]%s", get_line_color(line_id),
                   stations[idx].station_name, COLOR_RESET);
        }
        else
        {
            printf("%s●%s%s", get_line_color(line_id),
                   stations[idx].station_name, COLOR_RESET);
        }

        /* 站点信息 */
        printf(" (ID:%d)", stations[idx].station_id);

        if (stations[idx].is_transfer)
        {
            printf(" [换乘站]");
        }
        printf("\n");
    }

    printf("----------------------------------------\n");
}

/* 显示所有线路的完整地图 */
static void show_full_map(void)
{
    printf("\n");
    printf("========================================\n");
    printf("          完整地铁线路图                \n");
    printf("========================================\n");
    printf("  ● 普通站    [站名] 换乘站\n");
    printf("========================================\n");

    for (int i = 0; i < line_count; i++)
    {
        show_line_detail(lines[i].line_id);
    }
}

/* 按站点名称查询 */
static void search_station_by_name(void)
{
    char name[20];
    int found = 0;

    printf("\n");
    printf("----------------------------------------\n");
    printf("  请输入站点名称: ");
    scanf("%19s", name);
    clear_input_buffer();

    printf("\n  查询结果:\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < station_count; i++)
    {
        if (strstr(stations[i].station_name, name) != NULL)
        {
            /* 查找所属线路名称 */
            char *line_name = "未知";
            for (int j = 0; j < line_count; j++)
            {
                if (lines[j].line_id == stations[i].line_id)
                {
                    line_name = lines[j].line_name;
                    break;
                }
            }

            printf("  %s(ID:%d) - %s%s",
                   stations[i].station_name,
                   stations[i].station_id,
                   line_name,
                   stations[i].is_transfer ? " [换乘站]" : "");
            printf("\n");
            found = 1;
        }
    }

    if (!found)
    {
        printf("  未找到匹配的站点。\n");
    }
    printf("----------------------------------------\n");
}

/* 地图查询主函数 */
void show_map(void)
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("========================================\n");
        printf("          地铁地图查询                  \n");
        printf("========================================\n");
        printf("                                    \n");
        printf("    1. 线路概览                      \n");
        printf("    2. 查看线路详情                  \n");
        printf("    3. 完整地铁线路图                \n");
        printf("    4. 按名称查询站点                \n");
        printf("    5. 返回主菜单                    \n");
        printf("                                    \n");
        printf("========================================\n");
        printf("请选择(1-5): ");

        choice = get_valid_int(1, 5);

        switch (choice)
        {
        case 1:
            show_line_overview();
            break;

        case 2:
        {
            int line_id;
            printf("请输入线路编号(1-%d): ", line_count);
            line_id = get_valid_int(1, line_count);
            show_line_detail(line_id);
            break;
        }

        case 3:
            show_full_map();
            break;

        case 4:
            search_station_by_name();
            break;

        case 5:
            return;

        default:
            printf("无效选择，请重新输入！\n");
            break;
        }

        if (choice >= 1 && choice <= 4)
        {
            printf("\n  按 Enter 键继续...\n");
            getchar();
        }
    }
}
