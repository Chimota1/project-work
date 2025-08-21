#include "RepairComputer.h"
#include "Computer.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

RepairComputer::RepairComputer() :
    m_dateOfRepair{"Unknown Date"},
    m_describeOfProblem{""},
    m_cause{"Unknown"},
    m_repairStatus{"Unknown"},
    Computer()
    {
    };

RepairComputer::RepairComputer(const RepairComputer &other)
{
     m_dateOfRepair = other.m_dateOfRepair;
     m_describeOfProblem = other.m_describeOfProblem;
     m_cause = other.m_cause;
     m_repairStatus = other.m_repairStatus;
};

RepairComputer::RepairComputer(RepairComputer &&other) noexcept
{
    m_dateOfRepair = other.m_dateOfRepair;
    m_describeOfProblem = other.m_describeOfProblem;
    m_cause = other.m_cause;
    m_repairStatus = other.m_repairStatus;
};

RepairComputer::RepairComputer(
    string dateOfRepair,
    string describeOfProblem,
    string cause,
    string repairStatus
    ):
    m_dateOfRepair{dateOfRepair},
    m_describeOfProblem{describeOfProblem},
    m_cause{cause},
    m_repairStatus(repairStatus)
{
};

void RepairComputer::SetDate(string date)
{
  cout << "Set date of problem" << endl;
  cin >> date;
  m_dateOfRepair = date;
};

void RepairComputer::SetDescribe(string describe)
{
    cout << "Set describe of problem" << endl;
    cin >> describe;
    m_describeOfProblem = describe;
};
void RepairComputer::SetCause(string cause)
{
    cout << "Set cause of problem" << endl;
    cin >> cause;
    m_cause = cause;
};

string RepairComputer::GetDate()
{
    return m_dateOfRepair;
};

string RepairComputer::GetDescribe()
{
    return m_describeOfProblem;
};

string RepairComputer::GetCause()
{
    return m_cause;
};

void RepairComputer::ShowFullInfo()
{
 	vector<Computer> thisComputer;
    vector<Computer>::iterator i;
    for(i = thisComputer.begin(); i != thisComputer.end();++i)
      {
      	cout << i->GetComputer();
      }
      cout<< " " << m_cause << endl;
};

void RepairComputer::UpdateRepairStatus()
{
  	int k;
    cout << "Press key: 1 if waiting diagnostic, 2 if in procces, 3 if ready,"<<endl;
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
	};
};

bool RepairComputer::NeedsSpareParts()
{
	cout << "Computer need new Parts? \"1 if yes\\ 2 if no\"" << endl;
    bool needNewParts;
    cin >> needNewParts;
    return (needNewParts ? "yes" : "no");
};

void RepairComputer::ShowStatus()
{
    cout << "Status: " << m_repairStatus << endl;
};

RepairComputer::~RepairComputer()
{
    cout << "Destructor of Repair class" << endl;
};