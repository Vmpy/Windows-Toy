#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <windows.h>


class Doodle
{
    public:
    char FileName[12] = "Doodle.png";
    int x;
    int y;
    int Width;
    int Height;
    int MaxJumpHeight;
    bool IsDead = false;
};


#endif // DATA_H_INCLUDED
