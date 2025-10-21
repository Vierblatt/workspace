#include "../include/keyboardlocker.h"
#include <string>

// Chinese and English UI string constants
const wchar_t* STR_TRAY_TIP_CN = L"Jianpan suoding gongju - youjian dianji caidan";
const wchar_t* STR_TRAY_TIP_EN = L"Keyboard Locker - Right click for menu";
const wchar_t* STR_TRAY_TIP_LOCKED_CN = L"Jianpan yi suoding - an Ctrl+Alt+K jiesuo";
const wchar_t* STR_TRAY_TIP_LOCKED_EN = L"Keyboard locked - Press Ctrl+Alt+K to unlock";
const wchar_t* STR_TRAY_TIP_MOUSE_LOCKED_CN = L"Shubiao yi suoding - an Ctrl+Alt+M jiesuo";
const wchar_t* STR_TRAY_TIP_MOUSE_LOCKED_EN = L"Mouse locked - Press Ctrl+Alt+M to unlock";
const wchar_t* STR_TRAY_TIP_ALL_LOCKED_CN = L"Jianpan he shubiao yi suoding\nJianpan: Ctrl+Alt+K\nShubiao: Ctrl+Alt+M";
const wchar_t* STR_TRAY_TIP_ALL_LOCKED_EN = L"Keyboard and mouse locked\nKeyboard: Ctrl+Alt+K\nMouse: Ctrl+Alt+M";
const wchar_t* STR_KEYBOARD_LOCKED_MSG_CN = L"Jianpan yi suoding!\n\nAn Ctrl+Alt+K jiesuo";
const wchar_t* STR_KEYBOARD_LOCKED_MSG_EN = L"Keyboard locked!\n\nPress Ctrl+Alt+K to unlock";
const wchar_t* STR_KEYBOARD_LOCKED_TITLE_CN = L"Jianpan suo";
const wchar_t* STR_KEYBOARD_LOCKED_TITLE_EN = L"Keyboard Locker";
const wchar_t* STR_MOUSE_LOCKED_MSG_CN = L"Shubiao yi suoding!\n\nAn Ctrl+Alt+M jiesuo";
const wchar_t* STR_MOUSE_LOCKED_MSG_EN = L"Mouse locked!\n\nPress Ctrl+Alt+M to unlock";
const wchar_t* STR_MOUSE_LOCKED_TITLE_CN = L"Shubiao suo";
const wchar_t* STR_MOUSE_LOCKED_TITLE_EN = L"Mouse Locker";
const wchar_t* STR_UNLOCK_KEYBOARD_CN = L"Jiesuo jianpan";
const wchar_t* STR_UNLOCK_KEYBOARD_EN = L"Unlock Keyboard";
const wchar_t* STR_LOCK_KEYBOARD_CN = L"Suoding jianpan";
const wchar_t* STR_LOCK_KEYBOARD_EN = L"Lock Keyboard";
const wchar_t* STR_UNLOCK_MOUSE_CN = L"Jiesuo shubiao";
const wchar_t* STR_UNLOCK_MOUSE_EN = L"Unlock Mouse";
const wchar_t* STR_LOCK_MOUSE_CN = L"Suoding shubiao";
const wchar_t* STR_LOCK_MOUSE_EN = L"Lock Mouse";
const wchar_t* STR_TOOL_CN = L"Jianpan suoding gongju";
const wchar_t* STR_TOOL_EN = L"Keyboard Locker";

// Create system tray icon
void CreateTrayIcon(HWND hWnd)
{
    g_notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
    g_notifyIconData.hWnd = hWnd;
    g_notifyIconData.uID = 1;
    g_notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    g_notifyIconData.uCallbackMessage = WM_USER + 1;
    g_notifyIconData.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcscpy_s(g_notifyIconData.szTip, 128, g_isChinese ? STR_TRAY_TIP_CN : STR_TRAY_TIP_EN);

    Shell_NotifyIcon(NIM_ADD, &g_notifyIconData);
}

// Show context menu
void ShowContextMenu(HWND hWnd)
{
    POINT pt;
    GetCursorPos(&pt);

    SetForegroundWindow(hWnd);

    // Update menu item text
    ModifyMenuW(g_contextMenu, 1, MF_BYCOMMAND | MF_STRING, 1,
        g_keyboardLocked ? (g_isChinese ? STR_UNLOCK_KEYBOARD_CN : STR_UNLOCK_KEYBOARD_EN)
        : (g_isChinese ? STR_LOCK_KEYBOARD_CN : STR_LOCK_KEYBOARD_EN));
    ModifyMenuW(g_contextMenu, 2, MF_BYCOMMAND | MF_STRING, 2,
        g_mouseLocked ? (g_isChinese ? STR_UNLOCK_MOUSE_CN : STR_UNLOCK_MOUSE_EN)
        : (g_isChinese ? STR_LOCK_MOUSE_CN : STR_LOCK_MOUSE_EN));

    TrackPopupMenu(g_contextMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, nullptr);
    PostMessage(hWnd, WM_NULL, 0, 0);
}

// Toggle keyboard lock state
void ToggleKeyboardLock()
{
    g_keyboardLocked = !g_keyboardLocked;

    // Update tray icon tooltip
    wcscpy_s(g_notifyIconData.szTip, 128,
        g_keyboardLocked ? (g_isChinese ? STR_TRAY_TIP_LOCKED_CN : STR_TRAY_TIP_LOCKED_EN)
        : (g_isChinese ? STR_TRAY_TIP_CN : STR_TRAY_TIP_EN));
    Shell_NotifyIcon(NIM_MODIFY, &g_notifyIconData);

    // Show notification
    if (g_keyboardLocked)
    {
        MessageBoxW(nullptr,
            g_isChinese ? STR_KEYBOARD_LOCKED_MSG_CN : STR_KEYBOARD_LOCKED_MSG_EN,
            g_isChinese ? STR_KEYBOARD_LOCKED_TITLE_CN : STR_KEYBOARD_LOCKED_TITLE_EN,
            MB_ICONINFORMATION | MB_OK);
    }
}

// Toggle mouse lock state
void ToggleMouseLock()
{
    g_mouseLocked = !g_mouseLocked;

    // Update tray icon tooltip
    wchar_t tip[128];
    if (g_keyboardLocked && g_mouseLocked)
        wcscpy_s(tip, 128, g_isChinese ? STR_TRAY_TIP_ALL_LOCKED_CN : STR_TRAY_TIP_ALL_LOCKED_EN);
    else if (g_keyboardLocked)
        wcscpy_s(tip, 128, g_isChinese ? STR_TRAY_TIP_LOCKED_CN : STR_TRAY_TIP_LOCKED_EN);
    else if (g_mouseLocked)
        wcscpy_s(tip, 128, g_isChinese ? STR_TRAY_TIP_MOUSE_LOCKED_CN : STR_TRAY_TIP_MOUSE_LOCKED_EN);
    else
        wcscpy_s(tip, 128, g_isChinese ? STR_TRAY_TIP_CN : STR_TRAY_TIP_EN);

    wcscpy_s(g_notifyIconData.szTip, 128, tip);
    Shell_NotifyIcon(NIM_MODIFY, &g_notifyIconData);

    // Show notification
    if (g_mouseLocked)
    {
        MessageBoxW(nullptr,
            g_isChinese ? STR_MOUSE_LOCKED_MSG_CN : STR_MOUSE_LOCKED_MSG_EN,
            g_isChinese ? STR_MOUSE_LOCKED_TITLE_CN : STR_MOUSE_LOCKED_TITLE_EN,
            MB_ICONINFORMATION | MB_OK);
    }
}

// Cleanup resources
void Cleanup()
{
    // Remove hooks
    if (g_keyboardHook)
        UnhookWindowsHookEx(g_keyboardHook);

    if (g_mouseHook)
        UnhookWindowsHookEx(g_mouseHook);

    // Remove tray icon
    Shell_NotifyIcon(NIM_DELETE, &g_notifyIconData);

    // Destroy menu
    if (g_contextMenu)
        DestroyMenu(g_contextMenu);
}