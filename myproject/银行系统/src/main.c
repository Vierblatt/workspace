/**
 * @file main.c
 * @brief 银行模拟系统主程序
 * @author Yang Hengyi
 * @version 1.0
 * @date 2025-11-27
 */

#include "../include/bank_simulation.h"
#include <unistd.h>

/**
 * @brief 打印帮助信息
 */
void print_help(const char* program_name) {
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("  -h, --help              Show this help message\n");
    printf("  -c, --config <file>     Specify configuration file\n");
    printf("  -m, --money <amount>    Set initial money (default: 10000)\n");
    printf("  -t, --time <minutes>    Set close time in minutes (default: 600)\n");
    printf("  -l, --log               Enable logging\n");
    printf("  -v, --verbose           Enable verbose logging (DEBUG level)\n");
    printf("\n");
    printf("Examples:\n");
    printf("  %s                          # Run with default settings\n", program_name);
    printf("  %s -m 5000 -t 300          # Run with 5000 initial money and 300 minutes\n", program_name);
    printf("  %s -c config.ini           # Run with configuration file\n", program_name);
    printf("  %s -l -v                   # Run with verbose logging\n", program_name);
}

/**
 * @brief 创建默认配置文件
 */
int create_default_config(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        return BANK_ERROR_FILE_OP;
    }

    fprintf(fp, "# 银行模拟系统配置文件\n");
    fprintf(fp, "\n");
    fprintf(fp, "# 初始资金\n");
    fprintf(fp, "initial_money = 10000\n");
    fprintf(fp, "\n");
    fprintf(fp, "# 营业时间（分钟）\n");
    fprintf(fp, "close_time = 600\n");
    fprintf(fp, "\n");
    fprintf(fp, "# 是否启用日志\n");
    fprintf(fp, "enable_log = 1\n");
    fprintf(fp, "\n");
    fprintf(fp, "# 日志级别 (0=DEBUG, 1=INFO, 2=WARN, 3=ERROR)\n");
    fprintf(fp, "log_level = 1\n");
    fprintf(fp, "\n");
    fprintf(fp, "# 日志文件路径\n");
    fprintf(fp, "log_file = bank_simulation.log\n");

    fclose(fp);
    return BANK_SUCCESS;
}

/**
 * @brief 主函数
 */
int main(int argc, char* argv[]) {
    // 设置随机数种子
    srand((unsigned int)time(NULL));

    // 初始化默认配置
    BankConfig config = {
        .initial_money = DEFAULT_INITIAL_MONEY,
        .close_time = DEFAULT_CLOSE_TIME,
        .enable_log = 0,
        .log_level = LOG_LEVEL_INFO,
        .log_file = ""
    };

    // 解析命令行参数
    int opt;
    while ((opt = getopt(argc, argv, "hc:m:t:lv")) != -1) {
        switch (opt) {
            case 'h':
                print_help(argv[0]);
                return 0;
            case 'c':
                if (load_config(&config, optarg) != BANK_SUCCESS) {
                    fprintf(stderr, "Error: Failed to load config file %s\n", optarg);
                    return 1;
                }
                break;
            case 'm':
                config.initial_money = atoi(optarg);
                break;
            case 't':
                config.close_time = atoi(optarg);
                break;
            case 'l':
                config.enable_log = 1;
                if (strlen(config.log_file) == 0) {
                    strncpy(config.log_file, "bank_simulation.log", sizeof(config.log_file) - 1);
                }
                break;
            case 'v':
                config.log_level = LOG_LEVEL_DEBUG;
                break;
            default:
                print_help(argv[0]);
                return 1;
        }
    }

    // 如果启用了日志但没有指定日志文件，使用默认文件名
    if (config.enable_log && strlen(config.log_file) == 0) {
        strncpy(config.log_file, "bank_simulation.log", sizeof(config.log_file) - 1);
    }

    // 创建默认配置文件（如果不存在）
    if (access("config.ini", F_OK) == -1) {
        if (create_default_config("config.ini") != BANK_SUCCESS) {
            fprintf(stderr, "Warning: Failed to create default config file\n");
        }
    }

    printf("Bank Simulation System\n");
    printf("======================\n");
    printf("Initial money: %d\n", config.initial_money);
    printf("Close time: %d minutes\n", config.close_time);
    if (config.enable_log) {
        printf("Logging enabled, level: %d, file: %s\n", config.log_level, config.log_file);
    }
    printf("\n");

    // 初始化银行系统
    BankSystem bank;
    if (init_bank_system(&bank, &config) != BANK_SUCCESS) {
        fprintf(stderr, "Error: Failed to initialize bank system\n");
        return 1;
    }

    // 运行模拟
    printf("Running simulation...\n");
    if (run_simulation(&bank) != BANK_SUCCESS) {
        fprintf(stderr, "Error: Failed to run simulation\n");
        destroy_bank_system(&bank);
        return 1;
    }

    // 打印统计信息
    if (print_statistics(&bank) != BANK_SUCCESS) {
        fprintf(stderr, "Error: Failed to print statistics\n");
        destroy_bank_system(&bank);
        return 1;
    }

    // 销毁银行系统
    if (destroy_bank_system(&bank) != BANK_SUCCESS) {
        fprintf(stderr, "Error: Failed to destroy bank system\n");
        return 1;
    }

    return 0;
}