#include "RepairComputer.h"
#include "Computer.h"
#include <iostream>
#include <string>

using namespace std;

RepairComputer::RepairComputer() : Computer() {};

void RepairComputer::ShowStatus()
{
    cout << "Computer is broken" << endl;
};

RepairComputer::~RepairComputer()
{
    cout << "Destructor of Repair class" << endl;
};