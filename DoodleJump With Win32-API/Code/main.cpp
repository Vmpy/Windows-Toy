#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <gdiplus.h>
#include <time.h>
#include "Data.h"

using namespace Gdiplus;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND,UINT,WPARAM,LPARAM);

GameClass Game;

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("DoodleJumpWin32");

int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    ULONG_PTR Token;
    GdiplusStartupInput Input;

    GdiplusStartup(&Token,&Input,NULL);
    srand(time(0));
    Game.First();

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    wincl.hbrBackground = 0;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Win32 DoodleJump"),       /* Title Text */
           WS_OVERLAPPEDWINDOW^WS_THICKFRAME^WS_MAXIMIZEBOX, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           MAX_WIDTH,                 /* The programs width */
           MAX_HEIGHT,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    GdiplusShutdown(Token);

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        {
            SetTimer(hwnd,ID_TIMER,1,0);
            break;
        }

        case WM_TIMER:
        {
            Game.Doodle.SetJumpDirection(Game.FloorMove,Game.Floor,MAX_ARRSIZE);
            Game.Doodle.Jump();
            Game.Doodle.SetJumpDirection(Game.FloorMove,Game.Floor,MAX_ARRSIZE);
            Game.Doodle.Jump();

            Game.FloorMove.Move();
            Game.FloorMove.ReBorn();
            for(int i = 0;i < MAX_ARRSIZE;i++)
            {
                Game.Floor[i].Move();
                Game.Floor[i].ReBorn();
            }

            Game.Doodle.Death();

            if(Game.Doodle.IsDead)
            {
                KillTimer(hwnd,ID_TIMER);
                MessageBox(0,"游戏结束.","提示",MB_OK|MB_ICONERROR);
            }

            InvalidateRect(hwnd,0,true);
            break;
        }

        case WM_KEYDOWN:
        {
            Game.Doodle.Move(wParam);

            break;
        }

        case WM_PAINT:
        {
            char score[20];

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd,&ps);
            HDC hDCBuffer = CreateCompatibleDC(hdc);

            HBITMAP hBitmap = (HBITMAP)LoadImage(0,"Res//sky.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
            SelectObject(hDCBuffer,hBitmap);

            if(!Game.DrawSight(hDCBuffer))
            {
                KillTimer(hwnd,ID_TIMER);
                MessageBox(0,"文件数据丢失!",NULL,MB_OK|MB_ICONERROR);
            }

            BitBlt(hdc,0,0,MAX_WIDTH,MAX_HEIGHT,hDCBuffer,0,0,SRCCOPY);

            wsprintf(score,"分数:%d",Game.Score/MAX_ARRSIZE);
            TextOut(hdc,0,0,score,lstrlen(score));

            EndPaint(hwnd,&ps);
            DeleteDC(hDCBuffer);    //清理创建设备上下文句柄
            DeleteObject(hBitmap);
            break;
        }
        case WM_DESTROY:
        {
            KillTimer(hwnd,ID_TIMER);
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        }
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
