/**
 * @file bank_simulation.c
 * @brief 银行模拟系统实现文件
 * @author Yang Hengyi
 * @version 1.0
 * @date 2025-11-27
 */

#include "../include/bank_simulation.h"
#include <stdarg.h>
#include <math.h>

// 日志级别字符串映射
static const char* log_level_strings[] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR"
};

/**
 * @brief 初始化银行系统
 */
int init_bank_system(BankSystem* bank, const BankConfig* config) {
    if (!bank || !config) {
        return BANK_ERROR_INVALID_PARAM;
    }

    // 初始化银行系统参数
    bank->total_money = config->initial_money;
    bank->current_time = 0;
    bank->close_time = config->close_time;
    bank->total_customers = 0;
    bank->total_wait_time = 0;
    bank->customer_count = 0;
    bank->event_list = NULL;

    // 初始化队列
    if (init_queue(&bank->queue1) != BANK_SUCCESS) {
        return BANK_ERROR_QUEUE_OP;
    }
    
    if (init_queue(&bank->queue2) != BANK_SUCCESS) {
        return BANK_ERROR_QUEUE_OP;
    }

    // 初始化日志
    bank->log_level = config->log_level;
    if (config->enable_log && strlen(config->log_file) > 0) {
        bank->log_fp = fopen(config->log_file, "w");
        if (!bank->log_fp) {
            fprintf(stderr, "Warning: Failed to open log file %s\n", config->log_file);
            bank->log_fp = stdout;
        }
    } else {
        bank->log_fp = NULL;
    }

    // 创建第一个客户到达事件
    Customer* first_customer = create_customer(bank->customer_count++, 0);
    if (!first_customer) {
        return BANK_ERROR_MEMORY_ALLOC;
    }

    Event* first_event = (Event*)malloc(sizeof(Event));
    if (!first_event) {
        destroy_customer(first_customer);
        return BANK_ERROR_MEMORY_ALLOC;
    }

    first_event->occur_time = 0;
    first_event->event_type = EVENT_ARRIVE;
    first_event->customer = first_customer;
    first_event->next = NULL;

    if (insert_event(&bank->event_list, first_event) != BANK_SUCCESS) {
        free(first_event);
        destroy_customer(first_customer);
        return BANK_ERROR_EVENT_OP;
    }

    bank_log(bank, LOG_LEVEL_INFO, "Bank system initialized with initial money: %d, close time: %d", 
             config->initial_money, config->close_time);

    return BANK_SUCCESS;
}

/**
 * @brief 销毁银行系统
 */
int destroy_bank_system(BankSystem* bank) {
    if (!bank) {
        return BANK_ERROR_INVALID_PARAM;
    }

    // 释放所有事件
    while (bank->event_list) {
        Event* event = get_next_event(&bank->event_list);
        if (event) {
            if (event->customer) {
                destroy_customer(event->customer);
            }
            free(event);
        }
    }

    // 释放队列中的所有客户
    Customer* customer;
    while ((customer = dequeue(&bank->queue1)) != NULL) {
        destroy_customer(customer);
    }

    while ((customer = dequeue(&bank->queue2)) != NULL) {
        destroy_customer(customer);
    }

    // 关闭日志文件
    if (bank->log_fp && bank->log_fp != stdout) {
        fclose(bank->log_fp);
    }

    bank_log(bank, LOG_LEVEL_INFO, "Bank system destroyed");
    return BANK_SUCCESS;
}

/**
 * @brief 初始化队列
 */
int init_queue(Queue* q) {
    if (!q) {
        return BANK_ERROR_INVALID_PARAM;
    }
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return BANK_SUCCESS;
}

/**
 * @brief 检查队列是否为空
 */
int is_queue_empty(const Queue* q) {
    if (!q) {
        return 1;
    }
    return q->front == NULL;
}

/**
 * @brief 获取队列大小
 */
int get_queue_size(const Queue* q) {
    if (!q) {
        return 0;
    }
    return q->size;
}

/**
 * @brief 入队
 */
int enqueue(Queue* q, Customer* customer) {
    if (!q || !customer) {
        return BANK_ERROR_INVALID_PARAM;
    }

    customer->next = NULL;

    if (is_queue_empty(q)) {
        q->front = customer;
        q->rear = customer;
    } else {
        q->rear->next = customer;
        q->rear = customer;
    }

    q->size++;
    return BANK_SUCCESS;
}

/**
 * @brief 出队
 */
Customer* dequeue(Queue* q) {
    if (!q || is_queue_empty(q)) {
        return NULL;
    }

    Customer* customer = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    customer->next = NULL;
    q->size--;

    return customer;
}

/**
 * @brief 获取队首元素
 */
Customer* queue_front(const Queue* q) {
    if (!q || is_queue_empty(q)) {
        return NULL;
    }
    return q->front;
}

/**
 * @brief 插入事件（按时间顺序）
 */
int insert_event(Event** event_list, Event* event) {
    if (!event_list || !event) {
        return BANK_ERROR_INVALID_PARAM;
    }

    // 如果事件列表为空或新事件时间早于第一个事件
    if (*event_list == NULL || (*event_list)->occur_time > event->occur_time) {
        event->next = *event_list;
        *event_list = event;
        return BANK_SUCCESS;
    }

    // 查找插入位置
    Event* current = *event_list;
    while (current->next != NULL && current->next->occur_time <= event->occur_time) {
        current = current->next;
    }

    event->next = current->next;
    current->next = event;
    return BANK_SUCCESS;
}

/**
 * @brief 获取下一个事件
 */
Event* get_next_event(Event** event_list) {
    if (!event_list || *event_list == NULL) {
        return NULL;
    }

    Event* event = *event_list;
    *event_list = (*event_list)->next;
    event->next = NULL;
    return event;
}

/**
 * @brief 创建客户
 */
Customer* create_customer(int id, int arrive_time) {
    Customer* customer = (Customer*)malloc(sizeof(Customer));
    if (!customer) {
        return NULL;
    }

    customer->id = id;
    customer->arrive_time = arrive_time;

    // 随机生成服务时间（1-20分钟）
    customer->duration = rand() % (MAX_SERVICE_TIME - MIN_SERVICE_TIME + 1) + MIN_SERVICE_TIME;

    // 随机生成交易金额（-5000到5000元）
    customer->amount = rand() % (MAX_TRANSACTION_AMOUNT - MIN_TRANSACTION_AMOUNT + 1) + MIN_TRANSACTION_AMOUNT;

    customer->next = NULL;

    return customer;
}

/**
 * @brief 销毁客户
 */
int destroy_customer(Customer* customer) {
    if (!customer) {
        return BANK_ERROR_INVALID_PARAM;
    }
    free(customer);
    return BANK_SUCCESS;
}

/**
 * @brief 处理客户到达事件
 */
int handle_arrive_event(BankSystem* bank, Event* event) {
    if (!bank || !event || !event->customer) {
        return BANK_ERROR_INVALID_PARAM;
    }

    Customer* customer = event->customer;

    // 将客户加入第一个队列
    if (enqueue(&bank->queue1, customer) != BANK_SUCCESS) {
        bank_log(bank, LOG_LEVEL_ERROR, "Failed to enqueue customer %d", customer->id);
        destroy_customer(customer);
        free(event);
        return BANK_ERROR_QUEUE_OP;
    }

    bank->total_customers++;

    bank_log(bank, LOG_LEVEL_INFO, "Time %d: Customer %d arrived, transaction amount %d, service time %d", 
             bank->current_time, customer->id, customer->amount, customer->duration);

    // 生成下一个客户到达事件
    if (bank->current_time < bank->close_time) {
        // 下一个客户到达的时间间隔（1-10分钟）
        int interval = rand() % (MAX_ARRIVAL_INTERVAL - MIN_ARRIVAL_INTERVAL + 1) + MIN_ARRIVAL_INTERVAL;
        int next_arrive_time = bank->current_time + interval;

        if (next_arrive_time < bank->close_time) {
            Customer* next_customer = create_customer(bank->customer_count++, next_arrive_time);
            if (next_customer) {
                Event* next_event = (Event*)malloc(sizeof(Event));
                if (next_event) {
                    next_event->occur_time = next_arrive_time;
                    next_event->event_type = EVENT_ARRIVE;
                    next_event->customer = next_customer;
                    next_event->next = NULL;

                    if (insert_event(&bank->event_list, next_event) != BANK_SUCCESS) {
                        bank_log(bank, LOG_LEVEL_WARN, "Failed to insert next arrival event");
                        destroy_customer(next_customer);
                        free(next_event);
                        // 不返回错误，因为主流程仍然可以继续
                    }
                } else {
                    destroy_customer(next_customer);
                }
            }
        }
    }

    free(event);
    return BANK_SUCCESS;
}

/**
 * @brief 处理客户离开事件
 */
int handle_leave_event(BankSystem* bank, Event* event) {
    if (!bank || !event || !event->customer) {
        return BANK_ERROR_INVALID_PARAM;
    }

    Customer* customer = event->customer;

    // 计算客户在银行的总逗留时间
    int stay_time = bank->current_time - customer->arrive_time;
    bank->total_wait_time += stay_time;

    bank_log(bank, LOG_LEVEL_INFO, "Time %d: Customer %d leaving, transaction amount %d, total stay time %d", 
             bank->current_time, customer->id, customer->amount, stay_time);

    // 如果是存款或还款业务（金额为正）
    if (customer->amount > 0) {
        bank->total_money += customer->amount;
        bank_log(bank, LOG_LEVEL_INFO, "  Bank money increased by %d, current total %d", 
                 customer->amount, bank->total_money);

        // 处理第二个队列中等待的客户
        process_queue2(bank);
    } 
    // 如果是取款或借款业务（金额为负）
    else {
        // 检查银行是否有足够资金
        if (bank->total_money >= abs(customer->amount)) {
            bank->total_money += customer->amount; // amount为负数
            bank_log(bank, LOG_LEVEL_INFO, "  Bank money decreased by %d, current total %d", 
                     abs(customer->amount), bank->total_money);
        } else {
            // 资金不足，将客户加入第二个队列
            bank_log(bank, LOG_LEVEL_INFO, "  Insufficient funds, customer %d added to waiting queue", customer->id);
            if (enqueue(&bank->queue2, customer) != BANK_SUCCESS) {
                bank_log(bank, LOG_LEVEL_ERROR, "Failed to enqueue customer %d to waiting queue", customer->id);
                destroy_customer(customer);
                free(event);
                return BANK_ERROR_QUEUE_OP;
            }
            free(event);
            return BANK_SUCCESS;
        }
    }

    destroy_customer(customer);
    free(event);
    return BANK_SUCCESS;
}

/**
 * @brief 处理第二个队列中的客户
 */
int process_queue2(BankSystem* bank) {
    if (!bank) {
        return BANK_ERROR_INVALID_PARAM;
    }
    
    if (is_queue_empty(&bank->queue2)) {
        return BANK_SUCCESS;
    }

    bank_log(bank, LOG_LEVEL_DEBUG, "Processing waiting queue customers");

    // 记录处理前的银行资金
    int money_before = bank->total_money;
    int processed_count = 0;

    // 创建临时队列存储无法处理的客户
    Queue temp_queue;
    if (init_queue(&temp_queue) != BANK_SUCCESS) {
        bank_log(bank, LOG_LEVEL_ERROR, "Failed to initialize temp queue");
        return BANK_ERROR_QUEUE_OP;
    }

    Customer* customer = dequeue(&bank->queue2);
    while (customer != NULL) {
        // 检查银行是否有足够资金处理该客户
        if (bank->total_money >= abs(customer->amount)) {
            // 可以处理
            bank->total_money += customer->amount;
            int stay_time = bank->current_time - customer->arrive_time;
            bank->total_wait_time += stay_time;
            processed_count++;

            bank_log(bank, LOG_LEVEL_INFO, "  Time %d: Waiting customer %d completed transaction, amount %d, total stay time %d", 
                     bank->current_time, customer->id, customer->amount, stay_time);
            bank_log(bank, LOG_LEVEL_INFO, "  Bank money changed by %d, current total %d", 
                     customer->amount, bank->total_money);

            destroy_customer(customer);
        } else {
            // 仍然无法处理，放回临时队列
            if (enqueue(&temp_queue, customer) != BANK_SUCCESS) {
                bank_log(bank, LOG_LEVEL_ERROR, "Failed to enqueue customer %d to temp queue", customer->id);
                destroy_customer(customer);
            }
        }

        // 检查是否应该停止处理
        if (bank->total_money <= money_before || processed_count > 100) {
            // 将当前客户重新放回队列
            if (customer != NULL && enqueue(&temp_queue, customer) != BANK_SUCCESS) {
                bank_log(bank, LOG_LEVEL_ERROR, "Failed to enqueue customer %d to temp queue", customer->id);
                destroy_customer(customer);
            }
            break;
        }

        customer = dequeue(&bank->queue2);
    }

    // 将未处理的客户移回等待队列
    while (!is_queue_empty(&temp_queue)) {
        Customer* temp_customer = dequeue(&temp_queue);
        if (temp_customer && enqueue(&bank->queue2, temp_customer) != BANK_SUCCESS) {
            bank_log(bank, LOG_LEVEL_ERROR, "Failed to enqueue customer %d back to waiting queue", temp_customer->id);
            destroy_customer(temp_customer);
        }
    }

    bank_log(bank, LOG_LEVEL_DEBUG, "Finished processing waiting queue");
    return BANK_SUCCESS;
}

/**
 * @brief 运行模拟
 */
int run_simulation(BankSystem* bank) {
    if (!bank) {
        return BANK_ERROR_INVALID_PARAM;
    }

    bank_log(bank, LOG_LEVEL_INFO, "Bank simulation started");
    bank_log(bank, LOG_LEVEL_INFO, "Initial money: %d", bank->total_money);
    bank_log(bank, LOG_LEVEL_INFO, "Close time: %d", bank->close_time);
    bank_log(bank, LOG_LEVEL_INFO, "========================");

    while (bank->event_list != NULL) {
        Event* event = get_next_event(&bank->event_list);
        if (event == NULL) {
            break;
        }

        bank->current_time = event->occur_time;

        // 如果已经超过关门时间，结束营业
        if (bank->current_time >= bank->close_time) {
            bank_log(bank, LOG_LEVEL_INFO, "Time %d: Bank closed, business ended", bank->current_time);
            if (event->customer) {
                destroy_customer(event->customer);
            }
            free(event);
            break;
        }

        int result;
        if (event->event_type == EVENT_ARRIVE) {
            // 到达事件
            result = handle_arrive_event(bank, event);
        } else {
            // 离开事件
            result = handle_leave_event(bank, event);
        }
        
        // 如果处理事件时出现严重错误，停止模拟
        if (result != BANK_SUCCESS && result != BANK_ERROR_EVENT_OP) {
            bank_log(bank, LOG_LEVEL_ERROR, "Error occurred during event processing, stopping simulation");
            return result;
        }
    }

    // 处理完所有事件后，处理队列1中剩余的客户
    bank_log(bank, LOG_LEVEL_INFO, "========================");
    bank_log(bank, LOG_LEVEL_INFO, "Processing remaining customers");

    while (!is_queue_empty(&bank->queue1)) {
        Customer* customer = dequeue(&bank->queue1);
        if (customer) {
            int stay_time = bank->current_time - customer->arrive_time;
            bank->total_wait_time += stay_time;
            bank_log(bank, LOG_LEVEL_INFO, "Time %d: Customer %d left (business ended), total stay time %d", 
                     bank->current_time, customer->id, stay_time);
            destroy_customer(customer);
        }
    }

    return BANK_SUCCESS;
}

/**
 * @brief 打印统计信息
 */
int print_statistics(const BankSystem* bank) {
    if (!bank) {
        return BANK_ERROR_INVALID_PARAM;
    }

    printf("========================\n");
    printf("Simulation completed, statistics:\n");
    printf("Total customers: %d\n", bank->total_customers);
    printf("Total wait time: %lld minutes\n", bank->total_wait_time);

    if (bank->total_customers > 0) {
        double avg_stay_time = (double)bank->total_wait_time / bank->total_customers;
        printf("Average stay time: %.2f minutes\n", avg_stay_time);
    }

    printf("Final bank money: %d yuan\n", bank->total_money);
    printf("Remaining customers in waiting queue: %d\n", get_queue_size(&bank->queue2));
    return BANK_SUCCESS;
}

/**
 * @brief 写日志
 */
int bank_log(const BankSystem* bank, LogLevel level, const char* format, ...) {
    if (!bank || level < bank->log_level) {
        return BANK_SUCCESS;
    }

    // 如果没有启用日志，直接返回
    if (!bank->log_fp) {
        return BANK_SUCCESS;
    }

    // 获取当前时间
    time_t now;
    time(&now);
    struct tm* local_time = localtime(&now);

    // 写入日志级别和时间
    fprintf(bank->log_fp, "[%04d-%02d-%02d %02d:%02d:%02d][%s] ", 
            local_time->tm_year + 1900,
            local_time->tm_mon + 1,
            local_time->tm_mday,
            local_time->tm_hour,
            local_time->tm_min,
            local_time->tm_sec,
            log_level_strings[level]);

    // 写入日志内容
    va_list args;
    va_start(args, format);
    vfprintf(bank->log_fp, format, args);
    va_end(args);

    fprintf(bank->log_fp, "\n");
    fflush(bank->log_fp);
    return BANK_SUCCESS;
}

/**
 * @brief 加载配置文件
 */
int load_config(BankConfig* config, const char* filename) {
    if (!config || !filename) {
        return BANK_ERROR_INVALID_PARAM;
    }

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        return BANK_ERROR_FILE_OP;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), fp)) {
        // 跳过注释和空行
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') {
            continue;
        }

        char key[MAX_LINE_LENGTH];
        char value[MAX_LINE_LENGTH];

        if (sscanf(line, "%s = %s", key, value) == 2) {
            if (strcmp(key, "initial_money") == 0) {
                config->initial_money = atoi(value);
            } else if (strcmp(key, "close_time") == 0) {
                config->close_time = atoi(value);
            } else if (strcmp(key, "enable_log") == 0) {
                config->enable_log = atoi(value);
            } else if (strcmp(key, "log_level") == 0) {
                config->log_level = (LogLevel)atoi(value);
            } else if (strcmp(key, "log_file") == 0) {
                strncpy(config->log_file, value, sizeof(config->log_file) - 1);
                config->log_file[sizeof(config->log_file) - 1] = '\0';
            }
        }
    }

    fclose(fp);
    return BANK_SUCCESS;
}