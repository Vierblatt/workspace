#ifndef BANK_SIMULATION_H
#define BANK_SIMULATION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 客户结构体
typedef struct Customer {
    int arrive_time;        // 到达时间
    int duration;           // 服务时间
    int amount;             // 交易金额（正数表示存款，负数表示取款）
    struct Customer* next;
} Customer;

// 事件结构体
typedef struct Event {
    int occur_time;         // 事件发生时间
    int event_type;         // 事件类型（0表示到达事件，1表示离开事件）
    struct Customer* customer; // 相关客户
    struct Event* next;
} Event;

// 队列结构体
typedef struct Queue {
    Customer* front;
    Customer* rear;
} Queue;

// 银行系统结构体
typedef struct BankSystem {
    int total_money;        // 银行总资金
    int current_time;       // 当前时间
    int close_time;         // 关门时间
    Queue queue1;           // 第一个队列（正在等待服务的客户）
    Queue queue2;           // 第二个队列（因资金不足而等待的客户）
    Event* event_list;      // 事件列表
    int total_customers;    // 总客户数
    int total_wait_time;    // 总等待时间
} BankSystem;

// 函数声明
void init_bank_system(BankSystem* bank, int initial_money, int close_time);
void init_queue(Queue* q);
int is_queue_empty(Queue* q);
void enqueue(Queue* q, Customer* customer);
Customer* dequeue(Queue* q);
Customer* queue_front(Queue* q);

void init_event_list(Event** event_list);
void insert_event(Event** event_list, Event* event);
Event* get_next_event(Event** event_list);

void generate_random_customer(BankSystem* bank);
Customer* create_customer(int arrive_time);
void handle_arrive_event(BankSystem* bank, Event* event);
void handle_leave_event(BankSystem* bank, Event* event);
void process_queue2(BankSystem* bank);

void run_simulation(BankSystem* bank);
void print_statistics(BankSystem* bank);

void free_all_customers(Queue* q);
void free_all_events(Event** event_list);

#endif