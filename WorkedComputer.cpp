#include "WorkedComputer.h"
#include "Computer.h"
#include <iostream>

using namespace std;

WorkedComputer::WorkedComputer(): m_statusOfWork{"Unknown"} {};

void WorkedComputer::ShowStatus()
{
    cout <<"Status: " << m_statusOfWork << endl;
};