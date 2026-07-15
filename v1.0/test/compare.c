/*
 * compare.c - AI方案对比实验
 * Metro Ticket System
 * 对比数组 vs 链表两种方案
 * 测试数据量: 1000 / 5000 / 10000
 * 测试指标: 运行时间 / 内存占用 / 维护性
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <psapi.h>

/* ========== 方案A: 静态数组 ========== */

#define MAX_DATA 10000

typedef struct
{
    int id;
    char name[20];
    int value;
} DataItem;

DataItem array_data[MAX_DATA];
int array_count = 0;

/* 数组 - 插入 */
int array_insert(DataItem item)
{
    if (array_count >= MAX_DATA)
        return -1;
    array_data[array_count++] = item;
    return 0;
}

/* 数组 - 查找（按ID） */
int array_find_by_id(int id)
{
    for (int i = 0; i < array_count; i++)
    {
        if (array_data[i].id == id)
            return i;
    }
    return -1;
}

/* 数组 - 删除（按ID） */
int array_delete_by_id(int id)
{
    int idx = array_find_by_id(id);
    if (idx == -1)
        return -1;
    for (int i = idx; i < array_count - 1; i++)
    {
        array_data[i] = array_data[i + 1];
    }
    array_count--;
    return 0;
}

/* 数组 - 遍历 */
void array_traverse(void)
{
    for (int i = 0; i < array_count; i++)
    {
        /* 模拟操作 */
        volatile int x = array_data[i].value;
    }
}

/* ========== 方案B: 动态链表 ========== */

typedef struct ListNode
{
    DataItem data;
    struct ListNode *next;
} ListNode;

ListNode *list_head = NULL;
int list_count = 0;

/* 链表 - 插入（尾插） */
int list_insert(DataItem item)
{
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    if (new_node == NULL)
        return -1;
    new_node->data = item;
    new_node->next = NULL;

    if (list_head == NULL)
    {
        list_head = new_node;
    }
    else
    {
        ListNode *p = list_head;
        while (p->next != NULL)
            p = p->next;
        p->next = new_node;
    }
    list_count++;
    return 0;
}

/* 链表 - 查找（按ID） */
ListNode *list_find_by_id(int id)
{
    ListNode *p = list_head;
    while (p != NULL)
    {
        if (p->data.id == id)
            return p;
        p = p->next;
    }
    return NULL;
}

/* 链表 - 删除（按ID） */
int list_delete_by_id(int id)
{
    ListNode *p = list_head;
    ListNode *prev = NULL;

    while (p != NULL)
    {
        if (p->data.id == id)
        {
            if (prev == NULL)
                list_head = p->next;
            else
                prev->next = p->next;
            free(p);
            list_count--;
            return 0;
        }
        prev = p;
        p = p->next;
    }
    return -1;
}

/* 链表 - 遍历 */
void list_traverse(void)
{
    ListNode *p = list_head;
    while (p != NULL)
    {
        volatile int x = p->data.value;
        p = p->next;
    }
}

/* 链表 - 释放所有节点 */
void list_free_all(void)
{
    ListNode *p = list_head;
    while (p != NULL)
    {
        ListNode *temp = p;
        p = p->next;
        free(temp);
    }
    list_head = NULL;
    list_count = 0;
}

/* ========== 测试数据生成 ========== */

void generate_test_data(DataItem *data, int count)
{
    for (int i = 0; i < count; i++)
    {
        data[i].id = i + 1;
        sprintf(data[i].name, "Item_%d", i + 1);
        data[i].value = rand() % 1000;
    }
}

/* ========== 性能测试 ========== */

/* 获取当前内存使用（KB） */
SIZE_T get_memory_usage(void)
{
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
    {
        return pmc.WorkingSetSize / 1024;
    }
    return 0;
}

/* 运行时间测试（毫秒） */
double get_time_ms(void)
{
    LARGE_INTEGER freq, start;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    return (double)start.QuadPart / (double)freq.QuadPart * 1000.0;
}

/* 测试数组方案 */
void test_array(DataItem *data, int count)
{
    double t1, t2;
    SIZE_T mem_before, mem_after;

    printf("\n");
    printf("  ----------------------------------------\n");
    printf("  方案A: 静态数组 (数据量: %d)\n", count);
    printf("  ----------------------------------------\n");

    /* 清空数组 */
    array_count = 0;

    /* 测试插入 */
    mem_before = get_memory_usage();
    t1 = get_time_ms();
    for (int i = 0; i < count; i++)
    {
        array_insert(data[i]);
    }
    t2 = get_time_ms();
    mem_after = get_memory_usage();
    printf("  插入 %d 条: %.2f ms\n", count, t2 - t1);
    printf("  内存变化: %lu KB -> %lu KB (增加 %lu KB)\n",
           (unsigned long)mem_before, (unsigned long)mem_after,
           (unsigned long)(mem_after - mem_before));

    /* 测试查找 */
    t1 = get_time_ms();
    for (int i = 0; i < 100; i++)
    {
        int id = rand() % count + 1;
        array_find_by_id(id);
    }
    t2 = get_time_ms();
    printf("  查找 100 次: %.2f ms\n", t2 - t1);

    /* 测试遍历 */
    t1 = get_time_ms();
    array_traverse();
    t2 = get_time_ms();
    printf("  遍历 1 次: %.2f ms\n", t2 - t1);

    /* 测试删除 */
    t1 = get_time_ms();
    for (int i = 0; i < 100; i++)
    {
        int id = rand() % count + 1;
        array_delete_by_id(id);
    }
    t2 = get_time_ms();
    printf("  删除 100 次: %.2f ms\n", t2 - t1);

    printf("  总内存占用: %lu KB\n", (unsigned long)(sizeof(array_data)));
}

/* 测试链表方案 */
void test_list(DataItem *data, int count)
{
    double t1, t2;
    SIZE_T mem_before, mem_after;

    printf("\n");
    printf("  ----------------------------------------\n");
    printf("  方案B: 动态链表 (数据量: %d)\n", count);
    printf("  ----------------------------------------\n");

    /* 清空链表 */
    list_free_all();

    /* 测试插入 */
    mem_before = get_memory_usage();
    t1 = get_time_ms();
    for (int i = 0; i < count; i++)
    {
        list_insert(data[i]);
    }
    t2 = get_time_ms();
    mem_after = get_memory_usage();
    printf("  插入 %d 条: %.2f ms\n", count, t2 - t1);
    printf("  内存变化: %lu KB -> %lu KB (增加 %lu KB)\n",
           (unsigned long)mem_before, (unsigned long)mem_after,
           (unsigned long)(mem_after - mem_before));

    /* 测试查找 */
    t1 = get_time_ms();
    for (int i = 0; i < 100; i++)
    {
        int id = rand() % count + 1;
        list_find_by_id(id);
    }
    t2 = get_time_ms();
    printf("  查找 100 次: %.2f ms\n", t2 - t1);

    /* 测试遍历 */
    t1 = get_time_ms();
    list_traverse();
    t2 = get_time_ms();
    printf("  遍历 1 次: %.2f ms\n", t2 - t1);

    /* 测试删除 */
    t1 = get_time_ms();
    for (int i = 0; i < 100; i++)
    {
        int id = rand() % count + 1;
        list_delete_by_id(id);
    }
    t2 = get_time_ms();
    printf("  删除 100 次: %.2f ms\n", t2 - t1);

    /* 计算链表内存占用 */
    SIZE_T list_mem = list_count * (sizeof(ListNode));
    printf("  总内存占用: %lu KB (节点数: %d)\n",
           (unsigned long)(list_mem / 1024), list_count);

    /* 释放链表 */
    list_free_all();
}

/* ========== 主函数 ========== */

int main(void)
{
    DataItem test_data[MAX_DATA];
    int sizes[] = {1000, 5000, 10000};
    int num_sizes = 3;

    /* 设置控制台编码 */
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    printf("\n");
    printf("========================================\n");
    printf("  AI方案对比实验                      \n");
    printf("  数组 vs 链表                        \n");
    printf("========================================\n");
    printf("\n");

    for (int s = 0; s < num_sizes; s++)
    {
        int count = sizes[s];

        /* 生成测试数据 */
        generate_test_data(test_data, count);

        printf("\n");
        printf("========================================\n");
        printf("  测试数据量: %d 条\n", count);
        printf("========================================\n");

        /* 测试数组 */
        test_array(test_data, count);

        /* 测试链表 */
        test_list(test_data, count);

        printf("\n");
        printf("  ----------------------------------------\n");
        printf("  数据量 %d 测试完成\n", count);
        printf("  ----------------------------------------\n");
    }

    /* 输出总结对比表 */
    printf("\n");
    printf("========================================\n");
    printf("  总结对比                            \n");
    printf("========================================\n");
    printf("\n");
    printf("  ┌──────────────┬─────────────────────┬─────────────────────┐\n");
    printf("  │  对比维度    │  方案A: 静态数组    │  方案B: 动态链表    │\n");
    printf("  ├──────────────┼─────────────────────┼─────────────────────┤\n");
    printf("  │  内存分配    │  编译时固定分配     │  运行时动态分配     │\n");
    printf("  │  插入效率    │  O(1) 尾部插入      │  O(n) 尾部遍历插入  │\n");
    printf("  │  查找效率    │  O(n) 顺序查找      │  O(n) 顺序查找      │\n");
    printf("  │  删除效率    │  O(n) 需移动元素    │  O(n) 修改指针      │\n");
    printf("  │  内存碎片    │  无                 │  有                 │\n");
    printf("  │  内存上限    │  固定 MAX_DATA      │  仅受堆内存限制     │\n");
    printf("  │  代码复杂度  │  简单               │  较复杂(需管理指针) │\n");
    printf("  │  维护难度    │  低                 │  中                 │\n");
    printf("  │  适用场景    │  数据量可预估       │  数据量动态变化     │\n");
    printf("  └──────────────┴─────────────────────┴─────────────────────┘\n");
    printf("\n");
    printf("========================================\n");
    printf("  实验完成！\n");
    printf("========================================\n");
    printf("\n");

    return 0;
}
