#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#define MAX_WIDTH 360
#define MAX_HEIGHT 640

#define MAX_ARRSIZE 10
#define ID_TIMER 1

class FloorClass
{
    public:
    int x;
    int y;

    int width;
    int height = 15;

    void ReBorn(void)
    {
        x = rand()%MAX_WIDTH;
        y = 0;
        width = rand()%50+25;
    }

    void Move(void)
    {
        y+=4;
    }
};

class DoodleClass
{
    public:
    int x;
    int y;
    int Width = 40;
    int Height = 40;

    bool UpOrDown = false;
    int MaxJumpHeight = 120;
    int CountJumpPixel = 0;
    bool IsDead = false;

    //左右移动.
    void Move(char Directiton)
    {
        switch(Directiton)
        {
            case 'D':
            {
                if(x < MAX_WIDTH)
                {
                    x++;
                }
                break;
            }
            case 'A':
            {
                if(x > 0)
                {
                    x--;
                }
                break;
            }
        }
    }

    //设置跳跃方向（落下[false]或者上升[true])
    void SetJumpDirection(FloorClass* Arr,int Size)
    {
        for(int i = 0;i < MAX_ARRSIZE;i++)
        {
            if(x > Arr[i].x && (x) < (Arr[i].x+Arr[i].width) && (y+Height) == Arr[i].y)
            {
                UpOrDown = true;
                CountJumpPixel=0;
            }
        }
    }

    //设置y坐标值
    void Jump(void)
    {
        if(UpOrDown)
        {
            y-=1;
            CountJumpPixel++;
        }
        else
        {
            y+=1;
            CountJumpPixel--;
        }

        if(CountJumpPixel >= MaxJumpHeight)
        {
            UpOrDown = false;
        }
    }
};

class GameClass
{
    public:
    FloorClass Floor[MAX_ARRSIZE];
    DoodleClass Doodle;

    GameClass(void)
    {
        int BlankHeight = MAX_HEIGHT/MAX_ARRSIZE;
        for(int i = 0;i < MAX_ARRSIZE;i++)
        {
            Floor[i].ReBorn();
            Floor[i].y = i*BlankHeight;
        }

        Doodle.x = Floor[9].x + 5;
        Doodle.y = Floor[9].y - Doodle.Height;
    }

    void DrawSight(HDC hdc)
    {
        Image ImageDoodle((wchar_t*)L"Res\\Doodle.png");
        Image ImageFloor((wchar_t*)L"Res\\Floor_normal.png");
        Image ImageSky((wchar_t*)L"Res\\Sky.png");
        if(ImageDoodle.GetLastStatus() != Status::Ok || ImageFloor.GetLastStatus() != Status::Ok)
        {
            MessageBox(0,"文件数据丢失!",NULL,MB_OK|MB_ICONERROR);
        }

        Graphics Graph(hdc);
        Graph.DrawImage(&ImageDoodle,RectF(Doodle.x,Doodle.y,Doodle.Width,Doodle.Height));
        for(int i = 0;i < MAX_ARRSIZE;i++)
        {
            Graph.DrawImage(&ImageFloor,RectF(Floor[i].x,Floor[i].y,Floor[i].width,Floor[i].height));
        }
    }
};


#endif // DATA_H_INCLUDED
