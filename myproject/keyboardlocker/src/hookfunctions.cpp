#include "../include/keyboardlocker.h"
#include <string>

// Keyboard hook procedure
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0 && g_keyboardLocked)
    {
        // Check if unlock key combination (Ctrl+Alt+K) is pressed
        KBDLLHOOKSTRUCT* pKeyInfo = (KBDLLHOOKSTRUCT*)lParam;

        static bool ctrlPressed = false;
        static bool altPressed = false;
        static bool kPressed = false;

        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
        {
            if (pKeyInfo->vkCode == VK_LCONTROL || pKeyInfo->vkCode == VK_RCONTROL)
                ctrlPressed = true;
            else if (pKeyInfo->vkCode == VK_LMENU || pKeyInfo->vkCode == VK_RMENU)
                altPressed = true;
            else if (pKeyInfo->vkCode == 'K')
                kPressed = true;

            // If unlock key combination is pressed, unlock keyboard
            if (ctrlPressed && altPressed && kPressed)
            {
                ToggleKeyboardLock();
                // Reset key states so it can be used again after next lock
                ctrlPressed = false;
                altPressed = false;
                kPressed = false;
                return 1; // Block key combination propagation
            }
        }
        else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
        {
            if (pKeyInfo->vkCode == VK_LCONTROL || pKeyInfo->vkCode == VK_RCONTROL)
                ctrlPressed = false;
            else if (pKeyInfo->vkCode == VK_LMENU || pKeyInfo->vkCode == VK_RMENU)
                altPressed = false;
            else if (pKeyInfo->vkCode == 'K')
                kPressed = false;
        }

        // If keyboard is locked, block all keyboard input
        return 1;
    }

    return CallNextHookEx(g_keyboardHook, nCode, wParam, lParam);
}

// Mouse hook procedure
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0 && g_mouseLocked)
    {
        // Check if unlock key combination (Ctrl+Alt+M) is pressed
        MSLLHOOKSTRUCT* pMouseInfo = (MSLLHOOKSTRUCT*)lParam;

        static bool ctrlPressed = false;
        static bool altPressed = false;
        static bool mPressed = false;

        if (wParam == WM_MOUSEMOVE || wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN || wParam == WM_MBUTTONDOWN)
        {
            // Get keyboard state
            if (GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL) < 0)
                ctrlPressed = true;
            else
                ctrlPressed = false;

            if (GetAsyncKeyState(VK_LMENU) < 0 || GetAsyncKeyState(VK_RMENU) < 0)
                altPressed = true;
            else
                altPressed = false;

            if (GetAsyncKeyState('M') < 0)
                mPressed = true;
            else
                mPressed = false;

            // If unlock key combination is pressed, unlock mouse
            if (ctrlPressed && altPressed && mPressed)
            {
                ToggleMouseLock();
                // Reset key states so it can be used again after next lock
                ctrlPressed = false;
                altPressed = false;
                mPressed = false;
                return 1; // Block mouse event propagation
            }
        }

        // If mouse is locked, block all mouse input
        return 1;
    }

    return CallNextHookEx(g_mouseHook, nCode, wParam, lParam);
}

// Window procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_USER + 1:
        switch (lParam)
        {
        case WM_RBUTTONUP:
            ShowContextMenu(hWnd);
            break;
        case WM_LBUTTONDBLCLK:
            ToggleKeyboardLock();
            break;
        }
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 1: // Lock/Unlock keyboard
            ToggleKeyboardLock();
            break;
        case 2: // Lock/Unlock mouse
            ToggleMouseLock();
            break;
        case 3: // Exit
            g_exitProgram = true;
            PostQuitMessage(0);
            break;
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}