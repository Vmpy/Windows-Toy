#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <windows.h>

#define MAX_WIDTH 720
#define MAX_HEIGHT 1280

class Floor
{
    public:
    int Type;
    int Num;
    int x;
    int y;

    int width;
};

class Doodle
{
    public:
    char FileName[20] = "Res\\Doodle.png";
    int x;
    int y;
    int JumpStartIndex;
    int Width;
    int Height;

    bool UpOrDown;
    int MaxJumpHeight;
    bool IsDead = false;

    void Move(char Directiton)
    {
        switch(Directiton):
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

    void GetJumpBase(Floor* Arr,int Size)
    {
        int Min;
        int Num[Size];
        for(int i = 0;i< Size;i++)
        {
            Num[i] = Arr[i]-y;      //当地板在人物上方时为负数
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


#endif // DATA_H_INCLUDED
