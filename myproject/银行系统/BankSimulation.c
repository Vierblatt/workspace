#include "BankSimulation.h"

// 初始化银行系统
void init_bank_system(BankSystem* bank, int initial_money, int close_time) {
    bank->total_money = initial_money;
    bank->current_time = 0;
    bank->close_time = close_time;
    bank->total_customers = 0;
    bank->total_wait_time = 0;
    
    init_queue(&bank->queue1);
    init_queue(&bank->queue2);
    bank->event_list = NULL;
    
    // 创建第一个客户到达事件
    Customer* first_customer = create_customer(0);
    Event* first_event = (Event*)malloc(sizeof(Event));
    first_event->occur_time = 0;
    first_event->event_type = 0; // 到达事件
    first_event->customer = first_customer;
    first_event->next = NULL;
    
    insert_event(&bank->event_list, first_event);
}

// 初始化队列
void init_queue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// 检查队列是否为空
int is_queue_empty(Queue* q) {
    return q->front == NULL;
}

// 入队
void enqueue(Queue* q, Customer* customer) {
    customer->next = NULL;
    if (is_queue_empty(q)) {
        q->front = customer;
        q->rear = customer;
    } else {
        q->rear->next = customer;
        q->rear = customer;
    }
}

// 出队
Customer* dequeue(Queue* q) {
    if (is_queue_empty(q)) {
        return NULL;
    }
    
    Customer* customer = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    customer->next = NULL;
    return customer;
}

// 获取队首元素
Customer* queue_front(Queue* q) {
    if (is_queue_empty(q)) {
        return NULL;
    }
    return q->front;
}

// 初始化事件列表
void init_event_list(Event** event_list) {
    *event_list = NULL;
}

// 插入事件（按时间顺序）
void insert_event(Event** event_list, Event* event) {
    if (*event_list == NULL || (*event_list)->occur_time > event->occur_time) {
        event->next = *event_list;
        *event_list = event;
        return;
    }
    
    Event* current = *event_list;
    while (current->next != NULL && current->next->occur_time <= event->occur_time) {
        current = current->next;
    }
    
    event->next = current->next;
    current->next = event;
}

// 获取下一个事件
Event* get_next_event(Event** event_list) {
    if (*event_list == NULL) {
        return NULL;
    }
    
    Event* event = *event_list;
    *event_list = (*event_list)->next;
    event->next = NULL;
    return event;
}

// 生成随机客户
Customer* create_customer(int arrive_time) {
    Customer* customer = (Customer*)malloc(sizeof(Customer));
    customer->arrive_time = arrive_time;
    
    // 随机生成服务时间（1-20分钟）
    customer->duration = rand() % 20 + 1;
    
    // 随机生成交易金额（-5000到5000元）
    customer->amount = (rand() % 10000 - 5000);
    
    customer->next = NULL;
    return customer;
}

// 处理客户到达事件
void handle_arrive_event(BankSystem* bank, Event* event) {
    Customer* customer = event->customer;
    
    // 将客户加入第一个队列
    enqueue(&bank->queue1, customer);
    bank->total_customers++;
    
    printf("时间 %d: 客户到达，交易金额 %d 元，服务时间 %d 分钟\n", 
           bank->current_time, customer->amount, customer->duration);
    
    // 生成下一个客户到达事件
    if (bank->current_time < bank->close_time) {
        // 下一个客户到达的时间间隔（1-10分钟）
        int interval = rand() % 10 + 1;
        int next_arrive_time = bank->current_time + interval;
        
        if (next_arrive_time < bank->close_time) {
            Customer* next_customer = create_customer(next_arrive_time);
            Event* next_event = (Event*)malloc(sizeof(Event));
            next_event->occur_time = next_arrive_time;
            next_event->event_type = 0; // 到达事件
            next_event->customer = next_customer;
            next_event->next = NULL;
            
            insert_event(&bank->event_list, next_event);
        }
    }
    
    free(event);
}

// 处理客户离开事件
void handle_leave_event(BankSystem* bank, Event* event) {
    Customer* customer = event->customer;
    
    // 计算客户在银行的总逗留时间
    int stay_time = bank->current_time - customer->arrive_time;
    bank->total_wait_time += stay_time;
    
    printf("时间 %d: 客户离开，交易金额 %d 元，总逗留时间 %d 分钟\n", 
           bank->current_time, customer->amount, stay_time);
    
    // 如果是存款或还款业务（金额为正）
    if (customer->amount > 0) {
        bank->total_money += customer->amount;
        printf("  银行资金增加 %d 元，当前总额 %d 元\n", customer->amount, bank->total_money);
        
        // 处理第二个队列中等待的客户
        process_queue2(bank);
    } 
    // 如果是取款或借款业务（金额为负）
    else {
        // 检查银行是否有足够资金
        if (bank->total_money >= abs(customer->amount)) {
            bank->total_money += customer->amount; // amount为负数
            printf("  银行资金减少 %d 元，当前总额 %d 元\n", abs(customer->amount), bank->total_money);
        } else {
            // 资金不足，将客户加入第二个队列
            printf("  银行资金不足，客户加入等待队列\n");
            enqueue(&bank->queue2, customer);
            return; // 不释放客户内存，因为客户仍在等待
        }
    }
    
    free(customer);
    free(event);
}

// 处理第二个队列中的客户
void process_queue2(BankSystem* bank) {
    if (is_queue_empty(&bank->queue2)) {
        return;
    }
    
    // 记录处理前的银行资金
    int money_before = bank->total_money;
    int processed_count = 0;
    
    printf("开始处理等待队列中的客户...\n");
    
    // 创建临时队列存储无法处理的客户
    Queue temp_queue;
    init_queue(&temp_queue);
    
    Customer* customer = dequeue(&bank->queue2);
    while (customer != NULL) {
        // 检查银行是否有足够资金处理该客户
        if (bank->total_money >= abs(customer->amount)) {
            // 可以处理
            bank->total_money += customer->amount;
            int stay_time = bank->current_time - customer->arrive_time;
            bank->total_wait_time += stay_time;
            processed_count++;
            
            printf("  时间 %d: 等待客户完成交易，交易金额 %d 元，总逗留时间 %d 分钟\n", 
                   bank->current_time, customer->amount, stay_time);
            printf("  银行资金减少 %d 元，当前总额 %d 元\n", abs(customer->amount), bank->total_money);
            
            free(customer);
        } else {
            // 仍然无法处理，放回临时队列
            enqueue(&temp_queue, customer);
        }
        
        // 检查是否应该停止处理
        if (bank->total_money <= money_before || processed_count > 100) { // 防止无限循环
            // 将当前客户重新放回队列
            if (customer != NULL) {
                enqueue(&temp_queue, customer);
            }
            break;
        }
        
        customer = dequeue(&bank->queue2);
    }
    
    // 将未处理的客户移回等待队列
    while (!is_queue_empty(&temp_queue)) {
        enqueue(&bank->queue2, dequeue(&temp_queue));
    }
    
    printf("等待队列处理完成\n");
}

// 运行模拟
void run_simulation(BankSystem* bank) {
    printf("银行模拟开始\n");
    printf("初始资金: %d 元\n", bank->total_money);
    printf("营业时间: %d 分钟\n", bank->close_time);
    printf("========================\n");
    
    while (bank->event_list != NULL) {
        Event* event = get_next_event(&bank->event_list);
        if (event == NULL) {
            break;
        }
        
        bank->current_time = event->occur_time;
        
        // 如果已经超过关门时间，结束营业
        if (bank->current_time >= bank->close_time) {
            printf("时间 %d: 银行关门，营业结束\n", bank->current_time);
            free(event);
            break;
        }
        
        if (event->event_type == 0) {
            // 到达事件
            handle_arrive_event(bank, event);
        } else {
            // 离开事件
            handle_leave_event(bank, event);
        }
    }
    
    // 处理完所有事件后，处理队列1中剩余的客户
    printf("========================\n");
    printf("处理剩余客户...\n");
    
    while (!is_queue_empty(&bank->queue1)) {
        Customer* customer = dequeue(&bank->queue1);
        int stay_time = bank->current_time - customer->arrive_time;
        bank->total_wait_time += stay_time;
        printf("时间 %d: 客户离开（营业结束），总逗留时间 %d 分钟\n", 
               bank->current_time, stay_time);
        free(customer);
    }
}

// 打印统计信息
void print_statistics(BankSystem* bank) {
    printf("========================\n");
    printf("模拟结束，统计信息:\n");
    printf("总客户数: %d\n", bank->total_customers);
    printf("总等待时间: %d 分钟\n", bank->total_wait_time);
    
    if (bank->total_customers > 0) {
        double avg_stay_time = (double)bank->total_wait_time / bank->total_customers;
        printf("平均逗留时间: %.2f 分钟\n", avg_stay_time);
    }
    
    printf("最终银行资金: %d 元\n", bank->total_money);
    printf("剩余等待队列客户数: %d\n", 
           is_queue_empty(&bank->queue2) ? 0 : 1); // 简化处理
}

// 释放队列中的所有客户
void free_all_customers(Queue* q) {
    while (!is_queue_empty(q)) {
        Customer* customer = dequeue(q);
        free(customer);
    }
}

// 释放所有事件
void free_all_events(Event** event_list) {
    while (*event_list != NULL) {
        Event* event = get_next_event(event_list);
        if (event->customer != NULL) {
            free(event->customer);
        }
        free(event);
    }
}