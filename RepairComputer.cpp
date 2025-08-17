#include "RepairComputer.h"
#include "Computer.h"
#include <iostream>
#include <string>

using namespace std;

RepairComputer::RepairComputer() :
    m_dateOfRepair{"Unknown Date"},
    m_describeOfProblem{""},
    m_cause{"Unknown"}
    ,Computer()
    {
    };

RepairComputer::RepairComputer(const RepairComputer &other)
{
     m_dateOfRepair = other.m_dateOfRepair;
     m_describeOfProblem = other.m_describeOfProblem;
     m_cause = other.m_cause;
};

RepairComputer::RepairComputer(RepairComputer &&other) noexcept
{
    m_dateOfRepair = other.m_dateOfRepair;
    m_describeOfProblem = other.m_describeOfProblem;
    m_cause = other.m_cause;
};

RepairComputer::RepairComputer(
    string dateOfRepair,
    string describeOfProblem,
    string cause
    ):
    m_dateOfRepair{dateOfRepair},
    m_describeOfProblem{describeOfProblem},
    m_cause{cause}
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

void RepairComputer::ShowStatus()
{
    cout << "Computer is broken" << endl;
};

RepairComputer::~RepairComputer()
{
    cout << "Destructor of Repair class" << endl;
};