/*
 * history.c - 历史记录模块
 * Metro Ticket System
 * 加载本地订单数据，展示所有购票订单信息
 */

#include "../include/data.h"

void show_history(void)
{
    int i;

    printf("\n");
    printf("========================================\n");
    printf("          购票历史记录                \n");
    printf("========================================\n");

    if (order_count == 0)
    {
        printf("  暂无购票记录。\n");
    }
    else
    {
        printf("编号  时间                    起点  终点  单价  数量  总价  找零\n");
        printf("----------------------------------------------------------------\n");

        for (i = 0; i < order_count; i++)
        {
            printf("%-6d %-24s %-5d %-5d %-4d %-4d %-4d %-4d\n",
                   orders[i].order_id,
                   orders[i].time,
                   orders[i].start_id,
                   orders[i].end_id,
                   orders[i].price,
                   orders[i].num,
                   orders[i].total_money,
                   orders[i].change);
        }
    }

    printf("========================================\n");
    printf("按 Enter 键返回主菜单...\n");
    clear_input_buffer();
    getchar();
}
