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

WorkedComputer::WorkedComputer(
    string statusOfWork,
    int serviceCostWorked,
    int daysWithoutRepair
    ):
	m_statusOfWork{statusOfWork},
	m_serviceCostWorked{serviceCostWorked},
    m_daysWithoutRepair{daysWithoutRepair}
{
};

WorkedComputer:: WorkedComputer(const WorkedComputer &other)
{
	m_statusOfWork = other.m_statusOfWork;
    m_serviceCostWorked = other.m_serviceCostWorked;
    m_daysWithoutRepair = other.m_daysWithoutRepair;
};

WorkedComputer::WorkedComputer(WorkedComputer &&other) noexcept
{
	m_statusOfWork = other.m_statusOfWork;
    m_serviceCostWorked = other.m_serviceCostWorked;
    m_daysWithoutRepair = other.m_daysWithoutRepair;
}

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

void WorkedComputer::SetDays(int days)
{
	cout << "Write days without Repair"<< endl;
    cin >> days;
    m_daysWithoutRepair = days;
};

int WorkedComputer::GetDays()
{
	return m_daysWithoutRepair;
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