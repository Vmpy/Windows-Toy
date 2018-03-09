#include <windows.h>

const int Time = 1;

LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;

	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc;
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "CloseWindowLOL";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"CloseWindowLOL","CloseWindowLOL",NULL,
		   CW_USEDEFAULT,CW_USEDEFAULT,0,0,NULL,NULL,hInstance,NULL);
		
	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(GetMessage(&msg,NULL,0,0) > 0)
	{ 
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
	static HWND hWILLBeClosed = 0x0;
	
	switch(Message)
	{
		case WM_TIMER:
		{
			if(wParam == Time)
			{
				//此处的类名可用SPY++手动查找. 
				hWILLBeClosed = FindWindowW((LPCWSTR)L"PP11FrameClass",NULL);
				if(hWILLBeClosed)
				{
					SendMessage(hWILLBeClosed,WM_CLOSE,0,0);
				}
				hWILLBeClosed = FindWindowW((LPCWSTR)L"PP12FrameClass",NULL);
				if(hWILLBeClosed)
				{
					SendMessage(hWILLBeClosed,WM_CLOSE,0,0);
				}
				hWILLBeClosed = FindWindowW((LPCWSTR)L"PPTFrameClass",NULL);
				if(hWILLBeClosed)
				{
					SendMessage(hWILLBeClosed,WM_CLOSE,0,0);
				}
				hWILLBeClosed = FindWindowW((LPCWSTR)L"PP10FrameClass",NULL);
				if(hWILLBeClosed)
				{
					SendMessage(hWILLBeClosed,WM_CLOSE,0,0);
				}
			}
			break;
		} 
		case WM_CREATE:
		{
			SetTimer(hwnd,Time,100,NULL); 
			break; 
		} 
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

		default:
			return DefWindowProc(hwnd,Message,wParam,lParam);
	}
}
