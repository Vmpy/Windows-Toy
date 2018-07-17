#ifndef PLANECLASS_H_INCLUDED
#define PLANECLASS_H_INCLUDED

#include <windows.h>
#include "FlyingMonsterClass.h"

class PlaneClass
{
    public:
    int x;
    int y;
    int Width = 100;
    int Height = 100;
    wchar_t* PngName = (wchar_t*)L"Plane.png";
    int HP = 100;

    bool IsDead = false;

    PlaneClass(void){}

    void Destroyed(FlyingMonsterClass& Monster)
    {
        RECT rcSelf;
        RECT rcMonster;
        RECT Tmp;

        rcSelf.left = x;
        rcSelf.top = y;
        rcSelf.right = x+Width;
        rcSelf.bottom = y+Height;

        rcMonster.left = Monster.x;
        rcMonster.top = Monster.y;
        rcMonster.right = Monster.x+Monster.Width;
        rcMonster.bottom = Monster.y+Monster.Height;

        if(IntersectRect(&Tmp,&rcSelf,&rcMonster))
        {
            IsDead = true;
        }
    }
};

#endif // PLANECLASS_H_INCLUDED
