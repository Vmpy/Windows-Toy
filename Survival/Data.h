#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

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

    class Asset
    {
        public:
        class Land
        {
            public:
            int Area = 0; //平方米
            enum dampness {Dry,Mid,Wet} m_Dampness;
        };
        class Animal
        {
            public:
            Animals * Header;
        };
        class House
        {
            public:
            int Area = 0;
            int FloorNum = 0;
        };
        class Weapon
        {
            enum WeaponType {Gun,Sword,Fist} m_Type = Sword;
            int LifeTime = 0;
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
    enum Time {Morning,Noon,Afternoon,night} m_Time;
    enum Season {Spring,Summer,Fall,Winter} m_Season;
    enum dampness {Dry,Mid,Wet} m_Dampness;
    int Temperature;
};


#endif // DATA_H_INCLUDED
