#include <windows.h>
#include <windowsx.h> 

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc,0,sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc; /* This is where we will send messages to */
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.style = CS_HREDRAW|CS_VREDRAW; 

    wc.hbrBackground = 0;        //解决闪烁问题. 
    wc.lpszClassName = "ScreenDisplay";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_TOPMOST|WS_EX_LAYERED,"ScreenDisplay","ScreenDisplay",WS_VISIBLE|WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, /* x */CW_USEDEFAULT, /* y */
        640, /* width */
        480, /* height */
        NULL,NULL,hInstance,NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }
    
    ::SetLayeredWindowAttributes(hwnd,0,255,LWA_ALPHA);    //客户区不再显示本窗口 
    
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); /* Translate key codes to chars if present */
        DispatchMessage(&msg); /* Send it to WndProc */
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc;
    static HDC hSrcDC;
    static RECT DeskTop,Client; 
    static PAINTSTRUCT ps;
    static int cx = 480;
    static int cy = 640;
    switch(Message)
    {
        case WM_CREATE:
        {
            GetWindowRect(GetDesktopWindow(),&DeskTop);
            SetTimer(hwnd,1,100,0);
            break;
        }
        
        case WM_TIMER:
        {
            InvalidateRect(hwnd,NULL,TRUE);
            break;
        }
        
        case WM_SIZE:
        {
            cx = GET_X_LPARAM(lParam);
            cy = GET_Y_LPARAM(lParam);
            break; 
        }
        
        case WM_PAINT:
        {
            hdc = BeginPaint(hwnd,&ps);
            hSrcDC = GetDC(NULL);
            SetStretchBltMode(hdc,COLORONCOLOR);
            StretchBlt(hdc,0,0,cx,cy,hSrcDC,0,0,DeskTop.right - DeskTop.left,DeskTop.bottom - DeskTop.top,SRCCOPY);
            EndPaint(hwnd,&ps);
            ReleaseDC(hwnd,hSrcDC);
            break; 
        }
        
        case WM_KILLFOCUS:
        {
            SetFocus(hwnd);
            break; 
        }
        
        case WM_DESTROY:
        {
            KillTimer(hwnd,1);
            PostQuitMessage(0);
            break;
        }
        
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}
