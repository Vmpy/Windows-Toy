#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "Data.h"

void FirstMenu(Human&);
void MainMenu(Human&,NatureEvent&);
float BMI(float,float);
void InitPlayer(Human&);
void ReadPlayer(Human&);
void SavePlayer(Human&);

void DisplayInformation(Human&,NatureEvent&);

void PlayGame(Human&,NatureEvent&);



#endif // FUNCTIONS_H_INCLUDED
