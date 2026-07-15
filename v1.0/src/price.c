/*
 * price.c - 票价计算模块
 * Metro Ticket System
 * 根据起点、终点站点距离自动计算票价
 * 深圳地铁计价规则：2元起步，每3站加1元，最高12元
 */

#include "../include/data.h"

/* 计算两个站点之间的最短距离（站数） */
static int calc_station_distance(int start_id, int end_id)
{
    int start_idx, end_idx;
    int start_line, end_line;
    int i, j;
    int dist;

    start_idx = find_station_by_id(start_id);
    end_idx = find_station_by_id(end_id);

    if (start_idx == -1 || end_idx == -1)
        return -1;

    start_line = stations[start_idx].line_id;
    end_line = stations[end_idx].line_id;

    if (start_line == end_line)
    {
        /* 同线路：直接计算站数差 */
        /* 需要按线路内顺序计算，不能简单用数组索引差 */
        int s_idx = -1, e_idx = -1;
        int count = 0;

        for (i = 0; i < station_count; i++)
        {
            if (stations[i].line_id == start_line)
            {
                if (stations[i].station_id == start_id)
                    s_idx = count;
                if (stations[i].station_id == end_id)
                    e_idx = count;
                count++;
            }
        }

        if (s_idx >= 0 && e_idx >= 0)
            return abs(s_idx - e_idx);
    }

    /* 跨线路：找最近的换乘站计算距离 */
    /* 简化：按数组索引差估算 */
    dist = abs(start_idx - end_idx);
    if (dist < 3)
        dist = 3; /* 跨线路至少3站 */

    return dist;
}

/* 计算票价
 * 深圳地铁规则：
 *   2元起步（0-3站）
 *   4站以上每3站加1元
 *   最高12元
 */
int calculate_price(int start_id, int end_id)
{
    int distance;
    int price;

    /* 断言：起止站点不同 */
    assert(start_id != end_id);

    distance = calc_station_distance(start_id, end_id);

    if (distance < 0)
    {
        return -1; /* 站点不存在 */
    }

    /* 深圳地铁计价：2元起步，每3站加1元 */
    if (distance <= 3)
    {
        price = 2;
    }
    else
    {
        price = 2 + (distance - 3 + 2) / 3; /* 向上取整 */
    }

    /* 最高12元 */
    if (price > 12)
        price = 12;

    /* 断言：票价至少2元 */
    assert(price >= 2);

    return price;
}
