/*
 * payment.c - 支付找零模块
 * Metro Ticket System
 * 接收用户输入支付金额，判断金额是否充足，自动计算找零
 */

#include "../include/data.h"

/*
 * 处理支付流程
 * 参数: total - 应付总金额
 * 返回: 找零金额
 * Bug2修复: 金额不足时提示并重新输入
 * Bug1修复: 非法输入拦截
 */
int process_payment(int total)
{
    int payment;
    int change;

    printf("\n");
    printf("========================================\n");
    printf("          支付界面                    \n");
    printf("========================================\n");
    printf("  应付金额: %d 元\n", total);
    printf("----------------------------------------\n");

    while (1)
    {
        printf("  请输入支付金额: ");
        payment = get_valid_int(0, 10000);

        if (payment < total)
        {
            /* Bug2: 金额不足 */
            printf("  【错误】金额不足！还需 %d 元\n", total - payment);
            printf("  请重新投币...\n");
        }
        else
        {
            change = payment - total;
            printf("  支付成功！\n");
            printf("  实收: %d 元\n", payment);
            printf("  找零: %d 元\n", change);
            printf("========================================\n");
            return change;
        }
    }
}
