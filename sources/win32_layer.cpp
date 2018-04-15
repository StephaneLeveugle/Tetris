#include <Windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define SCREEN_HEIGHT 1000
#define SCREEN_WIDTH 500
#define GAME_HEIGHT 1000
#define GAME_WIDTH 500

struct GameControls {
    bool isRightPressed, isLeftPressed, isDownPressed;
};

static GameControls gameControls = {};
static bool isGameRunning = true;
static u32 *buffer;

#include "game.cpp"

LRESULT CALLBACK win32_windowCallback(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    
    switch(uMsg) {

        case WM_QUIT: {
            isGameRunning = false;
            return 0;
        }

        case WM_DESTROY: {
            isGameRunning = false;
            PostQuitMessage(0);
            return 0;
        }

        case WM_KEYDOWN: {
            switch(wParam) {
                case VK_LEFT: {
                    gameControls.isLeftPressed = true;
                    return 0;
                }

                case VK_RIGHT: {
                    gameControls.isRightPressed = true;
                    return 0;
                }

                case VK_DOWN: {
                    gameControls.isDownPressed = true;
                    return 0;
                }

                case VK_ESCAPE: {
                    isGameRunning = false;
                    return 0;
                }

                default: {
                    return DefWindowProcA(hWindow, uMsg, wParam, lParam);
                }
            }
        }

        case WM_KEYUP: {
            switch(wParam) {
                case VK_LEFT: {
                    gameControls.isLeftPressed = false;
                    return 0;
                }

                case VK_RIGHT: {
                    gameControls.isRightPressed = false;
                    return 0;
                }

                case VK_DOWN: {
                    gameControls.isDownPressed = false;
                    return 0;
                }

                default: {
                    return DefWindowProcA(hWindow, uMsg, wParam, lParam);
                }
            }
        }

        case WM_PAINT:
        default: {
            return DefWindowProcA(hWindow, uMsg, wParam, lParam);
        }
    }
}

void win32_displayGame(HDC hdc, void *buffer, BITMAPINFO bitmapInfo) {
    StretchDIBits(hdc, 
                0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                0, 0, GAME_WIDTH, GAME_HEIGHT,
                buffer, &bitmapInfo,
                DIB_RGB_COLORS, SRCCOPY);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
    // register the window class
    WNDCLASSA windowClass = {};
    windowClass.lpfnWndProc = win32_windowCallback;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = "Tetris";

    RegisterClassA(&windowClass);

    // create the window
    HWND hWindow = CreateWindowExA(0, windowClass.lpszClassName, "Tetris", WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH + 50, SCREEN_HEIGHT + 50, nullptr, nullptr, hInstance, nullptr);

    if (!hWindow) {
        // TODO: Log error
        return -1;
    }

    buffer = (u32 *) calloc(GAME_WIDTH * GAME_HEIGHT, sizeof(u32));

    BITMAPINFO bitmapInfo = {};
    bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo.bmiHeader);
    bitmapInfo.bmiHeader.biWidth = GAME_WIDTH;
    bitmapInfo.bmiHeader.biHeight = GAME_HEIGHT;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;

    ShowWindow(hWindow, nCmdShow);

    HDC hdc = GetDC(hWindow);

    gameInit(buffer);

    u64 lastFrameTime = 0;
    u64 currentFrameTime = 0;

    MSG msg = {};
    while (isGameRunning) {
        msg = {};
        while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
 
        LARGE_INTEGER freq;
        LARGE_INTEGER t1, t2;
        double elapsedTime;

        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&t1);

        win32_displayGame(hdc, buffer, bitmapInfo);
        gameUpdate(buffer, gameControls);

        QueryPerformanceCounter(&t2);
        u64 timeElapsed = ((t2.QuadPart - t1.QuadPart) * 1000) / freq.QuadPart;
        char timeElapsedStr[256];
        sprintf(timeElapsedStr, "time elapsed in ms : %llu\n", timeElapsed);
        OutputDebugStringA(timeElapsedStr);
        s64 sleepTime = 500 - (s64)timeElapsed;
        if (sleepTime > 2) {
            if (gameControls.isLeftPressed || gameControls.isRightPressed) sleepTime /= 5;
            if (gameControls.isDownPressed) sleepTime /= 10;
            Sleep(sleepTime);
        }
    }

    ReleaseDC(hWindow, hdc);

    return 0;
}