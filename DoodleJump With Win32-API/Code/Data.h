#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <windows.h>

#define MAX_WIDTH 360
#define MAX_HEIGHT 640

#define MAX_ARRSIZE 10

class FloorClass
{
    public:
    int x;
    int y;

    int width;

    void ReBorn(void)
    {
        x = rand()%MAX_WIDTH;
        y = 0;
        width = rand()%50+15;
    }
};

class DoodleClass
{
    public:
    char FileName[20] = "Res\\Doodle.png";
    int x;
    int y;
    int JumpStartIndex;
    int Width = 10;
    int Height = 10;

    bool UpOrDown = false;
    int MaxJumpHeight = 25;
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

    //获取当前Doodle所踩的踏板下标
    void GetJumpBase(FloorClass* Arr,int Size)
    {
        int Min;
        int Num[Size];
        for(int i = 0;i< Size;i++)
        {
            Num[i] = Arr[i].y-y;      //当地板在人物上方时为负数
        }

        Min = Num[0];

        for(int i = 0;i< Size;i++)
        {
            if(Min > Num[i] && Num[i] >= 0)
            {
                Min = Num[i];
                JumpStartIndex = i;      //找出Num数组中最小的数字的下标
            }
        }
    }

    //设置跳跃方向（落下[false]或者上升[true])
    void SetJumpDirection(FloorClass* Arr,int Size)
    {
        if((Height + y) == Arr[JumpStartIndex].y)
        {
            UpOrDown = true;
        }
        if(y == (Arr[JumpStartIndex].y-MaxJumpHeight))
        {
            UpOrDown = false;
        }
    }

    //设置y坐标值
    void Jump(void)
    {
        if(UpOrDown)
        {
            y--;
        }
        else
        {
            y++;
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

        Doodle.JumpStartIndex = 0;
        Doodle.x = Floor[0].x + 5;
        Doodle.y = Floor[0].y;
    }
};


#endif // DATA_H_INCLUDED
