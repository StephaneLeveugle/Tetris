#include <Windows.h>
#include <stdint.h>

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define GAME_WIDTH 402 // 2pixels of border (1left 1 right)
#define GAME_HEIGHT 800 // 2pixels of border (1top 1bottom)

static void *buffer;
static bool global_isGameRunning = true;

#include "game.cpp"


static GameControls gameControls = {};

// TODO: Use own buffer and display it with StretchDIBits 

LRESULT CALLBACK win32_windowCallback(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch(uMsg)
  {

    case WM_QUIT:
    {
      global_isGameRunning = false;
      return 0;
    }

    case WM_DESTROY:
    {
      global_isGameRunning = false;
      PostQuitMessage(0);
      return 0;
    }

    case WM_KEYDOWN:
    {
      switch(wParam)
      {
        case VK_LEFT:
        {
          gameControls.isLeftPressed = true;
          return 0;
        }

        case VK_RIGHT:
        {
          gameControls.isRightPressed = true;
          return 0;
        }

        case VK_DOWN:
        {
          gameControls.isDownPressed = true;
          return 0;
        }

        default:
        {
          return DefWindowProcA(hWindow, uMsg, wParam, lParam);
        }
      }
    }

    case WM_KEYUP:
    {
      switch(wParam)
      {
        case VK_LEFT:
        {
          gameControls.isLeftPressed = false;
          return 0;
        }

        case VK_RIGHT:
        {
          gameControls.isRightPressed = false;
          return 0;
        }

        case VK_DOWN:
        {
          gameControls.isDownPressed = false;
          return 0;
        }

        default:
        {
          return DefWindowProcA(hWindow, uMsg, wParam, lParam);
        }
      }
    }
    
    case WM_PAINT:
    {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hWindow, &ps);

      FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(255, 255, 255)));

      /*RECT tile = {};
      tile.top = (SCREEN_HEIGHT / 2) - 10;
      tile.bottom = (SCREEN_HEIGHT / 2) + 10;
      tile.left = (SCREEN_WIDTH / 2) - 10;
      tile.right = (SCREEN_WIDTH / 2) + 10;

      FillRect(hdc, &tile, CreateSolidBrush(RGB(0, 255, 255)));

      POINT points[4];
      points[0].x = 10;
      points[0].y = 10;
      
      points[1].x = 20;
      points[1].y = 10;
      
      points[2].x = 20;
      points[2].y = 20;

      points[3].x = 10;
      points[3].y = 20;
    
      if(Polygon(hdc, points, sizeof(points) / sizeof(POINT)))
      {
        OutputDebugStringA("polygon drawn");
        HRGN polyRgn = CreatePolygonRgn(points, sizeof(points) / sizeof(POINT), WINDING);
        FillRgn(hdc, polyRgn, CreateSolidBrush(RGB(255, 0, 0)));
      }*/

      EndPaint(hWindow, &ps);
      return 0; 
    }
    default:
    {
      return DefWindowProcA(hWindow, uMsg, wParam, lParam);
    }
  }
}

void win32_displayGame(HDC hdc, void *buffer, BITMAPINFO bitmapInfo)
{
  StretchDIBits(hdc, 
                (SCREEN_WIDTH * (3.0f / 4.0f)) - (GAME_WIDTH / 2),
                (SCREEN_HEIGHT / 2) - (GAME_HEIGHT / 2),
                GAME_WIDTH, GAME_HEIGHT,
                0, 0,
                GAME_WIDTH, GAME_HEIGHT,
                buffer, &bitmapInfo,
                DIB_RGB_COLORS, SRCCOPY);
}

void resetControls(GameControls *gameControls)
{
  gameControls->isDownPressed = false;
  gameControls->isLeftPressed = false;
  gameControls->isRightPressed = false;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
  // register the window class
  WNDCLASSA windowClass = {};
  windowClass.lpfnWndProc = win32_windowCallback;
  windowClass.hInstance = hInstance;
  windowClass.lpszClassName = "Fucking Tetris";
  
  RegisterClassA(&windowClass);

  // create the window
  HWND hWindow = CreateWindowExA(0, windowClass.lpszClassName, "Fuuuuuuuuuucking Tetris", WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr);

  if(!hWindow)
  {
    // TODO: Log error
    return -1;
  }

  buffer = calloc(GAME_WIDTH * GAME_HEIGHT, sizeof(uint32));
  
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

  while(global_isGameRunning)
  {
    //resetControls(&gameControls);
    // run the message loop
    MSG msg = {};
    while(PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessageA(&msg);
    }

    // TODO: remember to swap them, gameUpdate should go first
    win32_displayGame(hdc, buffer, bitmapInfo);
    gameUpdate(buffer, gameControls);
//
    // Sleep(100);
  }
 
  ReleaseDC(hWindow, hdc);

  return 0;
}