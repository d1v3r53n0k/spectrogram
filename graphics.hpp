#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Windows.h>

bool InitGraphics(HWND hWnd);
void CleanupGraphics();
void RenderFrame();

#endif  /* GRAPHICS_H */
