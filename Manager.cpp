#include "Manager.h"
#include <iostream>
#include <memory>

using namespace std;

Manager::Manager() : thisComputer{}
{
};

Manager::~Manager()
{
    cout << "Destructor of manager class" << endl;
};
