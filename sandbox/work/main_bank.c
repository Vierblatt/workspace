#include "BankSimulation.h"

int main() {
    // 设置随机数种子
    srand((unsigned int)time(NULL));
    
    // 初始化银行系统
    BankSystem bank;
    int initial_money = 10000;  // 初始资金10000元
    int close_time = 600;       // 营业时间600分钟
    
    printf("银行模拟系统\n");
    printf("============\n");
    printf("请输入初始资金 (默认10000): ");
    scanf("%d", &initial_money);
    
    printf("请输入营业时间(分钟) (默认600): ");
    scanf("%d", &close_time);
    
    init_bank_system(&bank, initial_money, close_time);
    
    // 运行模拟
    run_simulation(&bank);
    
    // 打印统计信息
    print_statistics(&bank);
    
    // 释放内存
    free_all_customers(&bank.queue1);
    free_all_customers(&bank.queue2);
    free_all_events(&bank.event_list);
    
    return 0;
}