#include "RepairComputer.h"
#include "Computer.h"
#include <iostream>
#include <string>
#include "Exeption.h"
#include <vector>

using namespace std;

RepairComputer::RepairComputer() :
    m_dateOfRepair{"Unknown Date"},
    m_describeOfProblem{"Unknown"},
    m_cause{"Unknown"},
    m_repairStatus{"Unknown"},
    m_repairCost{0},
    m_serviceCostRepair{0},
    Computer()
{
};
RepairComputer::RepairComputer(const RepairComputer &other)
{
     this->m_dateOfRepair = other.m_dateOfRepair;
     this->m_describeOfProblem = other.m_describeOfProblem;
     this->m_cause = other.m_cause;
     this->m_repairStatus = other.m_repairStatus;
     this->m_repairCost = other.m_repairCost;
     this->m_serviceCostRepair = other.m_serviceCostRepair;
};

RepairComputer::RepairComputer(RepairComputer &&other) noexcept
{
     this->m_dateOfRepair = other.m_dateOfRepair;
     this->m_describeOfProblem = other.m_describeOfProblem;
     this->m_cause = other.m_cause;
     this->m_repairStatus = other.m_repairStatus;
     this->m_repairCost = other.m_repairCost;
     this->m_serviceCostRepair = other.m_serviceCostRepair;
};

RepairComputer::RepairComputer(
    string dateOfRepair,
    string describeOfProblem,
    string cause,
    string repairStatus,
    int repairCost,
    int serviceCost
    ):
    m_dateOfRepair{dateOfRepair},
    m_describeOfProblem{describeOfProblem},
    m_cause{cause},
    m_repairStatus(repairStatus),
    m_repairCost{repairCost},
    m_serviceCostRepair{serviceCost}
{
};

void RepairComputer::SetDate(string date)
{
    if (date.empty()) throw Exeption("Дата порожня");
    m_dateOfRepair = date;
};

void RepairComputer::SetDescribe(string describe)
{
    if (describe.empty()) throw Exeption("Опис порожній");
    m_describeOfProblem = describe;
};
void RepairComputer::SetCause(string cause)
{
    if (cause.empty()) throw Exeption("Причина порожня");
    m_cause = cause;
};

void RepairComputer::SetNeedParts(bool needNewParts)
{
    m_needNewParts = needNewParts;
};

void RepairComputer::SetRepairStatus(string repairStatus)
{
    m_repairStatus = repairStatus;
}

string RepairComputer::GetDate() const
{
    return m_dateOfRepair;
};

string RepairComputer::GetDescribe() const
{
    return m_describeOfProblem;
};

string RepairComputer::GetCause() const
{
    return m_cause;
};

int RepairComputer::GetRepairCost() const
{
    return m_repairCost;
};

string RepairComputer::GetRepairStatus() const
{
    return m_repairStatus;
};

void RepairComputer::ShowFullInfo()
{
      cout << GetComputerFull() << endl;
      cout << " Причина: " << m_cause << endl;
      cout << " Опис: " << m_describeOfProblem << endl;
      cout << " Дата ремонту: " << m_dateOfRepair << endl;
};

void RepairComputer::UpdateRepairStatus()
{
  	int k;
    cout << "Оберіть статус ремонту: 1 — очікує діагностику, 2 — у процесі, 3 — готовий" << endl;
    cin >> k;
	switch(k)
    {
    	case 1:
        m_repairStatus = "очікує діагностику";
        break;
        case 2:
        m_repairStatus = "у процесі";
        break;
        case 3:
        m_repairStatus = "готовий";
        break;
        default:
        throw Exeption("Невірне число");
        break;
	};
};

int RepairComputer::RepairCost(int cost)
{
    m_repairCost = cost;
    if (cost < 0) throw Exeption("Вартість ремонту повинна бути невід’ємною");
    return m_repairCost;
};



void RepairComputer::NeedsSpareParts(bool needNewParts)
{
	cout << "Чи потрібні комп’ютеру нові запчастини? (1 — так, 2 — ні)" << endl;
    cin >> needNewParts;
    if (needNewParts != 0 && needNewParts != 1)
    {
        throw Exeption("Ввід повинен бути 0 або 1");
    };
    m_needNewParts = needNewParts;
};

void RepairComputer::ShowInfoAboutRepair() const
{
	cout << GetInventoryNumber() << " у ремонті з " << GetDate() << " через " << GetCause();
};

void RepairComputer::ShowStatus()
{
    cout << "Статус: " << m_repairStatus << endl;
};

void RepairComputer::ServiceCost(int serviceCost)
{
    if (serviceCost < 0) throw Exeption("Вартість обслуговування повинна бути невід’ємною");
    m_serviceCostRepair = serviceCost;
    cout << "Загальна вартість (ремонт + обслуговування): "
         << m_serviceCostRepair + m_repairCost << endl;
};

bool RepairComputer::GetNeedNewParts() const
{
    return m_needNewParts;
}

RepairComputer::~RepairComputer()
{
    cout << "Викликано деструктор класу RepairComputer" << endl;
};
