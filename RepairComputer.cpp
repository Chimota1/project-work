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
    if (date.empty()) throw Exeption("Date is empty");
    m_dateOfRepair = date;
};

void RepairComputer::SetDescribe(string describe)
{
    if (describe.empty()) throw Exeption("Describe is empty");
    m_describeOfProblem = describe;
};
void RepairComputer::SetCause(string cause)
{
    if (cause.empty()) throw Exeption("Cause is empty");
    m_cause = cause;
};

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
      cout << " " << m_cause << endl;
      cout << " " << m_describeOfProblem << endl;
      cout << " " << m_dateOfRepair << endl;
};

void RepairComputer::UpdateRepairStatus()
{
  	int k;
    cout << "Press key: 1 if waiting diagnostic, 2 if in procces, 3 if ready," << endl;
    cin >> k;
	switch(k)
    {
    	case 1:
        m_repairStatus = "waiting diagnostic";
        break;
        case 2:
        m_repairStatus = "in procces";
        break;
        case 3:
        m_repairStatus = "ready";
        break;
        default:
        throw Exeption("Wrong number");
        break;
	};
};

int RepairComputer::RepairCost(int cost)
{
    m_repairCost = cost;
    if (cost < 0) throw Exeption("Repair cost must be 0 or positive");
    return m_repairCost;
};

void RepairComputer::NeedsSpareParts(bool needNewParts)
{
	cout << "Computer need new Parts? \"1 if yes \\ 2 if no\"" << endl;
    cin >> needNewParts;
    if (needNewParts != 0 && needNewParts != 1)
    {
        throw Exeption("Input must be 0 or 1");
    };
    m_needNewParts = needNewParts;
};

void RepairComputer::ShowInfoAboutRepair() const
{
	cout << GetInventoryNumber() << "in repair of" << GetDate() << "because" << GetCause();
};

void RepairComputer::ShowStatus()
{
    cout << "Status: " << m_repairStatus << endl;
};

void RepairComputer::ServiceCost(int serviceCost)
{
    if (serviceCost < 0) throw Exeption("Service cost must be 0 or positive");
    m_serviceCostRepair = serviceCost;
    cout << "Total cost (service + repair): "
         << m_serviceCostRepair + m_repairCost << endl;
};

bool RepairComputer::GetNeedNewParts() const
{
    return m_needNewParts;
}

RepairComputer::~RepairComputer()
{
    cout << "Destructor of Repair class" << endl;
};