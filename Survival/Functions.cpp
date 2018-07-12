#include <iostream>
#include <cstdio>

#include "Data.h"

using namespace std;

float BMI(float Height,float Weight)
{
    return Weight/((Height/100)*(Height/100));
}

void InitPlayer(Human& Player)
{
    cout << "请输入要创建的人物名称：" << endl;
    cin >> Player.Name;
    cout << "请输入人物年龄:" << endl;
    cin >> Player.Age;
    cout << "请输入人物身高(cm):" << endl;
    cin >> Player.Height;
    cout << "请输入人物体重(kg):" << endl;
    cin >> Player.Weight;

    Player.BMI = BMI(Player.Height,Player.Weight);
}
