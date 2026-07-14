/*
 * data.h - 统一数据结构定义
 * Metro Ticket System
 * 所有模块共享此头文件
 */

#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

/* ========== 常量定义 ========== */
#define MAX_STATIONS 100
#define MAX_LINES 20
#define MAX_ORDERS 1000
#define MAX_NAME 20
#define MAX_TIME 30
#define MAX_TICKETS 100

/* ========== 数据结构 ========== */

/* 站点结构体 */
typedef struct
{
    int station_id;        /* 站点编号 */
    char station_name[20]; /* 站点名称 */
    int line_id;           /* 所属线路 */
    int is_transfer;       /* 是否换乘站 1是 0否 */
} Station;

/* 线路结构体 */
typedef struct
{
    int line_id;        /* 线路编号 */
    char line_name[20]; /* 线路名称 */
    int station_count;  /* 站点数量 */
} Line;

/* 车票结构体 */
typedef struct
{
    int ticket_id;  /* 车票编号 */
    int start_id;   /* 起点站编号 */
    int end_id;     /* 终点站编号 */
    int price;      /* 票价 */
    int ticket_num; /* 购票数量 */
} Ticket;

/* 订单结构体（历史记录） */
typedef struct
{
    int order_id;    /* 订单编号 */
    char time[30];   /* 购票时间 */
    int start_id;    /* 起点站编号 */
    int end_id;      /* 终点站编号 */
    int price;       /* 单价 */
    int num;         /* 数量 */
    int total_money; /* 总金额 */
    int change;      /* 找零 */
} Order;

/* ========== 全局数据 ========== */
extern Station stations[MAX_STATIONS];
extern int station_count;

extern Line lines[MAX_LINES];
extern int line_count;

extern Order orders[MAX_ORDERS];
extern int order_count;

/* ========== 函数声明 ========== */

/* 欢迎界面 */
void show_welcome(void);

/* 系统说明 */
void show_instruction(void);

/* 主菜单 */
void show_menu(void);

/* 地图查询 */
void show_map(void);

/* 站点管理 */
int load_stations(void);
int find_station_by_id(int id);
int find_station_by_name(const char *name);
void list_stations(void);

/* 票价计算 */
int calculate_price(int start_id, int end_id);

/* 购票模块 */
void buy_ticket(void);

/* 支付模块 */
int process_payment(int total);

/* 文件管理 */
int load_data(void);
int save_order_to_file(const Order *order);
int load_orders(void);
int init_data_files(void);

/* 历史记录 */
void show_history(void);
int delete_order_by_id(int order_id);
int delete_all_orders(void);
int save_all_orders(void);

/* 复杂查询 */
void search_menu(void);

/* 测试模块 */
void run_tests(void);

/* 工具函数 */
void clear_input_buffer(void);
int get_valid_int(int min, int max);
void get_current_time(char *buffer);

#endif /* DATA_H */
