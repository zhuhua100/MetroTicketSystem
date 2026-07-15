/*
 * data.h - 统一数据结构定义
 * Metro Ticket System v2.0 (EasyX版)
 */

#ifndef DATA_H
#define DATA_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>
#include <windows.h>

/* ================================================================
 * 常量定义
 * ================================================================ */
#define MAX_STATIONS 100  /* 最大站点数 */
#define MAX_LINES 20      /* 最大线路数 */
#define MAX_ORDERS 500    /* 最大订单数 */
#define MAX_NAME 20       /* 名称最大长度 */
#define MAX_TICKET_NUM 10 /* 最大购票数 */
#define MAX_PRICE 12      /* 最高票价 */
#define MIN_PRICE 2       /* 最低票价 */

/* ================================================================
 * 数据结构
 * ================================================================ */

/* 站点结构体 */
typedef struct
{
    int station_id;
    char station_name[MAX_NAME];
    int line_id;     /* 所属线路 */
    int is_transfer; /* 是否换乘站 1是 0否 */
} Station;

/* 线路结构体 */
typedef struct
{
    int line_id;
    char line_name[MAX_NAME];
    int station_count;
} Line;

/* 车票结构体 */
typedef struct
{
    int ticket_id;
    int start_id;
    int end_id;
    int price;
    int ticket_num;
} Ticket;

/* 订单结构体（历史记录） */
typedef struct
{
    int order_id;
    char time[30];
    int start_id;
    int end_id;
    int price;
    int num;
    int total_money;
    int change;
} Order;

/* ================================================================
 * 全局变量声明
 * ================================================================ */
extern Station stations[MAX_STATIONS];
extern int station_count;

extern Line lines[MAX_LINES];
extern int line_count;

extern Order orders[MAX_ORDERS];
extern int order_count;

/* ================================================================
 * 函数声明
 * ================================================================ */

/* 文件管理 */
int init_data_files(void);
int load_stations(void);
int load_lines(void);
int load_orders_txt(void);
int load_orders_bin(void);
int save_orders_txt(void);
int save_orders_bin(void);
void load_data(void);

/* 站点管理 */
int find_station_by_id(int id);
int find_station_by_name(const char *name);
void list_all_stations(void);

/* 票价计算 */
int calculate_price(int start_id, int end_id);

/* 购票 */
int buy_ticket(int start_id, int end_id, int num);

/* 支付 */
int process_payment(int total);

/* 历史记录 */
void show_history(void);
int delete_order(int order_id);
int clear_all_orders(void);

/* 查询 */
void search_menu(void);

/* 测试 */
void run_tests(void);

/* 工具函数 */
int get_valid_int(int min, int max);
void clear_input_buffer(void);

/* UI函数 (v2.0 EasyX) */
void show_welcome(void);
void show_menu(void);
void show_instruction(void);
void show_map(void);

#endif /* DATA_H */
