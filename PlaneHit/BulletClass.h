#ifndef BULLETCLASS_H_INCLUDED
#define BULLETCLASS_H_INCLUDED

class BulletClass
{
    public:
    int x;
    int y;
    int width = 25;
    int height = 25;
    wchar_t* PngName = (wchar_t*)L"Res\\Bullet.png";
    bool IsOutPut = false;

    BulletClass(void){}

    void Move(void)
    {
        y-=20;
    }

};

#endif // BULLETCLASS_H_INCLUDED
