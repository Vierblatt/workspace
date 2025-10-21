#include "../include/keyboardlocker.h"
#include <string>
#include <Windows.h>

// Global variable definitions
HHOOK g_keyboardHook = nullptr;
HHOOK g_mouseHook = nullptr;
bool g_keyboardLocked = false;
bool g_mouseLocked = false;
bool g_exitProgram = false;
NOTIFYICONDATA g_notifyIconData = {};
HMENU g_contextMenu = nullptr;
HWND g_hWnd = nullptr;
bool g_isChinese = true;

// Main function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Detect system language
    LANGID langId = GetUserDefaultUILanguage();
    g_isChinese = (langId == 0x0804 || langId == 0x0404); // Simplified/Traditional Chinese

    // Register window class
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"KeyboardLocker";

    if (!RegisterClassEx(&wc))
    {
        MessageBox(nullptr, g_isChinese ? L"Window registration failed!" : L"Window registration failed!", g_isChinese ? L"Error" : L"Error", MB_ICONERROR);
        return 1;
    }

    // Create hidden window
    g_hWnd = CreateWindowEx(
        0,
        L"KeyboardLocker",
        g_isChinese ? L"Keyboard Locker" : L"Keyboard Locker",
        0,
        0, 0, 0, 0,
        nullptr, nullptr, hInstance, nullptr
    );
    if (!g_hWnd)
    {
        MessageBox(nullptr, g_isChinese ? L"Window creation failed!" : L"Window creation failed!", g_isChinese ? L"Error" : L"Error", MB_ICONERROR);
        return 1;
    }
    ShowWindow(g_hWnd, SW_HIDE); // Optimization: hide window immediately to prevent black window flash

    // Create system tray icon
    CreateTrayIcon(g_hWnd);

    // Set keyboard and mouse hooks
    g_keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInstance, 0);
    g_mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInstance, 0);

    if (!g_keyboardHook || !g_mouseHook)
    {
        if (!g_keyboardHook)
            MessageBox(nullptr, g_isChinese ? L"Keyboard hook set failed!" : L"Keyboard hook set failed!", g_isChinese ? L"Error" : L"Error", MB_ICONERROR);
        if (!g_mouseHook)
            MessageBox(nullptr, g_isChinese ? L"Mouse hook set failed!" : L"Mouse hook set failed!", g_isChinese ? L"Error" : L"Error", MB_ICONERROR);
        Cleanup();
        return 1;
    }

    // Create context menu
    g_contextMenu = CreatePopupMenu();
    AppendMenu(g_contextMenu, MF_STRING, 1, g_isChinese ? L"Lock/Unlock Keyboard" : L"Lock/Unlock Keyboard");
    AppendMenu(g_contextMenu, MF_STRING, 2, g_isChinese ? L"Lock/Unlock Mouse" : L"Lock/Unlock Mouse");
    AppendMenu(g_contextMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenu(g_contextMenu, MF_STRING, 3, g_isChinese ? L"Exit" : L"Exit");

    // Message loop
    MSG msg = {};
    while (!g_exitProgram && GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Cleanup resources
    Cleanup();

    return 0;
}