/**
 * @file bank_simulation.h
 * @brief 银行模拟系统头文件
 * @author Yang Hengyi
 * @version 1.0
 * @date 2025-11-27
 */

#ifndef BANK_SIMULATION_H
#define BANK_SIMULATION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

// 常量定义
#define MAX_LINE_LENGTH 1024
#define DEFAULT_INITIAL_MONEY 10000
#define DEFAULT_CLOSE_TIME 600
#define MIN_SERVICE_TIME 1
#define MAX_SERVICE_TIME 20
#define MIN_ARRIVAL_INTERVAL 1
#define MAX_ARRIVAL_INTERVAL 10
#define MIN_TRANSACTION_AMOUNT -5000
#define MAX_TRANSACTION_AMOUNT 5000

// 错误码定义
#define BANK_SUCCESS 0
#define BANK_ERROR_INVALID_PARAM -1
#define BANK_ERROR_MEMORY_ALLOC -2
#define BANK_ERROR_FILE_OP -3
#define BANK_ERROR_QUEUE_OP -4
#define BANK_ERROR_EVENT_OP -5

// 事件类型枚举
typedef enum {
    EVENT_ARRIVE = 0,  // 客户到达事件
    EVENT_LEAVE = 1    // 客户离开事件
} EventType;

// 客户业务类型枚举
typedef enum {
    BUSINESS_WITHDRAW = 0,  // 取款/借款
    BUSINESS_DEPOSIT = 1    // 存款/还款
} BusinessType;

// 日志级别枚举
typedef enum {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_ERROR = 3
} LogLevel;

// 客户结构体
typedef struct Customer {
    int id;                 // 客户ID
    int arrive_time;        // 到达时间
    int duration;           // 服务时间
    int amount;             // 交易金额（正数表示存款，负数表示取款）
    struct Customer* next;  // 链表指针
} Customer;

// 事件结构体
typedef struct Event {
    int occur_time;              // 事件发生时间
    EventType event_type;        // 事件类型
    struct Customer* customer;   // 相关客户
    struct Event* next;          // 链表指针
} Event;

// 队列结构体
typedef struct Queue {
    Customer* front;  // 队首指针
    Customer* rear;   // 队尾指针
    int size;         // 队列大小
} Queue;

// 银行系统配置结构体
typedef struct BankConfig {
    int initial_money;      // 初始资金
    int close_time;         // 关门时间
    int enable_log;         // 是否启用日志
    LogLevel log_level;     // 日志级别
    char log_file[256];     // 日志文件路径
} BankConfig;

// 银行系统结构体
typedef struct BankSystem {
    int total_money;        // 银行总资金
    int current_time;       // 当前时间
    int close_time;         // 关门时间
    int customer_count;     // 客户计数器
    Queue queue1;           // 第一个队列（正在等待服务的客户）
    Queue queue2;           // 第二个队列（因资金不足而等待的客户）
    Event* event_list;      // 事件列表
    int total_customers;    // 总客户数
    long long total_wait_time;  // 总等待时间
    FILE* log_fp;           // 日志文件指针
    LogLevel log_level;     // 日志级别
} BankSystem;

// 函数声明

/**
 * @brief 初始化银行系统
 * @param bank 银行系统指针
 * @param config 配置信息
 * @return 成功返回BANK_SUCCESS，失败返回错误码
 */
int init_bank_system(BankSystem* bank, const BankConfig* config);

/**
 * @brief 销毁银行系统
 * @param bank 银行系统指针
 * @return 成功返回BANK_SUCCESS，失败返回错误码
 */
int destroy_bank_system(BankSystem* bank);

/**
 * @brief 初始化队列
 * @param q 队列指针
 * @return 成功返回BANK_SUCCESS，失败返回错误码
 */
int init_queue(Queue* q);

/**
 * @brief 检查队列是否为空
 * @param q 队列指针
 * @return 空返回1，非空返回0
 */
int is_queue_empty(const Queue* q);

/**
 * @brief 获取队列大小
 * @param q 队列指针
 * @return 队列大小
 */
int get_queue_size(const Queue* q);

/**
 * @brief 入队
 * @param q 队列指针
 * @param customer 客户指针
 * @return 成功返回BANK_SUCCESS，失败返回错误码
 */
int enqueue(Queue* q, Customer* customer);

/**
 * @brief 出队
 * @param q 队列指针
 * @return 客户指针，失败返回NULL
 */
Customer* dequeue(Queue* q);

/**
 * @brief 获取队首元素
 * @param q 队列指针
 * @return 客户指针，失败返回NULL
 */
Customer* queue_front(const Queue* q);

/**
 * @brief 插入事件（按时间顺序）
 * @param event_list 事件列表指针的指针
 * @param event 事件指针
 * @return 成功返回BANK_SUCCESS，失败返回错误码
 */
int insert_event(Event** event_list, Event* event);

/**
 * @brief 获取下一个事件
 * @param event_list 事件列表指针的指针
 * @return 事件指针，失败返回NULL
 */
Event* get_next_event(Event** event_list);

/**
 * @brief 创建客户
 * @param id 客户ID
 * @param arrive_time 到达时间
 * @return 客户指针，失败返回NULL
 */
Customer* create_customer(int id, int arrive_time);

/**
 * @brief 销毁客户
 * @param customer 客户指针
 * @return 成功返回BANK_SUCCESS，失败返回错误码
 */
int destroy_customer(Customer* customer);

/**
 * @brief 处理客户到达事件
 * @param bank 银行系统指针
 * @param event 事件指针
 * @return 成功返回BANK_SUCCESS，失败返回错误码
 */
int handle_arrive_event(BankSystem* bank, Event* event);

/**
 * @brief 处理客户离开事件
 * @param bank 银行系统指针
 * @param event 事件指针
 * @return 成功返回BANK_SUCCESS，失败返回错误码
 */
int handle_leave_event(BankSystem* bank, Event* event);

/**
 * @brief 处理等待队列中的客户
 * @param bank 银行系统指针
 * @return 成功返回BANK_SUCCESS，失败返回错误码
 */
int process_queue2(BankSystem* bank);

/**
 * @brief 运行模拟
 * @param bank 银行系统指针
 * @return 成功返回BANK_SUCCESS，失败返回错误码
 */
int run_simulation(BankSystem* bank);

/**
 * @brief 打印统计信息
 * @param bank 银行系统指针
 * @return 成功返回BANK_SUCCESS，失败返回错误码
 */
int print_statistics(const BankSystem* bank);

/**
 * @brief 写日志
 * @param bank 银行系统指针
 * @param level 日志级别
 * @param format 格式化字符串
 * @param ... 可变参数
 * @return 成功返回BANK_SUCCESS，失败返回错误码
 */
int bank_log(const BankSystem* bank, LogLevel level, const char* format, ...);

/**
 * @brief 加载配置文件
 * @param config 配置结构体指针
 * @param filename 配置文件名
 * @return 成功返回BANK_SUCCESS，失败返回错误码
 */
int load_config(BankConfig* config, const char* filename);

#ifdef __cplusplus
}
#endif

#endif // BANK_SIMULATION_H