#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <gdiplus.h>
#include <ctime>
#include "Data.h"
#include "resource.h"

using namespace Gdiplus;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[] = _T("Flappy Huaji");

int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    ULONG_PTR GdiplusToken;
    GdiplusStartupInput Input;
    GdiplusStartup(&GdiplusToken,&Input,0);

    HMENU TopMenu = CreateMenu();
    HMENU GameMenu = CreateMenu();

    srand(time(0));

    AppendMenu(TopMenu,MF_POPUP,(UINT)GameMenu,"游戏操作");

    AppendMenu(GameMenu,MF_STRING,ID_RESTART,TEXT("重新开始"));
    AppendMenu(GameMenu,MF_STRING,ID_CHECKSCORE,TEXT("查看分数"));
    AppendMenu(GameMenu,MF_STRING,ID_PAUSE,TEXT("暂停游戏"));

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL,IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */

    HBITMAP Backgroud = (HBITMAP)LoadImage(hThisInstance,"Res//sky.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    wincl.hbrBackground = CreatePatternBrush(Backgroud);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
    {
        return 0;
    }

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Flappy Huaji"),  /* Title Text */
           WS_OVERLAPPEDWINDOW^WS_THICKFRAME^WS_MAXIMIZEBOX, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           WindowWidth,                 /* The programs width */
           WindowHeight,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           TopMenu,
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd,nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    GdiplusShutdown(GdiplusToken);
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    static RECT Client;
    static HDC hdc;
    static PAINTSTRUCT ps;

    static GameClass Game;

    switch (message)                  /* handle the messages */
    {
        case WM_TIMER:
        {
            //检查是否暂停.
            if(!Game.IsPause)
            {
                for(int i = 0;i < MaxYinxianNum;i++)
                {
                    Game.Yinxian[i].Move();
                    Game.Yinxian[i].DeathAndRelive();
                }
                Game.Score++;
                Game.Huaji.DropDown();
                InvalidateRect(hwnd,0,true);
            }
            break;
        }

        case WM_LBUTTONDOWN:
        {
            Game.Huaji.Flyup();
            break;
        }

        case WM_LBUTTONDBLCLK:
        {
            Game.Huaji.Flyup();
            Game.Huaji.Flyup();
            break;
        }

        case WM_CREATE:
        {
            Game.Window = hwnd;

            SetTimer(hwnd,0,50,0);
            break;
        }

        case WM_PAINT:
        {
            hdc = BeginPaint(hwnd,&ps);
            Game.DrawHuaji(hdc);
            Game.DrawYinxian(hdc);
            EndPaint(hwnd,&ps);
            if(Game.GameOver())
            {
                KillTimer(hwnd,0);
                MessageBox(hwnd,"由于滑稽因为不明操作身亡，游戏结束.","提示",MB_OK);
            }
            break;
        }

        case WM_COMMAND:
        {
            if(lParam == 0)
            {
                switch(LOWORD(wParam))
                {
                    case ID_RESTART:SetTimer(hwnd,0,50,0);Game.Restart();break;
                    case ID_CHECKSCORE:break;
                    case ID_PAUSE:Game.Pause();break;
                }
            }
            break;
        }

        case WM_SIZE:
        {
            GetClientRect(hwnd,&Client);
            break;
        }

        case WM_DESTROY:
        {
            KillTimer(hwnd,0);
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        }
        default:
            return DefWindowProc(hwnd,message,wParam,lParam);
    }
    return 0;
}
