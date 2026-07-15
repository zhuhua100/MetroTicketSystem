/*
 * welcome.c - 欢迎界面模块 (EasyX图形版)
 * Metro Ticket System v2.0
 */

#include "../include/data.h"

/* ================================================================
 * 显示欢迎界面
 * ================================================================ */
void show_welcome(void)
{
    /* 清屏 */
    cleardevice();

    /* 设置背景色 */
    setbkcolor(RGB(240, 248, 255)); /* 淡蓝色背景 */
    cleardevice();

    /* 绘制标题 */
    settextcolor(RGB(0, 51, 102)); /* 深蓝色 */
    settextstyle(48, 0, _T("微软雅黑"));
    setbkmode(TRANSPARENT);

    int title_x = (800 - textwidth(_T("模拟地铁自动售票系统"))) / 2;
    outtextxy(title_x, 100, _T("模拟地铁自动售票系统"));

    /* 绘制副标题 */
    settextcolor(RGB(0, 102, 153));
    settextstyle(24, 0, _T("微软雅黑"));
    int sub_x = (800 - textwidth(_T("Metro Ticket System v2.0"))) / 2;
    outtextxy(sub_x, 170, _T("Metro Ticket System v2.0"));

    /* 绘制装饰线 */
    setcolor(RGB(0, 153, 204));
    setlinestyle(PS_SOLID, 2);
    line(200, 220, 600, 220);

    /* 绘制开发者信息 */
    settextcolor(RGB(102, 102, 102));
    settextstyle(16, 0, _T("微软雅黑"));
    int dev_x = (800 - textwidth(_T("开发者: 课程设计小组"))) / 2;
    outtextxy(dev_x, 260, _T("开发者: 课程设计小组"));

    int copy_x = (800 - textwidth(_T("Copyright 2026 Metro Ticket System"))) / 2;
    outtextxy(copy_x, 290, _T("Copyright 2026 Metro Ticket System"));

    /* 绘制启动按钮 */
    setfillcolor(RGB(0, 153, 204));
    setcolor(RGB(0, 102, 153));
    setlinestyle(PS_SOLID, 2);
    fillroundrect(300, 380, 500, 440, 10, 10);

    settextcolor(WHITE);
    settextstyle(20, 0, _T("微软雅黑"));
    int btn_x = (800 - textwidth(_T("进入系统"))) / 2;
    outtextxy(btn_x, 400, _T("进入系统"));

    /* 提示信息 */
    settextcolor(RGB(153, 153, 153));
    settextstyle(14, 0, _T("微软雅黑"));
    int tip_x = (800 - textwidth(_T("点击按钮或按 Enter 键进入系统  |  ESC 键退出"))) / 2;
    outtextxy(tip_x, 500, _T("点击按钮或按 Enter 键进入系统  |  ESC 键退出"));

    /* 等待用户操作 */
    while (1)
    {
        /* 检测鼠标点击 */
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                /* 检查是否点击了按钮区域 */
                if (msg.x >= 300 && msg.x <= 500 &&
                    msg.y >= 380 && msg.y <= 440)
                {
                    return; /* 进入系统 */
                }
            }
        }

        /* 检测键盘输入 */
        if (kbhit())
        {
            int key = getch();
            if (key == 13) /* Enter键 */
                return;
            else if (key == 27) /* ESC键 */
            {
                closegraph();
                exit(0);
            }
        }

        Sleep(50); /* 防止CPU占用过高 */
    }
}
