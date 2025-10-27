#!/bin/bash

# 自动Git代理管理脚本
# 根据网络连接状态自动启用或禁用Git代理

# 代理设置
PROXY_ADDR="127.0.0.1"
PROXY_PORT="7897"
GITHUB_HOST="github.com"

# 检查网络连接
check_connection() {
    echo "正在检查到 $1 的连接..."
    if timeout 5 ping -c 1 "$1" >/dev/null 2>&1; then
        echo "连接正常"
        return 0
    else
        echo "连接失败"
        return 1
    fi
}

# 检查代理连接
check_proxy_connection() {
    echo "正在检查代理连接..."
    if nc -z -w 5 "$PROXY_ADDR" "$PROXY_PORT" 2>/dev/null; then
        echo "代理连接正常"
        return 0
    else
        echo "代理连接失败"
        return 1
    fi
}

# 检查GitHub连接
check_github_connection() {
    echo "正在检查GitHub连接..."
    if timeout 10 curl -s --head https://"$GITHUB_HOST" | head -n 1 | grep "200\|301\|302" >/dev/null 2>&1; then
        echo "GitHub连接正常"
        return 0
    else
        echo "GitHub连接失败"
        return 1
    fi
}

# 启用代理
enable_proxy() {
    echo "正在启用Git代理..."
    git config --global http.proxy "http://$PROXY_ADDR:$PROXY_PORT"
    git config --global https.proxy "http://$PROXY_ADDR:$PROXY_PORT"
    echo "Git代理已启用: http://$PROXY_ADDR:$PROXY_PORT"
}

# 禁用代理
disable_proxy() {
    echo "正在禁用Git代理..."
    git config --global --unset http.proxy 2>/dev/null
    git config --global --unset https.proxy 2>/dev/null
    echo "Git代理已禁用"
}

# 显示当前代理状态
show_status() {
    echo "=== Git代理状态 ==="
    http_proxy=$(git config --global --get http.proxy)
    https_proxy=$(git config --global --get https.proxy)
    
    if [ -z "$http_proxy" ] && [ -z "$https_proxy" ]; then
        echo "代理状态: 未启用"
    else
        echo "代理状态: 已启用"
        echo "HTTP代理:  $http_proxy"
        echo "HTTPS代理: $https_proxy"
    fi
    echo ""
}

# 自动检测并设置代理
auto_detect() {
    echo "=== 自动检测Git代理设置 ==="
    
    # 检查GitHub连接
    if check_github_connection; then
        echo "GitHub可以直接访问，无需代理"
        disable_proxy
    else
        echo "GitHub无法直接访问，检查代理..."
        # 检查代理是否可用
        if check_proxy_connection; then
            echo "代理可用，启用代理"
            enable_proxy
        else
            echo "代理不可用，保持当前设置"
        fi
    fi
}

# 主程序
case "$1" in
    enable)
        enable_proxy
        ;;
    disable)
        disable_proxy
        ;;
    status)
        show_status
        ;;
    auto)
        auto_detect
        ;;
    help|"")
        echo "自动Git代理管理脚本"
        echo "用法: $0 [选项]"
        echo ""
        echo "选项:"
        echo "  enable    启用Git代理"
        echo "  disable   禁用Git代理"
        echo "  status    显示当前代理状态"
        echo "  auto      自动检测并设置代理"
        echo "  help      显示此帮助信息"
        echo ""
        echo "示例:"
        echo "  $0 auto   # 自动检测并设置代理"
        echo "  $0 enable # 手动启用代理"
        ;;
    *)
        echo "未知选项: $1"
        echo "使用 '$0 help' 查看帮助信息"
        exit 1
        ;;
esac