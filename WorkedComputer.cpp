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

WorkedComputer::WorkedComputer(const WorkedComputer &other)
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
    cout << "set status PC \"1 if Working \\ 2 if Turned Off\" << endl";
    cin >> k;
    switch (k)
    {
         case 1:

           m_statusOfWork = "Working";
           break;

         case 2:
           m_statusOfWork = "Turned off";
           break;

        default:
           throw Exeption("Wrong number");
           break;
    };
};

void WorkedComputer::SetCountUsers(int users)
{
    if (users < 0) throw Exeption("Count of users must 0 or positive");
    m_countUsers = users;
}

void WorkedComputer::SetDays(int days)
{
    if (days < 0) throw Exeption("Days without repair must be 0 or positive");
    m_daysWithoutRepair = days;
};

int WorkedComputer::GetDays() const
{
	return m_daysWithoutRepair;
};

int WorkedComputer::GetCountUsers() const
{
    return m_countUsers;
}


int WorkedComputer::ServiceCost()
{
  	int serviceCost;
    cout << "Write Service cost" << endl;
    cin >> serviceCost;
    if (serviceCost < 0) throw Exeption("Service cost must be 0 or positive");
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

bool WorkedComputer::IsWorking()
{
    if (m_statusOfWork == "Working")
    {
        return true;
    }
    else
    {;
        return false;
    }
}


WorkedComputer::~WorkedComputer()
{
    cout << "Destructor of Worked class" << endl;
};