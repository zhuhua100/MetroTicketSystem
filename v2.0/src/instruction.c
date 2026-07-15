/*
 * instruction.c - 系统说明模块
 * Metro Ticket System
 * 展示系统功能介绍、操作指南、使用须知
 */

#include "../include/data.h"

void show_instruction(void)
{
    printf("\n");
    printf("========================================\n");
    printf("          系统说明                    \n");
    printf("========================================\n");
    printf("\n");
    printf("【系统功能】\n");
    printf("  本系统模拟地铁自动售票机完整业务流程\n");
    printf("\n");
    printf("【操作流程】\n");
    printf("  欢迎界面 -> 主菜单 -> 选择服务 -> 完成操作\n");
    printf("\n");
    printf("【购票流程】\n");
    printf("  1. 选择起点站\n");
    printf("  2. 选择终点站\n");
    printf("  3. 选择购票数量\n");
    printf("  4. 确认票价\n");
    printf("  5. 支付金额\n");
    printf("  6. 取票完成\n");
    printf("\n");
    printf("【功能说明】\n");
    printf("  1. 地图查询 - 查看地铁线路图\n");
    printf("  2. 购票服务 - 购买地铁车票\n");
    printf("  3. 历史记录 - 查看购票记录\n");
    printf("  4. 条件查询 - 多条件组合查询\n");
    printf("  5. 系统测试 - 运行系统测试\n");
    printf("\n");
    printf("【开发环境】\n");
    printf("  开发语言: C11\n");
    printf("  图形库: EasyX\n");
    printf("  IDE: Visual Studio 2022\n");
    printf("  操作系统: Windows 10/11\n");
    printf("\n");
    printf("========================================\n");
    printf("按 Enter 键返回主菜单...\n");
    clear_input_buffer();
    getchar();
}
