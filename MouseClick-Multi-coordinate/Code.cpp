#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("MouseClick-(Multi-coordinate)");

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
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("MouseClick-(Multi-coordinate) By Vmpy"),       /* Title Text */
           WS_OVERLAPPEDWINDOW^WS_THICKFRAME^WS_MAXIMIZEBOX, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           420,                 /* The programs width */
           650,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
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
    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    static HWND TextTime;
    static HWND TimeEdit;

    static HWND ChoiceGroupBox;
    static HWND RadioButtonLeft;
    static HWND RadioButtonMid;
    static HWND RadioButtonRight;

    static HWND PositionList;
    static HWND AddButton;
    static HWND DeleteButton;
    static HWND ClearButton;

    static HWND TextPosition;
    static HWND PositionXEdit;
    static HWND PositionYEdit;

    static HWND StartButton;
    static HWND EndButton;

    switch (message)
    {
        case WM_CREATE:
        {
            HFONT hFont = CreateFont(20,7,0,0,400,FALSE, FALSE, FALSE,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,TEXT("微软雅黑"));

            TextTime = CreateWindowEx(0,"STATIC","点击时间间隔(ms):",WS_CHILD|WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE,30,40,125,20,hwnd,(HMENU)1,0,0);
            TimeEdit = CreateWindowEx(0,"EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_NUMBER|ES_AUTOHSCROLL,165,40,70,25,hwnd,(HMENU)2,0,0);

            ChoiceGroupBox = CreateWindowEx(0,"BUTTON","按键选择",WS_CHILD|WS_VISIBLE|BS_GROUPBOX,25,120,350,100,hwnd,(HMENU)3,0,0);

            RadioButtonLeft = CreateWindowEx(0,"BUTTON","左键",WS_GROUP|WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,5,30,80,40,ChoiceGroupBox,(HMENU)4,0,0);
            RadioButtonMid = CreateWindowEx(0,"BUTTON","中键",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,120,30,80,40,ChoiceGroupBox,(HMENU)5,0,0);
            RadioButtonRight = CreateWindowEx(0,"BUTTON","右键",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,225,30,80,40,ChoiceGroupBox,(HMENU)6,0,0);

            PositionList = CreateWindowEx(0,"LISTBOX","坐标",WS_CHILD|WS_BORDER|WS_VISIBLE|LBS_STANDARD^LBS_SORT,25,255,180,210,hwnd,(HMENU)7,0,0);
            AddButton = CreateWindowEx(0,"BUTTON","添加",WS_CHILD|WS_BORDER|WS_VISIBLE|BS_PUSHBUTTON|BS_FLAT,25,480,40,25,hwnd,(HMENU)71,0,0);
            DeleteButton = CreateWindowEx(0,"BUTTON","删除",WS_CHILD|WS_BORDER|WS_VISIBLE|BS_PUSHBUTTON|BS_FLAT,75,480,40,25,hwnd,(HMENU)72,0,0);
            ClearButton = CreateWindowEx(0,"BUTTON","清空",WS_CHILD|WS_BORDER|WS_VISIBLE|BS_PUSHBUTTON|BS_FLAT,125,480,40*2,25,hwnd,(HMENU)73,0,0);

            TextPosition = CreateWindowEx(0,"STATIC","坐标（Ctrl+O锁定）",WS_BORDER|WS_CHILD|WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE,250,255,130,20,hwnd,(HMENU)8,0,0);
            PositionXEdit = CreateWindowEx(0,"EDIT","",WS_CHILD|WS_VISIBLE|ES_NUMBER|ES_AUTOHSCROLL|ES_READONLY|WS_BORDER,240,300,70,25,hwnd,(HMENU)9,0,0);
            PositionYEdit = CreateWindowEx(0,"EDIT","",WS_CHILD|WS_VISIBLE|ES_NUMBER|ES_AUTOHSCROLL|ES_READONLY|WS_BORDER,315,300,70,25,hwnd,(HMENU)10,0,0);

            StartButton = CreateWindowEx(0,"BUTTON","开始(Ctrl+S)",WS_CHILD|WS_BORDER|WS_VISIBLE|BS_PUSHBUTTON|BS_FLAT,230,400,95,35,hwnd,(HMENU)11,0,0);
            EndButton = CreateWindowEx(0,"BUTTON","停止(Ctrl+E)",WS_CHILD|WS_BORDER|WS_VISIBLE|BS_PUSHBUTTON|BS_FLAT,230,435,95,35,hwnd,(HMENU)12,0,0);

            SendMessage(ChoiceGroupBox,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(RadioButtonLeft,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(RadioButtonMid,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(RadioButtonRight,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(TextTime,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(TimeEdit,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(StartButton,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(EndButton,WM_SETFONT,(WPARAM)hFont,0);

            SendMessage(PositionList,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(AddButton,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(DeleteButton,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(ClearButton,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(TextPosition,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(PositionXEdit,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(PositionYEdit,WM_SETFONT,(WPARAM)hFont,0);
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage (0);
            break;
        }
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
