#include "graphics.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define WC_MAINCLASS    TEXT("AudioSpectrogram")

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow
) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    WNDCLASSEX wcex = {0};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.lpfnWndProc = WindowProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = NULL;
    wcex.lpszClassName = WC_MAINCLASS;

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    HWND hWnd = CreateWindowEx(
        0,
        WC_MAINCLASS,
        TEXT("Audio Spectrogram"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    
    if (!hWnd) {
        return 1;
    }

    if(!InitGraphics(hWnd)) {
        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CleanupGraphics();

    return 0;
}

LRESULT CALLBACK WindowProc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
) {
    switch (uMsg) {
        case WM_CREATE: {
            return 0;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT: {
            RenderFrame();
            ValidateRect(hWnd, NULL);
            return 0;
        }
        default: {
            break;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
