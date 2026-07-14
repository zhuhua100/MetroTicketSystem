/*
 * file.c - 文件管理模块
 * Metro Ticket System
 * 实现TXT文本、BIN二进制双格式保存、读取、初始化数据
 */

#include "../include/data.h"

/* 初始化数据文件 */
int init_data_files(void)
{
    FILE *fp;
    int need_init = 0;

    /* 检查station.txt */
    fp = fopen("data/station.txt", "r");
    if (fp == NULL)
    {
        need_init = 1;
    }
    else
    {
        fclose(fp);
    }

    /* 检查line.txt */
    fp = fopen("data/line.txt", "r");
    if (fp == NULL)
    {
        need_init = 1;
    }
    else
    {
        fclose(fp);
    }

    if (need_init)
    {
        printf("检测到数据文件缺失，正在初始化...\n");

        /* 创建station.txt - 深圳地铁数据 */
        fp = fopen("data/station.txt", "w");
        if (fp == NULL)
            return -1;
        fprintf(fp, "1,罗湖,1,0\n");
        fprintf(fp, "2,老街,1,1\n");
        fprintf(fp, "3,大剧院,1,1\n");
        fprintf(fp, "4,会展中心,1,1\n");
        fprintf(fp, "5,车公庙,1,1\n");
        fprintf(fp, "6,世界之窗,1,1\n");
        fprintf(fp, "7,赤湾,2,0\n");
        fprintf(fp, "8,市民中心,2,0\n");
        fprintf(fp, "9,新秀,2,0\n");
        fprintf(fp, "10,双龙,3,0\n");
        fprintf(fp, "11,布吉,3,0\n");
        fprintf(fp, "12,福田,3,0\n");
        fprintf(fp, "13,少年宫,3,1\n");
        fprintf(fp, "14,福田口岸,4,0\n");
        fprintf(fp, "15,清湖,4,0\n");
        fclose(fp);

        /* 创建line.txt */
        fp = fopen("data/line.txt", "w");
        if (fp == NULL)
            return -1;
        fprintf(fp, "1,1号线(罗宝线),6\n");
        fprintf(fp, "2,2号线(蛇口线),5\n");
        fprintf(fp, "3,3号线(龙岗线),5\n");
        fprintf(fp, "4,4号线(龙华线),4\n");
        fclose(fp);

        printf("数据文件初始化完成！\n");
    }

    return 0;
}

/* 加载站点数据 */
int load_stations(void)
{
    FILE *fp;
    station_count = 0;

    fp = fopen("data/station.txt", "r");
    if (fp == NULL)
    {
        printf("错误：无法打开站点数据文件！\n");
        return -1;
    }

    while (fscanf(fp, "%d,%[^,],%d,%d",
                  &stations[station_count].station_id,
                  stations[station_count].station_name,
                  &stations[station_count].line_id,
                  &stations[station_count].is_transfer) == 4)
    {
        station_count++;
        if (station_count >= MAX_STATIONS)
            break;
    }

    fclose(fp);
    return 0;
}

/* 加载所有数据 */
int load_data(void)
{
    if (load_stations() != 0)
        return -1;

    load_orders();

    return 0;
}

/* 保存订单到TXT文件 */
int save_order_to_txt(const Order *order)
{
    FILE *fp;

    fp = fopen("data/order.txt", "a");
    if (fp == NULL)
    {
        printf("错误：无法打开订单文件！\n");
        return -1;
    }

    fprintf(fp, "%d,%s,%d,%d,%d,%d,%d,%d\n",
            order->order_id, order->time,
            order->start_id, order->end_id,
            order->price, order->num,
            order->total_money, order->change);

    fclose(fp);
    return 0;
}

/* 保存订单到BIN文件 */
int save_order_to_bin(const Order *order)
{
    FILE *fp;

    fp = fopen("data/order.dat", "ab");
    if (fp == NULL)
    {
        printf("错误：无法打开二进制订单文件！\n");
        return -1;
    }

    fwrite(order, sizeof(Order), 1, fp);

    fclose(fp);
    return 0;
}

/* 保存订单（同时保存TXT和BIN） */
int save_order_to_file(const Order *order)
{
    if (save_order_to_txt(order) != 0)
        return -1;
    if (save_order_to_bin(order) != 0)
        return -1;
    return 0;
}

/* 从TXT加载订单 */
int load_orders_from_txt(void)
{
    FILE *fp;
    order_count = 0;

    fp = fopen("data/order.txt", "r");
    if (fp == NULL)
    {
        /* 文件不存在不是错误 */
        return 0;
    }

    while (fscanf(fp, "%d,%[^,],%d,%d,%d,%d,%d,%d",
                  &orders[order_count].order_id,
                  orders[order_count].time,
                  &orders[order_count].start_id,
                  &orders[order_count].end_id,
                  &orders[order_count].price,
                  &orders[order_count].num,
                  &orders[order_count].total_money,
                  &orders[order_count].change) == 8)
    {
        order_count++;
        if (order_count >= MAX_ORDERS)
            break;
    }

    fclose(fp);
    return 0;
}

/* 从BIN加载订单 */
int load_orders_from_bin(void)
{
    FILE *fp;
    Order temp;
    int count = 0;

    fp = fopen("data/order.dat", "rb");
    if (fp == NULL)
    {
        return 0;
    }

    while (fread(&temp, sizeof(Order), 1, fp) == 1)
    {
        if (count < MAX_ORDERS)
        {
            orders[count] = temp;
            count++;
        }
    }

    order_count = count;
    fclose(fp);
    return 0;
}

/* 将所有订单重新写入文件（覆盖写入） */
int save_all_orders(void)
{
    FILE *fp;
    int i;

    /* 重写TXT文件 */
    fp = fopen("data/order.txt", "w");
    if (fp == NULL)
    {
        printf("错误：无法打开订单文件！\n");
        return -1;
    }

    for (i = 0; i < order_count; i++)
    {
        fprintf(fp, "%d,%s,%d,%d,%d,%d,%d,%d\n",
                orders[i].order_id, orders[i].time,
                orders[i].start_id, orders[i].end_id,
                orders[i].price, orders[i].num,
                orders[i].total_money, orders[i].change);
    }
    fclose(fp);

    /* 重写BIN文件 */
    fp = fopen("data/order.dat", "wb");
    if (fp == NULL)
    {
        printf("错误：无法打开二进制订单文件！\n");
        return -1;
    }

    fwrite(orders, sizeof(Order), order_count, fp);
    fclose(fp);

    return 0;
}

/* 删除指定ID的订单 */
int delete_order_by_id(int order_id)
{
    int i, j;
    int found = 0;

    for (i = 0; i < order_count; i++)
    {
        if (orders[i].order_id == order_id)
        {
            found = 1;
            /* 将后面的订单前移 */
            for (j = i; j < order_count - 1; j++)
            {
                orders[j] = orders[j + 1];
            }
            order_count--;
            break;
        }
    }

    if (!found)
    {
        printf("未找到编号为 %d 的订单！\n", order_id);
        return -1;
    }

    /* 更新文件 */
    if (save_all_orders() != 0)
    {
        return -1;
    }

    printf("订单 %d 已删除！\n", order_id);
    return 0;
}

/* 删除全部订单 */
int delete_all_orders(void)
{
    FILE *fp;

    order_count = 0;

    /* 清空TXT文件 */
    fp = fopen("data/order.txt", "w");
    if (fp != NULL)
        fclose(fp);

    /* 清空BIN文件 */
    fp = fopen("data/order.dat", "wb");
    if (fp != NULL)
        fclose(fp);

    printf("所有订单已删除！\n");
    return 0;
}

/* 加载订单 */
int load_orders(void)
{
    /* 优先从TXT加载 */
    if (load_orders_from_txt() == 0 && order_count > 0)
    {
        return 0;
    }
    /* 如果TXT没有数据，从BIN加载 */
    return load_orders_from_bin();
}
