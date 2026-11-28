#include "graphics.hpp"
#include <d2d1.h>

HWND g_hWnd;
ID2D1Factory *g_pFactory;
ID2D1HwndRenderTarget *g_pRenderTarget;

template <class T>
void SafeRelease(T** ppT) {
    if (*ppT) {
        (*ppT)->Release();
        *ppT = nullptr;
    }
}

HRESULT CreateDeviceResources() {
    RECT rc;
    GetClientRect(g_hWnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(
        rc.right - rc.left,
        rc.bottom - rc.top
    );

    HRESULT hr = g_pFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(g_hWnd, size),
        &g_pRenderTarget
    );

    return hr;
}

void DiscardDeviceResources() {
    SafeRelease(&g_pRenderTarget);
}

bool InitGraphics(HWND hWnd) {
    g_hWnd = hWnd;

    HRESULT hr = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &g_pFactory
    );

    if (FAILED(hr)) {
        return false;
    }

    if (FAILED(CreateDeviceResources())) {
        CleanupGraphics();
        return false;
    }

    return true;
}

void CleanupGraphics() {
    DiscardDeviceResources();
    SafeRelease(&g_pFactory);
}

void RenderFrame() {
    g_pRenderTarget->BeginDraw();
    g_pRenderTarget->Clear(D2D1::ColorF(1.0, 1.0, 1.0));
    g_pRenderTarget->EndDraw();
}