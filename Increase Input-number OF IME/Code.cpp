#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM); 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc; /* A properties struct of our window */
    HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
    MSG msg; /* A temporary location for all messages */

    /* zero out the struct and set the stuff we want to modify */
    memset(&wc,0,sizeof(wc));
    wc.cbSize         = sizeof(WNDCLASSEX);
    wc.lpfnWndProc     = WndProc; /* This is where we will send messages to */
    wc.hInstance     = hInstance;
    wc.hCursor         = LoadCursor(NULL, IDC_ARROW);
    
    /* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = "IME INCRESE-NUM";
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
    wc.hIconSm         = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"IME INCRESE-NUM","输入法刷字数",WS_VISIBLE|WS_OVERLAPPEDWINDOW^WS_THICKFRAME^WS_MAXIMIZEBOX,
        CW_USEDEFAULT, /* x */
        CW_USEDEFAULT, /* y */
        305, /* width */
        600, /* height */
        NULL,NULL,hInstance,NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); /* Translate key codes to chars if present */
        DispatchMessage(&msg); /* Send it to WndProc */
    }
    return msg.wParam;
}

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    static HWND Edit;
    static HWND StartButton;
    static HWND EndButton;
    static HWND ClearButton;
    
    switch(Message)
    {
        case WM_CREATE:
        {
            HFONT hFont = CreateFont(22,8,0,0,400,FALSE, FALSE, FALSE,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,FF_DONTCARE, TEXT("微软雅黑"));
            
            Edit = CreateWindowEx(0,"edit","",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOVSCROLL|ES_MULTILINE,0,0,300,300,hwnd,0,0,0);
            StartButton = CreateWindowEx(0,"button","开始",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_PUSHBUTTON,25,350,60,30,hwnd,(HMENU)1,0,0);
            EndButton = CreateWindowEx(0,"button","停止",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_PUSHBUTTON,185,350,60,30,hwnd,(HMENU)2,0,0);
            ClearButton = CreateWindowEx(0,"button","清除",WS_CHILD|WS_VISIBLE|WS_BORDER|BS_PUSHBUTTON,100,450,60,30,hwnd,(HMENU)3,0,0);
            
            SendMessage(Edit,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(StartButton,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(EndButton,WM_SETFONT,(WPARAM)hFont,0);
            SendMessage(ClearButton,WM_SETFONT,(WPARAM)hFont,0);
            
            break; 
        }
        
        case WM_TIMER:
        {
            switch(wParam)
            {
                case 1001:
                {
                    keybd_event(68,0,0,0);
                    keybd_event(68,0,KEYEVENTF_KEYUP,0);
                    keybd_event(VK_SPACE,0,0,0);
                    keybd_event(VK_SPACE,0,KEYEVENTF_KEYUP,0);
                    break;
                }
            }
            break; 
        }
        
        case WM_COMMAND:
        {
            if((HWND)lParam == StartButton)
            {
                if(MessageBox(hwnd,"请在开始前确认:\n1.当前输入法正确.\n2.输入法输入选项正确(大小写设置).\n","提示",MB_YESNO) == IDYES)
                {
                    SetFocus(Edit);
                    SetTimer(hwnd,1001,50,0);
                }
                else
                {
                    break;
                }
            }
            else if((HWND)lParam == EndButton)
            {
                KillTimer(hwnd,1001);
            }
            else if((HWND)lParam == ClearButton)
            {
                SetWindowText(Edit,"");
            }
            break;
        }
        
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        
        /* All other messages (a lot of them) are processed using default procedures */
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}
