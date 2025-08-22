#include "WorkedComputer.h"
#include "Computer.h"
#include <iostream>

using namespace std;

WorkedComputer::WorkedComputer():
	m_statusOfWork{"Unknown"},
	m_serviceCostWorked{0},
    m_daysWithoutRepair{0}
{
};

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

int WorkedComputer::ServiceCost()
{
  	int serviceCost;
    cout << "Write Service cost" << endl;
    cin >> serviceCost;
    m_serviceCostWorked = serviceCost;
    return m_serviceCostWorked;
};

WorkedComputer::~WorkedComputer()
{
    cout << "Destructor of Worked class" << endl;
};