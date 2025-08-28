#include "Manager.h"
#include <iostream>
#include <memory>

using namespace std;

Manager::Manager() : m_thisComputer{}
{
};

Manager::Manager(vector<shared_ptr<Computer>> thisComputer):
m_thisComputer{thisComputer}
{
}

Manager::~Manager()
{
    cout << "Destructor of manager class" << endl;
};
