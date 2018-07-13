#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <cstdlib>

struct Animals
{
    char Name[20];
    int num;
    int Weight; //kg
    Animals* Next;
};

class Human
{
    public:
    char Name[20];
    unsigned int Life;
    unsigned int Power;
    float Height;//cm
    float Weight;//kg
    float BMI;
    bool Sex;
    unsigned int Age;

    enum PlaceEn {Home,Forest,River,MonsterIsland} m_Place = Home;

    class Asset
    {
        public:
        class Land
        {
            public:
            int Area = 0; //平方米
            enum dampness {Dry,Mid,Wet} m_Dampness = Mid;
        };
        class Animal
        {
            public:
            Animals * Header = nullptr;
        };
        class House
        {
            public:
            int Area = 0;
            int FloorNum = 0;
        };
        class Weapon
        {
            enum WeaponType {Gun,Sword,Fist} m_Type = Fist;
            int LifeTime = 0;
            int Power = 5;
        };

        Land m_Land;
        Animal m_Animal;
        House m_House;
        Weapon m_Weapon;
    };

    Asset m_Asset;
};

class NatureEvent
{
    public:
    enum Time {Morning,Noon,Afternoon,Night} m_Time = Morning;
    enum Season {Spring,Summer,Fall,Winter} m_Season = Spring;
    enum dampness {Dry,Mid,Wet} m_Dampness = Mid;
    int Temperature = 15;
};

class Place
{
    class Forest
    {
        bool Trees[200];
        bool Sheep[20];
        bool Bull[20];
        bool Horse[10];
    };
    class River
    {
        bool Fish[50];
        bool Snake[10];
    };
    class MonsterIsland
    {
        bool Zombie[10];
        bool Wolves[10];
        bool Snake[10];
        bool WaterMonster[2];
    };

    Forest m_Forest;
    River m_River;
    MonsterIsland m_MonsterIsland;
};

#endif // DATA_H_INCLUDED
