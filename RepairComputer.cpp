#include "RepairComputer.h"
#include "Computer.h"
#include <iostream>
#include <string>
#include "MyException.h"
#include <vector>

using namespace std;

RepairComputer::RepairComputer() :
    dateOfRepair{"Unknown Date"},
    describeOfProblem{"Unknown"},
    cause{"Unknown"},
    repairStatus{"Unknown"},
    repairCost{0},
    serviceCostRepair{0},
    Computer()
{
};
RepairComputer::RepairComputer(const RepairComputer &other)
{
     this->dateOfRepair = other.dateOfRepair;
     this->describeOfProblem = other.describeOfProblem;
     this->cause = other.cause;
     this->repairStatus = other.repairStatus;
     this->repairCost = other.repairCost;
     this->serviceCostRepair = other.serviceCostRepair;
};

RepairComputer::RepairComputer(RepairComputer &&other) noexcept
{
     this->dateOfRepair = other.dateOfRepair;
     this->describeOfProblem = other.describeOfProblem;
     this->cause = other.cause;
     this->repairStatus = other.repairStatus;
     this->repairCost = other.repairCost;
     this->serviceCostRepair = other.serviceCostRepair;
};

RepairComputer::RepairComputer(
    const string& dateOfRepair,
    const string& describeOfProblem,
    const string& cause,
    const string& repairStatus,
    int repairCost,
    int serviceCost
    ):
    dateOfRepair{dateOfRepair},
    describeOfProblem{describeOfProblem},
    cause{cause},
    repairStatus(repairStatus),
    repairCost{repairCost},
    serviceCostRepair{serviceCost}
{
};

void RepairComputer::SetDate(string date)
{
    if (date.empty()) throw MyException("Дата порожня");
    dateOfRepair = date;
};

void RepairComputer::SetDescribe(string describe)
{
    if (describe.empty()) throw MyException("Опис порожній");
    describeOfProblem = describe;
};
void RepairComputer::SetCause(string cause)
{
    if (cause.empty()) throw MyException("Причина порожня");
    this->cause = cause;
};

void RepairComputer::SetNeedParts(bool needNewParts)
{
    this->needNewParts = needNewParts;
};

void RepairComputer::SetRepairStatus(string repairStatus)
{
    this->repairStatus = repairStatus;
}

string RepairComputer::GetDate() const
{
    return dateOfRepair;
};

string RepairComputer::GetDescribe() const
{
    return describeOfProblem;
};

string RepairComputer::GetCause() const
{
    return cause;
};

int RepairComputer::GetRepairCost() const
{
    return repairCost;
};

string RepairComputer::GetRepairStatus() const
{
    return repairStatus;
};

void RepairComputer::ShowFullInfo()
{
      cout << GetComputerFull() << endl;
      cout << " Причина: " << cause << endl;
      cout << " Опис: " << describeOfProblem << endl;
      cout << " Дата ремонту: " << dateOfRepair << endl;
};

void RepairComputer::UpdateRepairStatus()
{
  	int k;
    cout << "Оберіть статус ремонту: 1 — очікує діагностику, 2 — у процесі, 3 — готовий" << endl;
    cin >> k;
	switch(k)
    {
    	case 1:
        repairStatus = "очікує діагностику";
        break;

        case 2:
        repairStatus = "у процесі";
        break;

        case 3:
        repairStatus = "готовий";
        break;

        default:
        throw MyException("Невірне число");
	};
};

int RepairComputer::RepairCost(int cost)
{
    repairCost = cost;
    if (cost < 0) throw MyException("Вартість ремонту повинна бути невід’ємною");
    return repairCost;
};



void RepairComputer::NeedsSpareParts(bool needNewParts)
{
	cout << "Чи потрібні комп’ютеру нові запчастини? (1 — так, 2 — ні)" << endl;
    cin >> needNewParts;
    if (needNewParts != 0 && needNewParts != 1)
    {
        throw MyException("Ввід повинен бути 0 або 1");
    };
    this->needNewParts = needNewParts;
};

void RepairComputer::ShowInfoAboutRepair() const
{
	cout << GetInventoryNumber() << " у ремонті з " << GetDate() << " через " << GetCause();
};

void RepairComputer::ShowStatus()
{
    cout << "Статус: " << repairStatus << endl;
};

void RepairComputer::ServiceCost(int serviceCost)
{
    if (serviceCost < 0) throw MyException("Вартість обслуговування повинна бути невід’ємною");
    serviceCostRepair = serviceCost;
    cout << "Загальна вартість (ремонт + обслуговування): "
         << serviceCostRepair + repairCost << endl;
};

bool RepairComputer::GetNeedNewParts() const
{
    return needNewParts;
}

RepairComputer::~RepairComputer()
{
    cout << "\nВикликано деструктор класу RepairComputer\n";
};
