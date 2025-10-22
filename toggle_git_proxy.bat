@echo off
chcp 65001 > nul
title Git代理切换工具
echo 正在检查Git代理状态...
for /f "tokens=*" %%i in ('git config --global --get http.proxy 2^>nul') do set current_proxy=%%i
if "%current_proxy%"=="" (
  echo 正在设置Git代理...
  git config --global http.proxy http://127.0.0.1:7890
  git config --global https.proxy http://127.0.0.1:7890
  echo ✅ Git代理已开启
) else (
  echo 正在移除Git代理...
  git config --global --unset http.proxy
  git config --global --unset https.proxy
  echo ✅ Git代理已关闭
)
echo.
echo 当前Git代理状态：
for /f "tokens=*" %%i in ('git config --global --get http.proxy 2^>nul') do set http_proxy=%%i
for /f "tokens=*" %%i in ('git config --global --get https.proxy 2^>nul') do set https_proxy=%%i
if "%http_proxy%"=="" (
  echo HTTP代理: 未设置
) else (
  echo HTTP代理: %http_proxy%
)
if "%https_proxy%"=="" (
  echo HTTPS代理: 未设置
) else (
  echo HTTPS代理: %https_proxy%
)
echo.
echo 按任意键退出...
pause > nul
