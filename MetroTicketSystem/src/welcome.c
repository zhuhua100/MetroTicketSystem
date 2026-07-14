/*
 * welcome.c - 欢迎界面模块
 * Metro Ticket System
 * 显示项目名称、开发者信息、启动按钮
 */

#include "../include/data.h"

void show_welcome(void)
{
    printf("\n");
    printf("========================================\n");
    printf("                                    \n");
    printf("    模拟地铁自动售票系统            \n");
    printf("    Metro Ticket System             \n");
    printf("                                    \n");
    printf("========================================\n");
    printf("                                    \n");
    printf("    版本: v1.0                      \n");
    printf("    开发者: AI辅助开发团队          \n");
    printf("    开发语言: C11 + EasyX           \n");
    printf("    开发环境: Visual Studio 2022    \n");
    printf("                                    \n");
    printf("========================================\n");
    printf("\n");
    printf("按 Enter 键进入系统...\n");
    printf("按 ESC 键退出系统...\n");

    char c = getchar();
    if (c == 27) /* ESC */
    {
        printf("感谢使用，再见！\n");
        exit(0);
    }
    clear_input_buffer();
}
