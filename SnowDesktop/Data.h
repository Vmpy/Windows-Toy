#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <gdiplus.h>
class OneSnow
{
    public:
    int x;
    int y;
    int Width;
    int Height;
    int Type;
    int Direct;
    int StepSize;

    RECT RedrawRect;

    OneSnow(void)
    {
        int cx = GetSystemMetrics(SM_CXSCREEN);
        int cy = GetSystemMetrics(SM_CYSCREEN);
        Type = rand()%6+1;
        Direct = rand()%8+1;
        Height = Width = rand()%50+16;
        x = rand()%cx;
        y = rand()%cy;
        StepSize = rand()%10+1;
    }
    void Move(void)
    {
        RedrawRect.left = x;
        RedrawRect.top = y;
        RedrawRect.right = x+Width;
        RedrawRect.bottom = y+Height;

        switch(Direct)
        {
            //向左移动.
            case 1:
            {
                x-=StepSize;
                break;
            }
            //向右移动
            case 2:
            {
                x+=StepSize;
                break;
            }
            //向上移动
            case 3:
            {
                y-=StepSize;
                break;
            }
            //向下移动
            case 4:
            {
                y+=StepSize;
                break;
            }
            //左上
            case 5:
            {
                x-=StepSize;
                y-=StepSize;
                break;
            }
            //右上
            case 6:
            {
                x+=StepSize;
                y-=StepSize;
                break;
            }
            //左下
            case 7:
            {
                x-=StepSize;
                y+=StepSize;
                break;
            }
            case 8:
            {
                x+=StepSize;
                y+=StepSize;
                break;
            }
        }
        Die();
    }

    void Die(void)
    {
        int cx = GetSystemMetrics(SM_CXSCREEN);
        int cy = GetSystemMetrics(SM_CYSCREEN);
        if(x > cx || x < 0 || y > cy || y < 0)
        {
            Type = rand()%6+1;
            Direct = rand()%8+1;
            Height = Width = rand()%50+16;
            x = rand()%cx;
            y = rand()%cy;
            StepSize = rand()%10+1;
        }
    }

};


#endif // DATA_H_INCLUDED
