/*
 * main.c - 主程序入口
 * Metro Ticket System v2.0 (EasyX版)
 */

#include "../include/data.h"

/* ================================================================
 * 全局变量定义
 * ================================================================ */
Station stations[MAX_STATIONS];
int station_count = 0;

Line lines[MAX_LINES];
int line_count = 0;

Order orders[MAX_ORDERS];
int order_count = 0;

/* ================================================================
 * 工具函数
 * ================================================================ */

/* 清空输入缓冲区 */
void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* 获取合法整数输入 */
int get_valid_int(int min, int max)
{
    int input;
    int result;
    char c;

    while (1)
    {
        result = scanf("%d", &input);
        if (result == 1 && input >= min && input <= max)
        {
            return input;
        }
        /* 清空缓冲区 */
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        printf("    输入无效！请输入 %d-%d 之间的数字: ", min, max);
    }
}

/* ================================================================
 * EasyX图形界面 - 主函数
 * ================================================================ */
int main(void)
{
    /* 初始化图形窗口 */
    initgraph(800, 600);
    setbkcolor(WHITE);
    setbkmode(TRANSPARENT);

    /* 加载数据 */
    load_data();

    /* 显示欢迎界面 */
    show_welcome();

    /* 进入主菜单循环 */
    show_menu();

    /* 关闭图形窗口 */
    closegraph();
    return 0;
}
