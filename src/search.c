/*
 * search.c - 复杂查询模块
 * Metro Ticket System
 * 支持线路、站点、票价、是否换乘四条件组合查询
 */

#include "../include/data.h"

/* 复杂查询菜单 */
void search_menu(void)
{
    int choice;
    int line_id, price_filter;
    int i, found;
    char name_filter[20];

    printf("\n");
    printf("========================================\n");
    printf("          条件查询                    \n");
    printf("========================================\n");
    printf("  1. 按线路查询站点\n");
    printf("  2. 按名称查询站点\n");
    printf("  3. 按票价查询订单\n");
    printf("  4. 查询换乘站\n");
    printf("  5. 组合查询\n");
    printf("  6. 返回主菜单\n");
    printf("========================================\n");
    printf("请选择(1-6): ");

    choice = get_valid_int(1, 6);

    switch (choice)
    {
    case 1:
        /* 按线路查询 */
        printf("请输入线路编号(1-%d): ", line_count > 0 ? line_count : 3);
        line_id = get_valid_int(1, line_count > 0 ? line_count : 3);

        printf("\n线路%d 的站点:\n", line_id);
        found = 0;
        for (i = 0; i < station_count; i++)
        {
            if (stations[i].line_id == line_id)
            {
                printf("  [%d] %s", stations[i].station_id, stations[i].station_name);
                if (stations[i].is_transfer)
                    printf(" (换乘站)");
                printf("\n");
                found = 1;
            }
        }
        if (!found)
            printf("  该线路暂无站点数据。\n");
        break;

    case 2:
        /* 按名称查询 */
        printf("请输入站点名称: ");
        clear_input_buffer();
        fgets(name_filter, sizeof(name_filter), stdin);
        name_filter[strcspn(name_filter, "\n")] = '\0';

        found = 0;
        for (i = 0; i < station_count; i++)
        {
            if (strstr(stations[i].station_name, name_filter) != NULL)
            {
                printf("  [%d] %s (线路%d)%s\n",
                       stations[i].station_id,
                       stations[i].station_name,
                       stations[i].line_id,
                       stations[i].is_transfer ? " [换乘站]" : "");
                found = 1;
            }
        }
        if (!found)
            printf("  未找到匹配的站点。\n");
        break;

    case 3:
        /* 按票价查询订单 */
        printf("请输入最低票价: ");
        price_filter = get_valid_int(0, 100);

        printf("\n票价 >= %d 元的订单:\n", price_filter);
        found = 0;
        for (i = 0; i < order_count; i++)
        {
            if (orders[i].price >= price_filter)
            {
                printf("  订单%d: %s 起点%d->终点%d 单价%d元 数量%d\n",
                       orders[i].order_id, orders[i].time,
                       orders[i].start_id, orders[i].end_id,
                       orders[i].price, orders[i].num);
                found = 1;
            }
        }
        if (!found)
            printf("  未找到匹配的订单。\n");
        break;

    case 4:
        /* 查询换乘站 */
        printf("\n换乘站列表:\n");
        found = 0;
        for (i = 0; i < station_count; i++)
        {
            if (stations[i].is_transfer)
            {
                printf("  [%d] %s (线路%d)\n",
                       stations[i].station_id,
                       stations[i].station_name,
                       stations[i].line_id);
                found = 1;
            }
        }
        if (!found)
            printf("  暂无换乘站数据。\n");
        break;

    case 5:
        /* 组合查询 */
        printf("\n【组合查询】\n");
        printf("请输入线路编号(0=不限): ");
        line_id = get_valid_int(0, line_count > 0 ? line_count : 3);

        printf("是否仅查询换乘站(0=不限, 1=仅换乘站): ");
        int transfer_only = get_valid_int(0, 1);

        printf("\n查询结果:\n");
        found = 0;
        for (i = 0; i < station_count; i++)
        {
            int match = 1;
            if (line_id > 0 && stations[i].line_id != line_id)
                match = 0;
            if (transfer_only && !stations[i].is_transfer)
                match = 0;

            if (match)
            {
                printf("  [%d] %s (线路%d)%s\n",
                       stations[i].station_id,
                       stations[i].station_name,
                       stations[i].line_id,
                       stations[i].is_transfer ? " [换乘站]" : "");
                found = 1;
            }
        }
        if (!found)
            printf("  未找到匹配的站点。\n");
        break;

    case 6:
        return;

    default:
        break;
    }

    printf("\n========================================\n");
    printf("按 Enter 键返回查询菜单...\n");
    clear_input_buffer();
    getchar();
    search_menu(); /* 递归返回查询菜单 */
}
