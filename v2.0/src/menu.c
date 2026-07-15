/*
 * menu.c - 主菜单模块 (EasyX图形版)
 * Metro Ticket System v2.0
 */

#include "../include/data.h"

/* 按钮结构体 */
typedef struct
{
    int x, y, w, h;
    const char *text;
    COLORREF color;
} Button;

/* 按钮点击检测 */
static int is_button_clicked(Button btn, int mx, int my)
{
    return (mx >= btn.x && mx <= btn.x + btn.w &&
            my >= btn.y && my <= btn.y + btn.h);
}

/* 绘制按钮 */
static void draw_button(Button btn)
{
    setfillcolor(btn.color);
    setcolor(RGB(0, 51, 102));
    setlinestyle(PS_SOLID, 2);
    fillroundrect(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, 8, 8);

    settextcolor(WHITE);
    settextstyle(18, 0, _T("微软雅黑"));
    int text_x = btn.x + (btn.w - textwidth(_T(btn.text))) / 2;
    int text_y = btn.y + (btn.h - 20) / 2;
    outtextxy(text_x, text_y, _T(btn.text));
}

/* ================================================================
 * 显示主菜单
 * ================================================================ */
void show_menu(void)
{
    /* 定义6个功能按钮 */
    Button buttons[] = {
        {100, 120, 250, 60, "1. 地图查询", RGB(0, 153, 204)},
        {450, 120, 250, 60, "2. 购票服务", RGB(0, 180, 100)},
        {100, 210, 250, 60, "3. 历史记录", RGB(200, 150, 50)},
        {450, 210, 250, 60, "4. 条件查询", RGB(180, 100, 180)},
        {100, 300, 250, 60, "5. 系统说明", RGB(100, 150, 200)},
        {450, 300, 250, 60, "6. 系统测试", RGB(200, 80, 80)},
    };
    int btn_count = sizeof(buttons) / sizeof(Button);

    while (1)
    {
        /* 清屏 */
        cleardevice();
        setbkcolor(RGB(240, 248, 255));
        cleardevice();

        /* 绘制标题 */
        settextcolor(RGB(0, 51, 102));
        settextstyle(32, 0, _T("微软雅黑"));
        int title_x = (800 - textwidth(_T("主菜单"))) / 2;
        outtextxy(title_x, 30, _T("主菜单"));

        /* 绘制装饰线 */
        setcolor(RGB(0, 153, 204));
        setlinestyle(PS_SOLID, 2);
        line(300, 75, 500, 75);

        /* 绘制所有按钮 */
        for (int i = 0; i < btn_count; i++)
        {
            draw_button(buttons[i]);
        }

        /* 绘制退出按钮 */
        Button exit_btn = {300, 420, 200, 50, "0. 退出系统", RGB(150, 150, 150)};
        draw_button(exit_btn);

        /* 提示信息 */
        settextcolor(RGB(153, 153, 153));
        settextstyle(14, 0, _T("微软雅黑"));
        int tip_x = (800 - textwidth(_T("请点击对应按钮进入功能  |  ESC 键退出系统"))) / 2;
        outtextxy(tip_x, 520, _T("请点击对应按钮进入功能  |  ESC 键退出系统"));

        /* 等待用户操作 */
        int running = 1;
        while (running)
        {
            if (MouseHit())
            {
                MOUSEMSG msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    /* 检查按钮点击 */
                    for (int i = 0; i < btn_count; i++)
                    {
                        if (is_button_clicked(buttons[i], msg.x, msg.y))
                        {
                            running = 0;
                            switch (i)
                            {
                            case 0: /* 地图查询 */
                                show_map();
                                break;
                            case 1: /* 购票服务 */
                            {
                                int start_id, end_id, num;
                                /* 显示购票界面 */
                                cleardevice();
                                setbkcolor(RGB(240, 248, 255));
                                cleardevice();
                                settextcolor(RGB(0, 51, 102));
                                settextstyle(28, 0, _T("微软雅黑"));
                                outtextxy(300, 50, _T("购票服务"));

                                /* 这里简化处理，实际需要图形化选择 */
                                settextcolor(RGB(102, 102, 102));
                                settextstyle(16, 0, _T("微软雅黑"));
                                outtextxy(200, 150, _T("请在控制台窗口操作购票..."));

                                /* 临时用控制台 */
                                AllocConsole();
                                freopen("CONIN$", "r", stdin);
                                freopen("CONOUT$", "w", stdout);

                                printf("\n===== 购票服务 =====\n");
                                printf("请输入起点站ID: ");
                                start_id = get_valid_int(1, station_count);
                                printf("请输入终点站ID: ");
                                end_id = get_valid_int(1, station_count);
                                printf("请输入购票数量(1-%d): ", MAX_TICKET_NUM);
                                num = get_valid_int(1, MAX_TICKET_NUM);

                                if (start_id == end_id)
                                {
                                    printf("起点和终点不能相同！\n");
                                }
                                else
                                {
                                    int price = calculate_price(start_id, end_id);
                                    int total = price * num;
                                    printf("票价: %d元/张, 共%d张, 总计%d元\n",
                                           price, num, total);

                                    if (process_payment(total) == 0)
                                    {
                                        buy_ticket(start_id, end_id, num);
                                        printf("购票成功！\n");
                                    }
                                }

                                printf("\n按 Enter 键返回菜单...");
                                clear_input_buffer();
                                getchar();
                                FreeConsole();
                            }
                            break;
                            case 2: /* 历史记录 */
                            {
                                AllocConsole();
                                freopen("CONIN$", "r", stdin);
                                freopen("CONOUT$", "w", stdout);
                                show_history();
                                printf("\n按 Enter 键返回菜单...");
                                clear_input_buffer();
                                getchar();
                                FreeConsole();
                            }
                            break;
                            case 3: /* 条件查询 */
                            {
                                AllocConsole();
                                freopen("CONIN$", "r", stdin);
                                freopen("CONOUT$", "w", stdout);
                                search_menu();
                                printf("\n按 Enter 键返回菜单...");
                                clear_input_buffer();
                                getchar();
                                FreeConsole();
                            }
                            break;
                            case 4: /* 系统说明 */
                            {
                                AllocConsole();
                                freopen("CONOUT$", "w", stdout);
                                show_instruction();
                                printf("\n按 Enter 键返回菜单...");
                                clear_input_buffer();
                                getchar();
                                FreeConsole();
                            }
                            break;
                            case 5: /* 系统测试 */
                            {
                                AllocConsole();
                                freopen("CONIN$", "r", stdin);
                                freopen("CONOUT$", "w", stdout);
                                run_tests();
                                FreeConsole();
                            }
                            break;
                            }
                        }
                    }

                    /* 检查退出按钮 */
                    if (is_button_clicked(exit_btn, msg.x, msg.y))
                    {
                        return; /* 返回主函数，退出 */
                    }
                }
            }

            if (kbhit())
            {
                int key = getch();
                if (key == 27) /* ESC键 */
                {
                    return;
                }
            }

            Sleep(50);
        }
    }
}
