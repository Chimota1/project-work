#include "WorkedComputer.h"
#include "Computer.h"
#include <iostream>

using namespace std;

WorkedComputer::WorkedComputer():
    Computer(),
	m_statusOfWork{"Unknown"},
	m_serviceCostWorked{0},
    m_daysWithoutRepair{0},
    m_countUsers{0}
{
};

WorkedComputer::WorkedComputer(
    string statusOfWork,
    int serviceCostWorked,
    int daysWithoutRepair,
    int countUsers
    ):
    Computer(),
	m_statusOfWork{statusOfWork},
	m_serviceCostWorked{serviceCostWorked},
    m_daysWithoutRepair{daysWithoutRepair},
    m_countUsers{countUsers}
{
};

WorkedComputer:: WorkedComputer(const WorkedComputer &other)
{
	this->m_statusOfWork = other.m_statusOfWork;
    this->m_serviceCostWorked = other.m_serviceCostWorked;
    this->m_daysWithoutRepair = other.m_daysWithoutRepair;
    this->m_countUsers = other.m_countUsers;
};

WorkedComputer::WorkedComputer(WorkedComputer &&other) noexcept
{
	this->m_statusOfWork = other.m_statusOfWork;
    this->m_serviceCostWorked = other.m_serviceCostWorked;
    this->m_daysWithoutRepair = other.m_daysWithoutRepair;
    this->m_countUsers = other.m_countUsers;
}

void WorkedComputer::ShowStatus()
{
    cout <<"Status of Worked PC: " << m_statusOfWork << endl;
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

void WorkedComputer::SetCountUsers(int users)
{
    cout << "Set count Users" << endl;
    cin >> users;
    m_countUsers = users;
}

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

int WorkedComputer::GetCountUsers()
{
    return m_countUsers;
}


int WorkedComputer::ServiceCost()
{
  	int serviceCost;
    cout << "Write Service cost" << endl;
    cin >> serviceCost;
    m_serviceCostWorked = serviceCost;
    return m_serviceCostWorked;
};

void WorkedComputer::TurnOn()
{
    m_statusOfWork = "Working";
}

void WorkedComputer::TurnOff()
{
    m_statusOfWork = "Turned off";
}


WorkedComputer::~WorkedComputer()
{
    cout << "Destructor of Worked class" << endl;
};