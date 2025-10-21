@echo off
echo 正在清理旧的构建目录...
if exist build rmdir /s /q build

echo 正在创建新的构建目录...
mkdir build

echo 正在进入构建目录...
cd build

echo 正在配置项目...
cmake ..

echo 正在构建项目...
cmake --build . --config Debug

echo 构建完成！
pause