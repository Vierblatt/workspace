#!/bin/bash

# Git代理管理脚本

# 代理设置
PROXY_ADDR="127.0.0.1"
PROXY_PORT="7897"

# 显示当前代理设置
show_proxy() {
    echo "=== 当前Git代理设置 ==="
    http_proxy=$(git config --global --get http.proxy)
    https_proxy=$(git config --global --get https.proxy)
    
    if [ -z "$http_proxy" ] && [ -z "$https_proxy" ]; then
        echo "未设置代理"
    else
        echo "HTTP代理:  $http_proxy"
        echo "HTTPS代理: $https_proxy"
    fi
    echo ""
}

# 启用代理
enable_proxy() {
    echo "正在设置Git代理..."
    git config --global http.proxy "http://$PROXY_ADDR:$PROXY_PORT"
    git config --global https.proxy "http://$PROXY_ADDR:$PROXY_PORT"
    echo "Git代理已设置为 http://$PROXY_ADDR:$PROXY_PORT"
    echo ""
}

# 禁用代理
disable_proxy() {
    echo "正在移除Git代理设置..."
    git config --global --unset http.proxy 2>/dev/null
    git config --global --unset https.proxy 2>/dev/null
    echo "Git代理已移除"
    echo ""
}

# 显示帮助信息
show_help() {
    echo "Git代理管理脚本"
    echo "用法: $0 [选项]"
    echo ""
    echo "选项:"
    echo "  enable    启用Git代理"
    echo "  disable   禁用Git代理"
    echo "  status    显示当前代理状态"
    echo "  help      显示此帮助信息"
    echo ""
}

# 主程序逻辑
case "$1" in
    enable)
        enable_proxy
        ;;
    disable)
        disable_proxy
        ;;
    status)
        show_proxy
        ;;
    help|"")
        show_help
        ;;
    *)
        echo "未知选项: $1"
        show_help
        exit 1
        ;;
esac