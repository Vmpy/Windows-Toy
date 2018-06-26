#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM); 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW^WS_THICKFRAME^WS_MAXIMIZEBOX,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		300, /* width */
		600, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
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
     
	switch(Message)
    {
        case WM_CREATE:
        {
            Edit = CreateWindowEx(0,"edit","",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOVSCROLL|ES_MULTILINE,0,0,300,300,hwnd,0,0,0);
            StartButton = CreateWindowEx(0,"button","开始",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOVSCROLL|ES_MULTILINE,25,350,60,30,hwnd,(HMENU)1,0,0);
            EndButton = CreateWindowEx(0,"button","停止",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOVSCROLL|ES_MULTILINE,25,350,60,30,hwnd,(HMENU)2,0,0);
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
                SetFocus(Edit);
                SetTimer(hwnd,1001,500,0);
            }
            else if((HWND)lParam == EndButton)
            {
                KillTimer(hwnd,1001);
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
