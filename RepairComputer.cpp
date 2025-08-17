#include "RepairComputer.h"
#include "Computer.h"
#include <iostream>
#include <string>

using namespace std;

RepairComputer::RepairComputer() : Computer() {};

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

void RepairComputer::ShowStatus()
{
    cout << "Computer is broken" << endl;
};

RepairComputer::~RepairComputer()
{
    cout << "Destructor of Repair class" << endl;
};