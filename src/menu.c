/*
 * menu.c - 主菜单模块
 * Metro Ticket System
 * 系统核心导航界面
 */

#include "../include/data.h"

void show_menu(void)
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("========================================\n");
        printf("          主菜单                      \n");
        printf("========================================\n");
        printf("                                    \n");
        printf("    1. 地图查询                      \n");
        printf("    2. 购票服务                      \n");
        printf("    3. 历史记录                      \n");
        printf("    4. 条件查询                      \n");
        printf("    5. 系统说明                      \n");
        printf("    6. 系统测试                      \n");
        printf("    7. 退出系统                      \n");
        printf("                                    \n");
        printf("========================================\n");
        printf("请选择(1-7): ");

        choice = get_valid_int(1, 7);

        switch (choice)
        {
        case 1:
            show_map();
            break;
        case 2:
            buy_ticket();
            break;
        case 3:
            show_history();
            break;
        case 4:
            search_menu();
            break;
        case 5:
            show_instruction();
            break;
        case 6:
            run_tests();
            break;
        case 7:
            printf("感谢使用本系统，再见！\n");
            return;
        default:
            printf("无效选择，请重新输入！\n");
            break;
        }
    }
}
