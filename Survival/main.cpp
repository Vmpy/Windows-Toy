#include <iostream>
#include <cstdio>

#include "Data.h"
#include "Functions.h"

using namespace std;

Human Me;
NatureEvent NE;

int main()
{
    FirstMenu(Me);
    DisplayInformation(Me,NE);
    return 0;
}
