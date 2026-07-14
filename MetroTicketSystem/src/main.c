/*
 * main.c - 主程序入口
 * Metro Ticket System - Version 0.1
 * 模拟地铁自动售票系统
 */

#include "../include/data.h"
#include <windows.h>

/* ========== 全局变量定义 ========== */
Station stations[MAX_STATIONS];
int station_count = 0;

Line lines[MAX_LINES];
int line_count = 0;

Order orders[MAX_ORDERS];
int order_count = 0;

/* ========== 工具函数实现 ========== */

void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int get_valid_int(int min, int max)
{
    int value;
    int result;
    char c;

    while (1)
    {
        result = scanf("%d", &value);
        if (result == 1 && value >= min && value <= max)
        {
            return value;
        }
        /* 清除无效输入 */
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        printf("输入无效，请重新输入(%d-%d): ", min, max);
    }
}

void get_current_time(char *buffer)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buffer, MAX_TIME, "%Y-%m-%d %H:%M:%S", tm_info);
}

/* ========== 主函数 ========== */

int main(void)
{
    /* 设置控制台编码为 UTF-8，解决中文乱码 */
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    /* 切换到程序所在目录，确保 data/ 路径正确 */
    {
        char exe_path[MAX_PATH];
        GetModuleFileNameA(NULL, exe_path, MAX_PATH);
        char *last_slash = strrchr(exe_path, '\\');
        if (last_slash != NULL)
        {
            *last_slash = '\0';
            SetCurrentDirectoryA(exe_path);
        }
    }

    /* 初始化数据 */
    if (init_data_files() != 0)
    {
        printf("数据文件初始化失败！\n");
        return 1;
    }

    load_data();

    /* 显示欢迎界面 */
    show_welcome();

    /* 进入主菜单 */
    show_menu();

    return 0;
}
