#include <windows.h>
#include <gdiplus.h>
#include "Data.h"

using namespace Gdiplus;


LRESULT CALLBACK WindowProcedure (HWND,UINT,WPARAM,LPARAM);
bool DrawImage(OneSnow,Bitmap*,const wchar_t*);

TCHAR szClassName[ ] = TEXT("SnowDeskTop");

int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    GdiplusStartupInput Input;
    ULONG_PTR GdiplusToken;

    GdiplusStartup(&GdiplusToken,&Input,0);

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    wincl.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
    {
        return 0;
    }

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           TEXT("SnowDeskTop"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           640,                 /* The programs width */
           480,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd,SW_HIDE);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    GdiplusShutdown(GdiplusToken);

    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc;
    static OneSnow Snow[10];
    static int cx = GetSystemMetrics(SM_CXSCREEN);
    static int cy = GetSystemMetrics(SM_CYSCREEN);
    static HWND Desktop;
    static int COUNT = 0;

    Desktop = FindWindow("Progman", NULL);
    Desktop = GetWindow(Desktop, GW_CHILD);
    Desktop = GetWindow(Desktop, GW_CHILD);

    switch (message)
    {
        case WM_TIMER:
        {
            COUNT++;
            if(COUNT%2 == 0)
            {
                for(int i = 0;i < 25;i++)
                    InvalidateRect(Desktop,&Snow[i].RedrawRect,false);
            }
            hdc = GetDC(Desktop);
            Bitmap Drawmap_(cx,cy);
            Graphics gr(hdc);
            for(int i = 0;i < 25;i++)
            {
                switch(Snow[i].Type)
                {
                    case 1:
                    {
                        DrawImage(Snow[i],&Drawmap_,L"Snow1.png");
                        break;
                    }
                    case 2:
                    {
                        DrawImage(Snow[i],&Drawmap_,L"Snow2.png");
                        break;
                    }
                    case 3:
                    {
                        DrawImage(Snow[i],&Drawmap_,L"Snow3.png");
                        break;
                    }
                    case 4:
                    {
                        DrawImage(Snow[i],&Drawmap_,L"Snow4.png");
                        break;
                    }
                    case 5:
                    {
                        DrawImage(Snow[i],&Drawmap_,L"Snow5.png");
                        break;
                    }
                    case 6:
                    {
                        DrawImage(Snow[i],&Drawmap_,L"Snow1.png");
                        break;
                    }
                }
                Snow[i].Move();
            }
            gr.DrawImage(&Drawmap_,0,0);

            ReleaseDC(Desktop,hdc);
            break;
        }
        case WM_CREATE:
        {
            SetTimer(hwnd,1,10,0);
            break;
        }
        case WM_DESTROY:
        {
            KillTimer(hwnd,1);
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        }
        default:
            return DefWindowProc(hwnd,message,wParam,lParam);
    }
    return 0;
}

bool DrawImage(OneSnow Snow,Bitmap* bitmap,const wchar_t* FileName)
{
    /*加载雪花图片*/
    Image SnowImage(FileName);
    if(SnowImage.GetLastStatus() != Status::Ok)
    {
        return false;
    }
    Graphics Graph(bitmap);
    Graph.DrawImage(&SnowImage,RectF(Snow.x,Snow.y,Snow.Width,Snow.Height));
    return true;
}
