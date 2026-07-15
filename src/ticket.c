/*
 * ticket.c - 购票模块
 * Metro Ticket System
 * 选择起终点、购票数量，校验站点合法、票数合法
 */

#include "../include/data.h"

/* 购票主流程 */
void buy_ticket(void)
{
    int start_id, end_id;
    int start_idx, end_idx;
    int price, num, total;
    int change;
    Order order;
    char confirm;
    static int order_id_counter = 1;

    printf("\n");
    printf("========================================\n");
    printf("          购票服务                    \n");
    printf("========================================\n");

    /* 显示站点列表 */
    list_stations();

    /* 选择起点站 */
    printf("\n请选择起点站(输入站点编号): ");
    start_id = get_valid_int(1, station_count);
    start_idx = find_station_by_id(start_id);

    /* Bug3: 站点不存在检查 */
    if (start_idx == -1)
    {
        printf("【错误】站点不存在！\n");
        printf("按 Enter 键返回主菜单...\n");
        clear_input_buffer();
        getchar();
        return;
    }

    /* 选择终点站 */
    printf("请选择终点站(输入站点编号): ");
    end_id = get_valid_int(1, station_count);
    end_idx = find_station_by_id(end_id);

    if (end_idx == -1)
    {
        printf("【错误】站点不存在！\n");
        printf("按 Enter 键返回主菜单...\n");
        clear_input_buffer();
        getchar();
        return;
    }

    /* 检查起止站点是否相同 */
    if (start_id == end_id)
    {
        printf("【错误】起点站和终点站不能相同！\n");
        printf("按 Enter 键返回主菜单...\n");
        clear_input_buffer();
        getchar();
        return;
    }

    /* 计算票价 */
    price = calculate_price(start_id, end_id);
    if (price < 0)
    {
        printf("【错误】票价计算失败！\n");
        return;
    }

    printf("\n  起点: %s\n", stations[start_idx].station_name);
    printf("  终点: %s\n", stations[end_idx].station_name);
    printf("  单价: %d 元\n", price);

    /* 选择购票数量 */
    printf("\n请选择购票数量(1-10): ");
    num = get_valid_int(1, 10);

    /* 断言：购票数量大于0 */
    assert(num > 0);

    total = price * num;
    printf("  总价: %d 元\n", total);

    /* Bug5: 重复购票检查 - 检查当天是否有相同路线的订单 */
    {
        int i;
        char today[11] = {0};
        char order_day[11] = {0};
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        strftime(today, sizeof(today), "%Y-%m-%d", tm_info);

        for (i = 0; i < order_count; i++)
        {
            /* 提取订单日期的年月日部分 */
            strncpy(order_day, orders[i].time, 10);
            order_day[10] = '\0';

            if (orders[i].start_id == start_id &&
                orders[i].end_id == end_id &&
                strcmp(order_day, today) == 0)
            {
                printf("\n  【提示】您今天已购买过相同路线的车票！\n");
                printf("  是否继续购买？(y/n): ");
                clear_input_buffer();
                confirm = getchar();
                if (confirm != 'y' && confirm != 'Y')
                {
                    printf("购票已取消。\n");
                    return;
                }
                break;
            }
        }
    }

    /* 确认购票 */
    printf("\n是否确认购票？(y/n): ");
    clear_input_buffer();
    confirm = getchar();
    if (confirm != 'y' && confirm != 'Y')
    {
        printf("购票已取消。\n");
        return;
    }

    /* 处理支付 */
    change = process_payment(total);

    /* 生成订单 */
    order.order_id = order_id_counter++;
    get_current_time(order.time);
    order.start_id = start_id;
    order.end_id = end_id;
    order.price = price;
    order.num = num;
    order.total_money = total;
    order.change = change;

    /* 保存订单 */
    if (save_order_to_file(&order) == 0)
    {
        orders[order_count] = order;
        order_count++;
        printf("\n  ★ 购票成功！★\n");
        printf("  订单编号: %d\n", order.order_id);
        printf("  请取走您的 %d 张车票\n", num);
    }
    else
    {
        printf("\n  【错误】订单保存失败！\n");
    }

    printf("\n========================================\n");
    printf("按 Enter 键返回主菜单...\n");
    clear_input_buffer();
    getchar();
}
