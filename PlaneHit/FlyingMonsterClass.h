#ifndef FLYINGMONSTERCLASS_H_INCLUDED
#define FLYINGMONSTERCLASS_H_INCLUDED

#include <windows.h>
#include "PlaneClass.h"
#include "BulletClass.h"

class FlyingMonsterClass
{
    public:
    int x;
    int y;
    int Width = 50;
    int Height = 50;
    int HP = 25;
    wchar_t* PngName = (wchar_t*)L"Res\\Target.png";
    bool IsDead = false;

    FlyingMonsterClass(void)
    {
        x = rand()%750;
        y = rand()%550;
    }

    void Move(int X,int Y)
    {
        if(X> x) //飞机位于右边
        {
            x++;
        }
        else if(X < x) //飞机位于左边
        {
            x--;
        }
        if(Y > y) //飞机位于下面
        {
            y++;
        }
        else if(Y < y) //飞机位于上面
        {
            y--;
        }
    }

    void Destroyed(const BulletClass& Bullet)
    {
        RECT rcSelf;
        RECT rcBullet;
        RECT Tmp;

        rcSelf.left = x;
        rcSelf.top = y;
        rcSelf.right = x+Width;
        rcSelf.bottom = y+Height;

        rcBullet.left = Bullet.x;
        rcBullet.top = Bullet.y;
        rcBullet.right = Bullet.x+Bullet.width;
        rcBullet.bottom = Bullet.y+Bullet.height;

        if(IntersectRect(&Tmp,&rcSelf,&rcBullet))
        {
            IsDead = true;
        }

        if(HP <= 0)
        {
            IsDead = true;
        }
    }

    void ReLive(void)
    {
        if(IsDead)
        {
            x = rand()%750;
            y = rand()%550;
        }
    }
};

#endif // FLYINGMONSTERCLASS_H_INCLUDED
