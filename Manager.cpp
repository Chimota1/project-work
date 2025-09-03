#include "Manager.h"
#include "Computer.h"
#include <iostream>
#include <memory>

using namespace std;

Manager::Manager() : m_thisComputer{}
{
};

Manager::Manager(vector<shared_ptr<Computer>> thisComputer):
    m_thisComputer{thisComputer}
{
};

Manager::Manager(const Manager &other)
{
    this->m_thisComputer = other.m_thisComputer;
};

Manager::Manager(Manager &&other) noexcept
{
    this->m_thisComputer = other.m_thisComputer;
};

 void const Manager::GetManager()
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        cout << (*it)->GetComputerFull() << endl;
    }
};

void Manager::SetManager(shared_ptr<Computer> thisComputer)
{
    m_thisComputer.push_back(thisComputer);
};

void const Manager::AuditoriumFilter(int auditoriumNumber)
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetAuditoriumNumber() == auditoriumNumber)
        cout << (*it)->GetComputerFull() << endl;
    }
}

void const Manager::InventoryFilter(int inventoryNumber)
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetInventoryNumber() == inventoryNumber)
        cout << (*it)->GetComputerFull() << endl;
    };
};

void const Manager::SizeOfRomFilter(int sizeOfRom)
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetSizeOfRom() == sizeOfRom)
        cout << (*it)->GetComputerFull() << endl;
    };
};

void Manager::HasCdRomFilter(bool hasCdRom) const
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetHasCdRom() == hasCdRom)
        cout << (*it)->GetComputerFull() << endl;
    };
};

Manager::~Manager()
{
    cout << "Destructor of manager class" << endl;
};
