#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <stdlib.h>
#include <windows.h>

LRESULT CALLBACK WindowProcedure (HWND,UINT,WPARAM,LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("MouseClick");

int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           WS_EX_TOPMOST,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("MouseClick"),       /* Title Text */
           WS_OVERLAPPEDWINDOW^WS_THICKFRAME, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           600,                 /* The programs width */
           350,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    ShowWindow (hwnd, nCmdShow);
    RegisterHotKey(hwnd,1,MOD_CONTROL,'S');	// Ctrl + S
    RegisterHotKey(hwnd,2,MOD_CONTROL,'E');	// Ctrl + S

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND ChoiceGroupBox;
    static HWND RadioButtonLeft;
    static HWND RadioButtonMid;
    static HWND RadioButtonRight;

    static HWND OkButton;
    static HWND EndButton;
    static HWND TimeEdit;
    static HWND TextTime;

    int aiElements[] ={COLOR_BTNFACE};

    DWORD aColors[] ={RGB(255,255,255)};

    switch (message)
    {
        case WM_CREATE:
        {
            HFONT hFont = CreateFont(20,7,0,0,400,FALSE, FALSE, FALSE,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,TEXT("微软雅黑"));
            SetSysColors(1,aiElements,aColors);
            ChoiceGroupBox = CreateWindowEx(NULL,"BUTTON","按键选择",WS_CHILD|WS_VISIBLE|BS_GROUPBOX,60,45,500,85,hwnd,(HMENU)1,0,0);
            RadioButtonLeft = CreateWindowEx(NULL,"BUTTON","左键",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,5,30,165,40,ChoiceGroupBox,(HMENU)2,0,0);
            RadioButtonMid = CreateWindowEx(NULL,"BUTTON","中键",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,170,30,165,40,ChoiceGroupBox,(HMENU)3,0,0);
            RadioButtonRight = CreateWindowEx(NULL,"BUTTON","右键",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,335,30,160,40,ChoiceGroupBox,(HMENU)4,0,0);
            TextTime = CreateWindowEx(NULL,"STATIC","点击时间间隔(毫秒):",WS_CHILD|WS_VISIBLE|SS_CENTERIMAGE|SS_CENTER,60,180,135,20,hwnd,(HMENU)5,0,0);
            TimeEdit = CreateWindowEx(NULL,"EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_NUMBER|ES_AUTOHSCROLL,200,180,135,25,hwnd,(HMENU)6,0,0);
            OkButton = CreateWindowEx(NULL,"BUTTON","开始(S键)",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_PUSHBUTTON|BS_FLAT,410,180,80,30,hwnd,(HMENU)7,0,0);
            EndButton = CreateWindowEx(NULL,"BUTTON","结束(E键)",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_PUSHBUTTON|BS_FLAT,410,245,80,30,hwnd,(HMENU)8,0,0);

            SendMessage(ChoiceGroupBox,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(RadioButtonLeft,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(RadioButtonMid,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(RadioButtonRight,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(TextTime,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(TimeEdit,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(OkButton,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(EndButton,WM_SETFONT,(WPARAM)hFont,0);
            break;
        }

        case WM_HOTKEY:
        {
            switch(wParam)
            {
                case 1:
                {
                    char Time[10];
                    SendMessage(TimeEdit,WM_GETTEXT,(WPARAM)10,(LPARAM)Time);
                    UINT TimeOut = atoi(Time);
                    SetTimer(hwnd,1,TimeOut,0);
                    break;
                }
                case 2:
                {
                    KillTimer(hwnd,1);
                    break;
                }
            }
            break;
        }

        case WM_TIMER:
        {
            if(SendMessage(RadioButtonLeft,BM_GETCHECK,0,0))
            {
                mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,NULL);
                mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,NULL);
                break;
            }
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        }
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
