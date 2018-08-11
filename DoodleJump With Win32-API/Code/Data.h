#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#define MAX_WIDTH 360
#define MAX_HEIGHT 640

#define MAX_ARRSIZE 8
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
        if(y > MAX_HEIGHT)          //当踏板的位置到达屏幕不可见的位置时就重写数据
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

class FloorMoveClass:public FloorClass
{
    public:
    bool MoveDirection = false;         //踏板移动方向:左(false)右(true)
    bool IsHave = true;                 //移动踏板由概率生成，标志游戏场景中是否存在移动踏板

    void SetIsHave(void)
    {
        if(rand()%100 > 30)
        {
            IsHave = true;
        }
        else
        {
            IsHave = false;
        }
    }

    void ReBorn(void)
    {
        if(y > MAX_HEIGHT)
        {
            SetIsHave();
            x = rand()%MAX_WIDTH;
            y = rand()%(width+1) + 15;
            width = rand()%100+35;
        }
    }

    void SetMoveDirection(void)
    {
        if(x <= 0)
        {
            MoveDirection = true;
        }
        if(x >= MAX_WIDTH)
        {
            MoveDirection = false;
        }
    }

    void Move(void)
    {
        SetMoveDirection();
        y+=1;

        if(MoveDirection)
        {
            x++;
        }
        else
        {
            x--;
        }
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
    int MaxJumpHeight = 125;    //极限跳跃高度.
    int CountJumpPixel = 0;     //当前已经跳跃的像素高度
    bool IsDead = false;

    //左右移动.
    void Move(char Directiton)
    {
        switch(Directiton)
        {
            case 'D':
            {
                if(x < MAX_WIDTH-Width)
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
    void SetJumpDirection(FloorMoveClass MoveF,FloorClass* Arr,int Size)
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

        if((x+Width) > MoveF.x && (x) < (MoveF.x+MoveF.width) && (y+Height) == MoveF.y && UpOrDown == false && MoveF.IsHave)
        {
            UpOrDown = true;
            CountJumpPixel=0;
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

    void Death(void)
    {
        if(y > MAX_HEIGHT)
        {
            IsDead = true;
        }
    }
};

class GameClass
{
    public:
    FloorClass Floor[MAX_ARRSIZE];
    DoodleClass Doodle;
    FloorMoveClass FloorMove;

    int Score = 0;

    void First(void)
    {
        int BlankHeight = MAX_HEIGHT/MAX_ARRSIZE;
        for(int i = 0;i < MAX_ARRSIZE;i++)
        {
            Floor[i].x = rand()%MAX_WIDTH;
            Floor[i].width = rand()%100+35;
            Floor[i].y = i*BlankHeight;
        }

        Doodle.x = Floor[MAX_ARRSIZE-1].x + Doodle.Width;
        Doodle.y = Doodle.Height;
    }

    bool DrawSight(HDC hdc)
    {
        Image ImageDoodle((wchar_t*)L"Res\\Doodle.png");
        Image ImageFloor((wchar_t*)L"Res\\Floor_normal.png");
        Image ImageSky((wchar_t*)L"Res\\Sky.png");
        Image ImageMoveFloor((wchar_t*)L"Res\\Floor_move.png");

        if(ImageDoodle.GetLastStatus() != Status::Ok || ImageFloor.GetLastStatus() != Status::Ok || ImageMoveFloor.GetLastStatus() != Status::Ok)
        {
            return false;
        }

        Graphics Graph(hdc);
        Graph.DrawImage(&ImageDoodle,RectF(Doodle.x,Doodle.y,Doodle.Width,Doodle.Height));
        for(int i = 0;i < MAX_ARRSIZE;i++)
        {
            Graph.DrawImage(&ImageFloor,RectF(Floor[i].x,Floor[i].y,Floor[i].width,Floor[i].height));
        }

        if(FloorMove.IsHave)
        {
            Graph.DrawImage(&ImageMoveFloor,RectF(FloorMove.x,FloorMove.y,FloorMove.width,FloorMove.height));
        }
        Score++;
        return true;
    }
};


#endif // DATA_H_INCLUDED
