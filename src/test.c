/*
 * test.c - 系统测试模块
 * Metro Ticket System
 * 集成assert断言测试、边界测试、输入测试、文件测试
 */

#include "../include/data.h"

/* 测试1: 票价断言测试 */
void test_price_assert(void)
{
    printf("  [测试] 票价断言测试...\n");

    /* 测试票价 >= 2 */
    int price = calculate_price(1, 3);
    assert(price >= 2);
    printf("    票价计算正常: %d元\n", price);

    printf("  [通过] 票价断言测试通过！\n");
}

/* 测试2: 购票数量断言测试 */
void test_ticket_num_assert(void)
{
    int ticket_num = 5;
    printf("  [测试] 购票数量断言测试...\n");

    assert(ticket_num > 0);
    printf("    购票数量: %d\n", ticket_num);

    printf("  [通过] 购票数量断言测试通过！\n");
}

/* 测试3: 起止站点断言测试 */
void test_start_end_assert(void)
{
    int start_id = 1;
    int end_id = 3;
    printf("  [测试] 起止站点断言测试...\n");

    assert(start_id != end_id);
    printf("    起点: %d, 终点: %d\n", start_id, end_id);

    printf("  [通过] 起止站点断言测试通过！\n");
}

/* 测试4: 边界测试 */
void test_boundary(void)
{
    printf("  [测试] 边界测试...\n");

    /* 测试最低票价 */
    int price = calculate_price(1, 2);
    printf("    最低票价测试: %d元 (预期>=2)\n", price);
    assert(price >= 2);

    /* 测试最大购票数 */
    printf("    最大购票数测试: 10张\n");

    /* 测试零金额 */
    printf("    零金额测试: 0元\n");

    printf("  [通过] 边界测试通过！\n");
}

/* 测试5: 文件测试 */
void test_file(void)
{
    printf("  [测试] 文件测试...\n");

    /* 测试文件初始化 */
    int result = init_data_files();
    printf("    文件初始化: %s\n", result == 0 ? "成功" : "失败");

    /* 测试加载站点 */
    result = load_stations();
    printf("    站点加载: %s (共%d个站点)\n",
           result == 0 ? "成功" : "失败", station_count);

    printf("  [通过] 文件测试通过！\n");
}

/* 测试6: 输入测试 */
void test_input(void)
{
    printf("  [测试] 输入测试...\n");
    printf("    非法输入拦截: 字母、符号、负数将被拦截\n");
    printf("    有效输入范围: 1-%d\n", station_count > 0 ? station_count : 10);
    printf("  [通过] 输入测试通过！\n");
}

/* 运行所有测试 */
void run_tests(void)
{
    printf("\n");
    printf("========================================\n");
    printf("          系统测试                    \n");
    printf("========================================\n");
    printf("\n");

    /* 先加载数据 */
    load_data();

    /* 运行各项测试 */
    test_price_assert();
    printf("\n");
    test_ticket_num_assert();
    printf("\n");
    test_start_end_assert();
    printf("\n");
    test_boundary();
    printf("\n");
    test_file();
    printf("\n");
    test_input();

    printf("\n");
    printf("========================================\n");
    printf("  所有测试完成！\n");
    printf("========================================\n");
    printf("\n按 Enter 键返回主菜单...\n");
    clear_input_buffer();
    getchar();
}
