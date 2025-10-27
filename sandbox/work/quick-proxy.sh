#!/bin/bash

# 快速Git代理切换脚本

PROXY_ADDR="127.0.0.1"
PROXY_PORT="7897"

# 检查当前是否启用了代理
is_proxy_enabled() {
    http_proxy=$(git config --global --get http.proxy)
    if [ -n "$http_proxy" ]; then
        return 0  # 已启用
    else
        return 1  # 未启用
    fi
}

# 切换代理状态
toggle_proxy() {
    if is_proxy_enabled; then
        # 禁用代理
        git config --global --unset http.proxy
        git config --global --unset https.proxy
        echo "Git代理已禁用"
    else
        # 启用代理
        git config --global http.proxy "http://$PROXY_ADDR:$PROXY_PORT"
        git config --global https.proxy "http://$PROXY_ADDR:$PROXY_PORT"
        echo "Git代理已启用: http://$PROXY_ADDR:$PROXY_PORT"
    fi
}

# 显示当前状态
show_status() {
    if is_proxy_enabled; then
        http_proxy=$(git config --global --get http.proxy)
        echo "当前状态: 已启用 ($http_proxy)"
    else
        echo "当前状态: 未启用"
    fi
}

# 根据参数执行操作
case "$1" in
    toggle)
        toggle_proxy
        ;;
    status|"")
        show_status
        ;;
    *)
        echo "用法: $0 [toggle|status]"
        echo "  toggle  切换代理状态"
        echo "  status  显示当前状态(默认)"
        ;;
esac