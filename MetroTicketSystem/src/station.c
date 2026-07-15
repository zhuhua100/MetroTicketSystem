/*
 * station.c - 站点管理模块
 * Metro Ticket System
 * 读取站点数据，校验站点合法性，查询站点信息
 */

#include "../include/data.h"

/* 根据ID查找站点 */
int find_station_by_id(int id)
{
    int i;
    for (i = 0; i < station_count; i++)
    {
        if (stations[i].station_id == id)
        {
            return i;
        }
    }
    return -1; /* 未找到 */
}

/* 根据名称查找站点 */
int find_station_by_name(const char *name)
{
    int i;
    for (i = 0; i < station_count; i++)
    {
        if (strcmp(stations[i].station_name, name) == 0)
        {
            return i;
        }
    }
    return -1; /* 未找到 */
}

/* 列出所有站点 */
void list_stations(void)
{
    int i;

    printf("\n");
    printf("========================================\n");
    printf("          站点列表                    \n");
    printf("========================================\n");
    printf("编号  站点名称        线路    换乘\n");
    printf("----------------------------------------\n");

    for (i = 0; i < station_count; i++)
    {
        printf("%-6d %-16s %-6d %s\n",
               stations[i].station_id,
               stations[i].station_name,
               stations[i].line_id,
               stations[i].is_transfer ? "Yes" : "No");
    }
    printf("========================================\n");
}
