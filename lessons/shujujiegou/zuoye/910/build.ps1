Write-Host "正在清理旧的构建目录..." -ForegroundColor Green
if (Test-Path build) {
    Remove-Item build -Recurse -Force
}

Write-Host "正在创建新的构建目录..." -ForegroundColor Green
New-Item -ItemType Directory -Name build | Out-Null

Write-Host "正在进入构建目录..." -ForegroundColor Green
Set-Location build

Write-Host "正在配置项目..." -ForegroundColor Green
cmake ..

Write-Host "正在构建项目..." -ForegroundColor Green
cmake --build . --config Debug

Write-Host "构建完成！" -ForegroundColor Green