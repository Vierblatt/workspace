#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#ifndef KEYBOARD_LOCKER_H
#define KEYBOARD_LOCKER_H

#include <Windows.h>

// Global variable declarations
extern HHOOK g_keyboardHook;
extern HHOOK g_mouseHook;
extern bool g_keyboardLocked;
extern bool g_mouseLocked;
extern bool g_exitProgram;
extern NOTIFYICONDATA g_notifyIconData;
extern HMENU g_contextMenu;
extern HWND g_hWnd;
extern bool g_isChinese;

// Function declarations
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void CreateTrayIcon(HWND hWnd);
void ShowContextMenu(HWND hWnd);
void ToggleKeyboardLock();
void ToggleMouseLock();
void Cleanup();

#endif // KEYBOARD_LOCKER_H