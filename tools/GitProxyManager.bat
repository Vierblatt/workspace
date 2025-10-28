@echo off
chcp 65001 >nul

title Git Proxy Manager

echo.
echo Git Proxy Manager
echo =================
echo 1. Set proxy (port 7890)
echo 2. Unset proxy
echo 3. Show current proxy
echo 4. Exit
echo =================
echo.

choice /c 1234 /m "Select option"
set choice=%errorlevel%

if %choice%==1 goto set_proxy
if %choice%==2 goto unset_proxy
if %choice%==3 goto show_proxy
if %choice%==4 goto end

:set_proxy
echo.
echo Setting Git proxy to localhost:7890
git config --global http.proxy http://127.0.0.1:7890
git config --global https.proxy https://127.0.0.1:7890
echo Proxy has been set.
goto end

:unset_proxy
echo.
echo Unsetting Git proxy
git config --global --unset http.proxy
git config --global --unset https.proxy
echo Proxy has been unset.
goto end

:show_proxy
echo.
echo Current Git proxy settings:
echo HTTP Proxy: 
git config --global --get http.proxy
echo HTTPS Proxy: 
git config --global --get https.proxy
goto end

:end
echo.
echo Press any key to exit...
pause >nul