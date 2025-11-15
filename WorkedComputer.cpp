#include "WorkedComputer.h"
#include "Computer.h"
#include "Exeption.h"
#include <string>
#include <iostream>

using namespace std;

WorkedComputer::WorkedComputer():
    Computer(),
	m_statusOfWork{"Unknown"},
	m_serviceCostWorked{0},
    m_daysWithoutRepair{0},
    m_countUsers{0},
    m_employmentStatus{"Freely"}
{
};

WorkedComputer::WorkedComputer(
    string statusOfWork,
    string employmentStatus,
    int serviceCostWorked,
    int daysWithoutRepair,
    int countUsers
    ):
    Computer(),
	m_statusOfWork{statusOfWork},
    m_employmentStatus{employmentStatus},
	m_serviceCostWorked{serviceCostWorked},
    m_daysWithoutRepair{daysWithoutRepair},
    m_countUsers{countUsers}
{
};

WorkedComputer::WorkedComputer(const WorkedComputer &other)
{
	this->m_statusOfWork = other.m_statusOfWork;
    this->m_employmentStatus = other.m_employmentStatus;
    this->m_serviceCostWorked = other.m_serviceCostWorked;
    this->m_daysWithoutRepair = other.m_daysWithoutRepair;
    this->m_countUsers = other.m_countUsers;
};

WorkedComputer::WorkedComputer(WorkedComputer &&other) noexcept
{
    this->m_statusOfWork = other.m_statusOfWork;
    this->m_employmentStatus = other.m_employmentStatus;
    this->m_serviceCostWorked = other.m_serviceCostWorked;
    this->m_daysWithoutRepair = other.m_daysWithoutRepair;
    this->m_countUsers = other.m_countUsers;
}

void WorkedComputer::ShowStatus()
{
    cout <<"Статус робочого комп’ютера: " << m_statusOfWork << endl;
};

void WorkedComputer::UpdateStatus()
{
    int k;
    cout << "Встановіть статус комп’ютера (1 — Freely, 2 — Busy): " << endl;
    cin >> k;
    switch (k)
    {
        case 1:
           m_employmentStatus = "Freely";
        break;

        case 2:
           m_employmentStatus = "Busy";
        break;

        default:
           throw Exeption("Неправильний номер");
    };
};

void WorkedComputer::SetCountUsers(int users)
{
    if (users < 0) throw Exeption("Кількість користувачів повинна бути невід’ємною");
    m_countUsers = users;
}

void WorkedComputer::SetDays(int days)
{
    if (days < 0) throw Exeption("Кількість днів без ремонту повинна бути невід’ємною");
    m_daysWithoutRepair = days;
};

void WorkedComputer::SetEmploymentStatus(const string& status)
{
    if (status != "Freely" && status != "Busy")
        throw Exeption("Невірний статус зайнятості у JSON файлі");
    m_employmentStatus = status;
};


int WorkedComputer::GetDays() const
{
	return m_daysWithoutRepair;
};


int WorkedComputer::GetCountUsers() const
{
    return m_countUsers;
}

int WorkedComputer::GetServiceCost() const
{
    return m_serviceCostWorked;
}

string WorkedComputer::GetEmploymentStatus() const
{
    return m_employmentStatus;
}

void WorkedComputer::ServiceCost(int serviceCost)
{
    if (serviceCost < 0) throw Exeption("Вартість обслуговування повинна бути невід’ємною");
    m_serviceCostWorked = serviceCost;
};

void WorkedComputer::TurnOn()
{
    m_statusOfWork = "Turned on";
}

void WorkedComputer::TurnOff()
{
    m_statusOfWork = "Turned off";
}

bool WorkedComputer::IsWorking()
{
    if (m_statusOfWork == "Turned on")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void WorkedComputer::NeedsMaintenance() const
{
    if (m_daysWithoutRepair > 180 || m_countUsers > 50)
    {
        cout << "Комп’ютеру потрібне технічне обслуговування!" << endl;
    }
    else
    {
        cout << "Комп’ютер не потребує технічного обслуговування." << endl;
    }
};


WorkedComputer::~WorkedComputer()
{
    cout << "Викликано деструктор класу WorkedComputer" << endl;
};
