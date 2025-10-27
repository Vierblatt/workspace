@echo off
echo 正在配置Git代理（端口7890）...
git config --global http.proxy http://127.0.0.1:7890
git config --global https.proxy https://127.0.0.1:7890
echo 配置完成！现在可尝试连接GitHub仓库。
pause