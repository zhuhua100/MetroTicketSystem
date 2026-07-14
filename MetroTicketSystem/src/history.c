/*
 * history.c - 历史记录模块
 * Metro Ticket System
 * 加载本地订单数据，展示所有购票订单信息，支持删除操作
 */

#include "../include/data.h"

void show_history(void)
{
    int choice;
    int del_id;

    while (1)
    {
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

            for (int i = 0; i < order_count; i++)
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
        printf("  1. 删除某条记录\n");
        printf("  2. 删除全部记录\n");
        printf("  3. 返回主菜单\n");
        printf("----------------------------------------\n");
        printf("  请选择操作: ");
        choice = get_valid_int(1, 3);

        switch (choice)
        {
        case 1:
            if (order_count == 0)
            {
                printf("  暂无记录可删除。\n");
                printf("  按 Enter 键继续...\n");
                clear_input_buffer();
                getchar();
            }
            else
            {
                printf("  请输入要删除的订单编号: ");
                del_id = get_valid_int(1, 999999);
                delete_order_by_id(del_id);
                printf("  按 Enter 键继续...\n");
                clear_input_buffer();
                getchar();
            }
            break;

        case 2:
            if (order_count == 0)
            {
                printf("  暂无记录可删除。\n");
                printf("  按 Enter 键继续...\n");
                clear_input_buffer();
                getchar();
            }
            else
            {
                printf("  确定要删除所有记录吗？(y/n): ");
                char confirm = getchar();
                clear_input_buffer();
                if (confirm == 'y' || confirm == 'Y')
                {
                    delete_all_orders();
                }
                else
                {
                    printf("  已取消删除操作。\n");
                }
                printf("  按 Enter 键继续...\n");
                getchar();
            }
            break;

        case 3:
            return;
        }
    }
}
