#include "Manager.h"
#include "Computer.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "WorkedComputer.h"
#include "RepairComputer.h"
#include "Exeption.h"
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

 void Manager::GetManager() const
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

void Manager::AuditoriumFilter(int auditoriumNumber) const
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetAuditoriumNumber() == auditoriumNumber)
        cout << (*it)->GetComputerFull() << endl;
    }
}

void Manager::InventoryFilter(int inventoryNumber) const
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetInventoryNumber() == inventoryNumber)
        cout << (*it)->GetComputerFull() << endl;
    };
};

void Manager::SizeOfRomFilter(int sizeOfRom) const
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

void Manager::HasFloppyDiskFilter(bool hasFloppyDisk) const
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetHasFloppyDisk() == hasFloppyDisk)
        cout << (*it)->GetComputerFull() << endl;
    };
};

void Manager::KeyboardFilter(string keyboard) const
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetKeyboard() == keyboard)
        cout << (*it)->GetComputerFull() << endl;
    };
};

void Manager::MonitorFilter(string monitor) const
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetMonitor() == monitor)
        cout << (*it)->GetComputerFull() << endl;
    };
};

void Manager::GpuFilter(string gpu) const
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetGpu() == gpu)
        cout << (*it)->GetComputerFull() << endl;
    };
};

void Manager::CpuFilter(string cpu) const
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetCpu() == cpu)
        cout << (*it)->GetComputerFull() << endl;
    }
};


void Manager::RemoveComputer(int inventoryNumber)
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetInventoryNumber()  == inventoryNumber)
        {
            m_thisComputer.erase(it);
            break;
        }
    }
};

void Manager::ClearAll()
{
    m_thisComputer.clear();
}

void Manager::GetCount() const
{
    cout << "Count of all computers" << m_thisComputer.size();
}

void Manager::CountBrokenComputers() const
{
    int count = 0;
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if (dynamic_cast<RepairComputer*>(it->get()) != nullptr)
        {
            count++;
        }
    }
    cout << "Count of broken computers: " << count << endl;
}

void Manager::CountWorkingComputers() const
{
    int count = 0;
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if (dynamic_cast<WorkedComputer*>(it->get()) != nullptr)
        {
            count++;
        }
    }
    cout << "Count of working computers: " << count << endl;
}

void Manager::SortByInventoryNumber()
{
    sort(m_thisComputer.begin(), m_thisComputer.end(),
         [](const shared_ptr<Computer>& first, const shared_ptr<Computer>& last)
         {
             return first->GetInventoryNumber() < last->GetInventoryNumber();
         });
};

void Manager::SortByAuditoriumNumber()
{
    sort(m_thisComputer.begin(), m_thisComputer.end(),
         [](const shared_ptr<Computer>& first, const shared_ptr<Computer>& last)
         {
             return first->GetAuditoriumNumber() < last->GetAuditoriumNumber();
         });
};

void Manager::ChangeToBroken(int inventoryNumber)
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ( (*it)->GetInventoryNumber()  == inventoryNumber)
        {
            shared_ptr<Computer> brokenComputer = make_shared<RepairComputer>();
            brokenComputer->SetGpu((*it)->GetGpu());
            brokenComputer->SetCpu((*it)->GetCpu());
            brokenComputer->SetMonitor((*it)->GetMonitor());
            brokenComputer->SetKeyboard((*it)->GetKeyboard());
            brokenComputer->SetSizeOfRom((*it)->GetSizeOfRom());
            brokenComputer->SetHasCdRom((*it)->GetHasCdRom());
            brokenComputer->SetHasFloppyDisk((*it)->GetHasFloppyDisk());
            brokenComputer->SetAuditoriumNumber((*it)->GetAuditoriumNumber());
            brokenComputer->SetInventoryNumber((*it)->GetInventoryNumber());
            m_thisComputer.erase(it);
            m_thisComputer.push_back(brokenComputer);
            break;
        }
    }
}

void Manager::ChangeToWorking(int inventoryNumber)
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ( (*it)->GetInventoryNumber()  == inventoryNumber)
        {
            shared_ptr<Computer> workingComputer = make_shared<WorkedComputer>();
            workingComputer->SetGpu((*it)->GetGpu());
            workingComputer->SetCpu((*it)->GetCpu());
            workingComputer->SetMonitor((*it)->GetMonitor());
            workingComputer->SetKeyboard((*it)->GetKeyboard());
            workingComputer->SetSizeOfRom((*it)->GetSizeOfRom());
            workingComputer->SetHasCdRom((*it)->GetHasCdRom());
            workingComputer->SetHasFloppyDisk((*it)->GetHasFloppyDisk());
            workingComputer->SetAuditoriumNumber((*it)->GetAuditoriumNumber());
            workingComputer->SetInventoryNumber((*it)->GetInventoryNumber());
            m_thisComputer.erase(it);
            m_thisComputer.push_back(workingComputer);
            break;
        }
    }
}


Manager::~Manager()
{
    cout << "Destructor of manager class" << endl;
};
