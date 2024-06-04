#include <windows.h>
#include <iostream>

HHOOK keyboardHook;

bool IsRightCtrlPressed() {
    return (GetKeyState(VK_RCONTROL) & 0x8000) != 0;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

        if (IsRightCtrlPressed()) {
            switch (p->vkCode) {
            case VK_UP:
                if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                    keybd_event(VK_NUMPAD8, 0, 0, 0);
                }
                else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                    keybd_event(VK_NUMPAD8, 0, KEYEVENTF_KEYUP, 0);
                }
                return 1;
            case VK_DOWN:
                if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                    keybd_event(VK_NUMPAD2, 0, 0, 0);
                }
                else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                    keybd_event(VK_NUMPAD2, 0, KEYEVENTF_KEYUP, 0);
                }
                return 1;
            case VK_LEFT:
                if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                    keybd_event(VK_NUMPAD4, 0, 0, 0);
                }
                else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                    keybd_event(VK_NUMPAD4, 0, KEYEVENTF_KEYUP, 0);
                }
                return 1;
            case VK_RIGHT:
                if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                    keybd_event(VK_NUMPAD6, 0, 0, 0);
                }
                else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                    keybd_event(VK_NUMPAD6, 0, KEYEVENTF_KEYUP, 0);
                }
                return 1;
            case VK_BACK:
                if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                    keybd_event(VK_NUMPAD0, 0, 0, 0);
                }
                else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                    keybd_event(VK_NUMPAD0, 0, KEYEVENTF_KEYUP, 0);
                }
                return 1;
            case VK_RETURN:
                if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                    keybd_event(VK_NUMPAD5, 0, 0, 0);
                }
                else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                    keybd_event(VK_NUMPAD5, 0, KEYEVENTF_KEYUP, 0);
                }
                return 1;
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    if (keyboardHook == NULL) {
        MessageBox(NULL, TEXT("Failed to install hook!"), TEXT("Error"), MB_ICONERROR);
        return 1;
    }
    std::cout << "Press right control and use arrows like you would normally";

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(keyboardHook);
    return 0;
}
