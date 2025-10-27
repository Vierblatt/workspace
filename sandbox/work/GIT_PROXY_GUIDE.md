# Git代理管理使用指南

## 概述

本指南介绍了如何使用提供的脚本管理Git代理设置，以便在不同网络环境下顺利访问GitHub。

## 脚本说明

### 1. git-proxy-manager.sh - 基础代理管理脚本

#### 使用方法：
```bash
./git-proxy-manager.sh [选项]
```

#### 选项：
- `enable` - 启用Git代理
- `disable` - 禁用Git代理
- `status` - 显示当前代理状态
- `help` - 显示帮助信息

#### 示例：
```bash
# 启用代理
./git-proxy-manager.sh enable

# 查看代理状态
./git-proxy-manager.sh status

# 禁用代理
./git-proxy-manager.sh disable
```

### 2. auto-git-proxy.sh - 自动代理管理脚本

#### 使用方法：
```bash
./auto-git-proxy.sh [选项]
```

#### 选项：
- `auto` - 自动检测网络连接并设置代理
- `enable` - 手动启用Git代理
- `disable` - 手动禁用Git代理
- `status` - 显示当前代理状态
- `help` - 显示帮助信息

#### 示例：
```bash
# 自动检测并设置代理
./auto-git-proxy.sh auto

# 查看代理状态
./auto-git-proxy.sh status
```

### 3. quick-proxy.sh - 快速切换脚本

#### 使用方法：
```bash
./quick-proxy.sh [选项]
```

#### 选项：
- `toggle` - 切换代理启用/禁用状态
- `status` - 显示当前代理状态

#### 示例：
```bash
# 切换代理状态
./quick-proxy.sh toggle

# 查看当前状态
./quick-proxy.sh
```

## 常见使用场景

### 1. 在公司/学校网络环境下（需要代理）
```bash
./quick-proxy.sh toggle  # 启用代理
git push origin main     # 推送代码
```

### 2. 在家庭网络环境下（不需要代理）
```bash
./quick-proxy.sh toggle  # 禁用代理
git push origin main     # 直接推送代码
```

### 3. 自动检测网络环境
```bash
./auto-git-proxy.sh auto  # 自动检测并设置代理
git push origin main      # 根据网络环境自动选择是否使用代理
```

## 注意事项

1. 这些脚本使用全局Git配置，会影响所有Git仓库
2. 如果您使用SSH方式连接GitHub，这些代理设置不会生效
3. 请确保代理服务器地址和端口正确（当前设置为127.0.0.1:7897）
4. 如果代理设置后仍然无法连接，请检查代理服务器是否正常运行

## 代理配置修改

如果需要修改代理地址或端口，请编辑相应的脚本文件：
- 修改 `PROXY_ADDR` 变量来更改代理地址
- 修改 `PROXY_PORT` 变量来更改代理端口

## 故障排除

### 1. 推送时提示认证失败
- 确保GitHub用户名和密码（或个人访问令牌）正确
- 如果启用了双因素认证，请使用个人访问令牌而不是密码

### 2. 代理设置后仍然无法连接
- 检查代理服务器是否正常运行
- 确认代理端口是否正确
- 尝试使用 `./auto-git-proxy.sh auto` 自动检测网络环境

### 3. 想要恢复默认设置
```bash
./git-proxy-manager.sh disable  # 禁用代理
```

## 附加信息

### 设置SSH密钥（推荐）
为了避免每次输入用户名和密码，建议设置SSH密钥：

1. 生成SSH密钥：
   ```bash
   ssh-keygen -t ed25519 -C "your_email@example.com"
   ```

2. 将SSH密钥添加到ssh-agent：
   ```bash
   eval "$(ssh-agent -s)"
   ssh-add ~/.ssh/id_ed25519
   ```

3. 将SSH密钥添加到GitHub账户：
   - 复制公钥内容：`cat ~/.ssh/id_ed25519.pub`
   - 在GitHub中添加SSH密钥到您的账户设置

4. 更改远程URL为SSH方式：
   ```bash
   git remote set-url origin git@github.com:Vierblatt/workspace.git
   ```