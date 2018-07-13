#include <iostream>
#include <fstream>
#include <string>
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
    Player.Power = 10;
    Player.Life = 120;
}

void ReadPlayer(Human& Player)
{
    string FileName;
    cout << "请输入文件完整名称:" << flush;
    getline(cin,FileName);

    fstream File;
    File.open(FileName.c_str(),ios::in|ios::binary);

    File.read((char*)&Player,sizeof(Human));
    File.close();
}

void SavePlayer(Human& Player)
{
    string FileName;
    cout << "请输入文件完整名称:" << flush;
    getline(cin,FileName);

    fstream File;
    File.open(FileName.c_str(),ios::in|ios::binary);

    File.write((char*)&Player,sizeof(Human));
    File.close();
}

void FirstMenu(Human& Player)
{
    int choice = 0;
    cout << "***************欢迎进入《原地生存》游戏***************" << endl;
    cout << "               1.创建人物;" << endl;
    cout << "               2.读取存档.\n" << endl;
    cin >> choice;
    switch(choice)
    {
        case 1:InitPlayer(Player);break;
        case 2:ReadPlayer(Player);break;
    }
}


void PlayGame(Human& Player,NatureEvent& NE)
{

}

void MainMenu(Human& Player,NatureEvent& NE)
{
    int choice = 0;
    cout << "***************《原地生存》游戏主菜单***************" << endl;
    cout << "               1.保存存档;" << endl;
    cout << "               2.进入游戏.\n" << endl;
    cin >> choice;
    switch(choice)
    {
        case 1:SavePlayer(Player);break;
        case 2:PlayGame(Player,NE);break;
    }
}

void DisplayInformation(Human& Player,NatureEvent& NE)
{
    cout << "天气与自然情况:" << endl;
    cout << "时间:" << flush;
    switch(NE.m_Time)
    {
        case NE.Morning:cout << "上午" << endl;break;
        case NE.Noon:cout << "中午" << endl;break;
        case NE.Afternoon:cout << "下午" << endl;break;
        case NE.Night:cout << "夜晚" << endl;break;
    }

    cout << "\n" << flush;
    cout << "季节:" << flush;
    switch(NE.m_Season)
    {
        case NE.Spring:cout << "春天" << endl;break;
        case NE.Summer:cout << "夏天" << endl;break;
        case NE.Fall:cout << "秋天" << endl;break;
        case NE.Winter:cout << "冬天" << endl;break;
    }

    cout << "\n" << flush;
    cout << "空气湿度:" << flush;

    switch(NE.m_Dampness)
    {
        case NE.Dry: cout << "干燥" << endl;break;
        case NE.Mid: cout << "适中" << endl;break;
        case NE.Wet: cout << "潮湿" << endl;break;
    }

    cout << "\n" << flush;
    cout << "环境温度:" << NE.Temperature << "℃" << endl;

    cout << "人物情况：" << endl;
    cout << "姓名:" << Player.Name << endl;
    cout << "年龄:" << Player.Age << "岁" << endl;
    cout << "身高:" << Player.Height << "cm" << endl;
    cout << "体重:" << Player.Weight << "kg" << endl;
    cout << "预计寿命:" << Player.Life << "年" << endl;
    cout << "性别:" << flush;
    Player.Sex?cout << "男":cout << "女";
    cout << "\n";


}
