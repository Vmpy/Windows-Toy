#ifndef PLANECLASS_H_INCLUDED
#define PLANECLASS_H_INCLUDED

#include <windows.h>
#include "FlyingMonsterClass.h"
#include "BulletClass.h"
#include "Data.h"

class PlaneClass
{
    public:
    int x = 400-100;
    int y = 450;
    int Width = 100;
    int Height = 100;
    wchar_t* PngName = (wchar_t*)L"Res\\Plane.png";
    int HP = 100;

    bool IsDead = false;

    BulletClass Bullet[MAX_BULLET];

    PlaneClass(void){}

    void Move(int Type)
    {
        switch(Type)
        {
            case 'W':
            {
                if(y > 0)
                {
                    y-=5;
                }
                break;
            }
            case 'S':
            {
                if(y < 500)
                {
                    y+=5;
                }
                break;
            }
            case 'A':
            {
                if(x > 0)
                {
                    x-=5;
                }
                break;
            }
            case 'D':
            {
                if(x < 700)
                {
                    x+=5;
                }
                break;
            }
            default:break;
        }

    }

    void Destroyed(FlyingMonsterClass& Monster)
    {
        RECT rcSelf;
        RECT rcMonster;
        RECT Tmp;

        rcSelf.left = x + 20;
        rcSelf.top = y + 20;
        rcSelf.right = x+Width - 20;
        rcSelf.bottom = y+Height - 20;

        rcMonster.left = Monster.x;
        rcMonster.top = Monster.y;
        rcMonster.right = Monster.x+Monster.Width;
        rcMonster.bottom = Monster.y+Monster.Height;

        if(IntersectRect(&Tmp,&rcSelf,&rcMonster) && !Monster.IsDead)
        {
            IsDead = true;
        }
    }

    void ReFillBullet(void)
    {
        for(int i = 0;i < MAX_BULLET;i++)
        {
            if(Bullet[i].y < 0)
            {
                Bullet[i].x = x+50-10;
                Bullet[i].y = y-25;

                if(i > 0 && Bullet[i].y == Bullet[i-1].y)       //防止玩家的移动到屏幕顶端再下来的时候图片重叠
                {
                    Bullet[i-1].y -= 50;
                }
            }
        }
    }

    void FillBullet(void)
    {
        for(int i = 0;i < MAX_BULLET;i++)
        {
            if(!Bullet[i].IsOutPut)
            {
                Bullet[i].x = x+50-10;
                Bullet[i].y = y-25;
            }
        }
    }

    void MoveBullet(void)
    {
        for(int i = 0;i < 5;i++)
        {
            if(Bullet[i].IsOutPut)
            {
                Bullet[i].Move();
            }
        }
    }
};

#endif // PLANECLASS_H_INCLUDED
