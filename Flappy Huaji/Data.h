#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <gdiplus.h>
using namespace Gdiplus;

const int WindowWidth = 800;
const int WindowHeight = 600;

const int FullXinxianHeight = 30*10;    //png素材高度（单位：像素）

const int MaxYinxianNum = 8;

class HuajiClass
{
    public:
    const int x = 30*4;
    int y = WindowHeight/2-30;
    const int Width = 30*2;
    const int Height = 30*2;
    const int DownSpeed = 3;
    const int UpSpeed = 35;

    void Flyup(void)
    {
        y -= UpSpeed;
    }

    void DropDown(void)
    {
        y += DownSpeed;
    }

    void Restart(void)
    {
        ;
    }
};

class YinxianClass
{
    public:
    bool Direct;
    int Pos;
    const int Width = 30*2;
    int Height;

    void RandomGernerate(int x,int y)
    {
        Pos = x;
        Height = 30*(rand()%7+1);
    }

    void Move(void)
    {
        Pos-=2;
    }

    void DeathAndRelive(void)
    {
        if (Pos < 0)
        {
            RandomGernerate(WindowWidth,WindowHeight);
        }
    }

    void Restart(void)
    {
        ;
    }
};

class GameClass
{
    public:
    HuajiClass Huaji;                       //滑稽主角对象.
    YinxianClass Yinxian[MaxYinxianNum];    //MaxYinxianNum数量的障碍物.
    HWND Window;
    bool IsPause = false;
    bool IsGameOver = false;
    unsigned int Score = 0;

    GameClass(void)
    {
        int ClientX = WindowWidth;
        int ClientY = WindowHeight;
        //开场布局总是很伤脑筋
        for(int i = 0;i < MaxYinxianNum;i++)
        {
            Yinxian[i].RandomGernerate(ClientX,ClientY);

            if(i <= 3)
            {
                Yinxian[i].Pos = ClientX/3 + i*Yinxian[i].Width*2;
                Yinxian[i].Direct = true;
                Yinxian[i].Height = (rand()%7+1)*30;
            }
            else
            {
                Yinxian[i].Pos = ClientX/3 + (i-3)*Yinxian[i].Width*2;
                Yinxian[i].Direct = false;
                Yinxian[i].Height = (rand()%7+1)*30;
            }
        }
    }

    bool DrawHuaji(HDC hdc)
    {
        Image Image((wchar_t*)L"Res\\滑稽.png");
        if(Image.GetLastStatus() != Status::Ok)
        {
            KillTimer(Window,0);
            MessageBox(0,"文件数据丢失!",NULL,MB_OK|MB_ICONERROR);
            DestroyWindow(Window);
            return false;
        }

        Graphics Graph(hdc);
        Graph.DrawImage(&Image,RectF(Huaji.x,Huaji.y,Huaji.Width,Huaji.Height));
        return true;
    }

    bool DrawYinxian(HDC hdc)
    {
        RECT rect;
        GetClientRect(Window,&rect);

        Image Image((wchar_t*)L"Res\\阴险.png");
        if(Image.GetLastStatus() != Status::Ok)
        {
            KillTimer(Window,0);
            MessageBox(0,"文件数据丢失!",NULL,MB_OK|MB_ICONERROR);
            DestroyWindow(Window);
            return false;
        }

        Graphics Graph(hdc);
        for(int i=0;i < MaxYinxianNum;i++)
        {
            switch(Yinxian[i].Direct)
            {
                case true:Graph.DrawImage(&Image,Yinxian[i].Pos,0,0,0,30*2,Yinxian[i].Height,UnitPixel);break;
                case false:Graph.DrawImage(&Image,Yinxian[i].Pos,rect.bottom-Yinxian[i].Height,0,0,30*2,Yinxian[i].Height,UnitPixel);break;
            }
        }
        return true;
    }

    void Restart(void)
    {
        int ClientX = WindowWidth;
        int ClientY = WindowHeight;

        Huaji.Restart();
        for(auto i:Yinxian)
        {
            i.Restart();
        }

        //开场布局总是很伤脑筋
        for(int i = 0;i < MaxYinxianNum;i++)
        {
            Yinxian[i].RandomGernerate(ClientX,ClientY);

            if(i <= 3)
            {
                Yinxian[i].Pos = ClientX/3 + i*Yinxian[i].Width*2;
                Yinxian[i].Direct = true;
                Yinxian[i].Height = (rand()%7+1)*30;
            }
            else
            {
                Yinxian[i].Pos = ClientX/3 + (i-3)*Yinxian[i].Width*2;
                Yinxian[i].Direct = false;
                Yinxian[i].Height = (rand()%7+1)*30;
            }
        }

    }

    bool GameOver(void)
    {
        RECT rect;
        GetClientRect(Window,&rect);

        if(Huaji.y < 0 || Huaji.y > rect.bottom)
        {
            IsGameOver = true;
            return true;
        }

        for(int i = 0;i < MaxYinxianNum;i++)
        {
            RECT Tmp;

            RECT HuajiRect;
            RECT YinxianRect;
            HuajiRect.left = Huaji.x;
            HuajiRect.right = Huaji.x+Huaji.Width-8; //这里-8是为了容错png图片的透明间隙.
            HuajiRect.top = Huaji.y;
            HuajiRect.bottom = Huaji.y+Huaji.Height-8;//这里-8是为了容错png图片的透明间隙.

            switch(Yinxian[i].Direct)
            {
                case true:
                {
                    YinxianRect.left = Yinxian[i].Pos;
                    YinxianRect.right = Yinxian[i].Pos+Yinxian[i].Width;
                    YinxianRect.top = 0;
                    YinxianRect.bottom = Yinxian[i].Height;
                    break;
                }
                case false:
                {
                    YinxianRect.left = Yinxian[i].Pos;
                    YinxianRect.right = Yinxian[i].Pos+Yinxian[i].Width;
                    YinxianRect.top = rect.bottom-Yinxian[i].Height;
                    YinxianRect.bottom = rect.bottom;
                    break;
                }
            }

            if(IntersectRect(&Tmp,&HuajiRect,&YinxianRect))
            {
                IsGameOver = true;
                return true;    //当滑稽矩形和阴险矩形有交集的时候，游戏结束.
            }
        }

        IsGameOver = false;
        return false;
    }

    void Pause(void)
    {
        //暂停与不暂停的转化.
        IsPause = !IsPause;
    }
};

#endif // DATA_H_INCLUDED
