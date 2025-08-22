#include "WorkedComputer.h"
#include "Computer.h"
#include <iostream>

using namespace std;

WorkedComputer::WorkedComputer(): m_statusOfWork{"Unknown"} {};

void WorkedComputer::ShowStatus()
{
    cout <<"Status: " << m_statusOfWork << endl;
};

void WorkedComputer::UpdateStatus()
{
    int k;
    cout << "set status PC \"1 if Working \\ 2 if Turned Off";
    cin >> k;
    switch (k)
    {
         case 1:

           m_statusOfWork = "Working";
           break;

         case 2:
           m_statusOfWork = "Turned off";
           break;
    };
};