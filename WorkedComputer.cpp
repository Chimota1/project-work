#include "WorkedComputer.h"
#include "Computer.h"
#include "MyException.h"
#include <string>
#include <iostream>

using namespace std;

WorkedComputer::WorkedComputer():
    Computer(),
	statusOfWork{"Unknown"},
	serviceCostWorked{0},
    daysWithoutRepair{0},
    countUsers{0},
    employmentStatus{"Freely"}
{
};

WorkedComputer::WorkedComputer(
    const string& statusOfWork,
    const string& employmentStatus,
    int serviceCostWorked,
    int daysWithoutRepair,
    int countUsers
    ):
    Computer(),
	statusOfWork{statusOfWork},
    employmentStatus{employmentStatus},
	serviceCostWorked{serviceCostWorked},
    daysWithoutRepair{daysWithoutRepair},
    countUsers{countUsers}
{
};

WorkedComputer::WorkedComputer(const WorkedComputer &other)
{
	this->statusOfWork = other.statusOfWork;
    this->employmentStatus = other.employmentStatus;
    this->serviceCostWorked = other.serviceCostWorked;
    this->daysWithoutRepair = other.daysWithoutRepair;
    this->countUsers = other.countUsers;
};

WorkedComputer::WorkedComputer(WorkedComputer &&other) noexcept
{
    this->statusOfWork = other.statusOfWork;
    this->employmentStatus = other.employmentStatus;
    this->serviceCostWorked = other.serviceCostWorked;
    this->daysWithoutRepair = other.daysWithoutRepair;
    this->countUsers = other.countUsers;
}

void WorkedComputer::ShowStatus()
{
    cout <<"Статус робочого комп’ютера: " << statusOfWork << endl;
};

void WorkedComputer::UpdateStatus()
{
    int k;
    cout << "Встановіть статус комп’ютера (1 — Freely, 2 — Busy): " << endl;
    cin >> k;
    switch (k)
    {
        case 1:
           employmentStatus = "Freely";
        break;

        case 2:
           employmentStatus = "Busy";
        break;

        default:
           throw MyException("Неправильний номер");
    };
};

void WorkedComputer::SetCountUsers(int users)
{
    if (users < 0) throw MyException("Кількість користувачів повинна бути невід’ємною");
    countUsers = users;
}

void WorkedComputer::SetDays(int days)
{
    if (days < 0) throw MyException("Кількість днів без ремонту повинна бути невід’ємною");
    daysWithoutRepair = days;
};

void WorkedComputer::SetEmploymentStatus(const string& status)
{
    if (status != "Freely" && status != "Busy")
        throw MyException("Невірний статус зайнятості у JSON файлі");
    employmentStatus = status;
};


int WorkedComputer::GetDays() const
{
	return daysWithoutRepair;
};


int WorkedComputer::GetCountUsers() const
{
    return countUsers;
}

int WorkedComputer::GetServiceCost() const
{
    return serviceCostWorked;
}

string WorkedComputer::GetEmploymentStatus() const
{
    return employmentStatus;
}

void WorkedComputer::ServiceCost(int serviceCost)
{
    if (serviceCost < 0) throw MyException("Вартість обслуговування повинна бути невід’ємною");
    serviceCostWorked = serviceCost;
};

void WorkedComputer::TurnOn()
{
    statusOfWork = "Turned on";
}

void WorkedComputer::TurnOff()
{
    statusOfWork = "Turned off";
}

bool WorkedComputer::IsWorking()
{
    if (statusOfWork == "Turned on")
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
    if (daysWithoutRepair > 180 || countUsers > 50)
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
