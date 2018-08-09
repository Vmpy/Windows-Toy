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
        if(y > MAX_HEIGHT)
        {
            x = rand()%MAX_WIDTH;
            y = 0;
            width = rand()%100+35;
        }
    }

    void Move(void)
    {
        y+=1;
    }
};

class DoodleClass
{
    public:
    int x;
    int y;
    int Width = 40;
    int Height = 40;

    bool UpOrDown = false;      //跳跃方向，落下或者上升
    int MaxJumpHeight = 130;    //极限跳跃高度.
    int CountJumpPixel = 0;     //当前已经跳跃的像素高度
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
                    x+=10;
                }
                break;
            }
            case 'A':
            {
                if(x > 0)
                {
                    x-=10;
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
            //满足条件:除了触碰踏板面还有跳跃方向为落下
            if((x+Width) > Arr[i].x && (x) < (Arr[i].x+Arr[i].width) && (y+Height) == Arr[i].y && UpOrDown == false)
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
            y--;
            CountJumpPixel++;
        }
        else
        {
            y++;
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

    void First(void)
    {
        int BlankHeight = MAX_HEIGHT/MAX_ARRSIZE;
        for(int i = 0;i < MAX_ARRSIZE;i++)
        {
            Floor[i].x = rand()%MAX_WIDTH;
            Floor[i].width = rand()%100+35;
            Floor[i].y = i*BlankHeight;
        }

        Doodle.x = Floor[9].x + Doodle.Width;
        Doodle.y = Doodle.Height;
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
