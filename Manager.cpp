#include "Manager.h"
#include "Computer.h"
#include "WorkedComputer.h"
#include "RepairComputer.h"
#include "Exeption.h"
#include <iostream>
#include <string>
#include <vector>
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
    if (thisComputer == nullptr) throw Exeption("Computer is empty");
    m_thisComputer.push_back(thisComputer);
};

void Manager::AuditoriumFilter(int auditoriumNumber) const
{
    bool found = false;
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetAuditoriumNumber() == auditoriumNumber)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        }
    }
    if (!found) throw Exeption("No computers found inthis auditorium");
}

void Manager::InventoryFilter(int inventoryNumber) const
{
    bool found = false;
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetInventoryNumber() == inventoryNumber)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        }
    };
    if (!found) throw Exeption("No computers found with this inventory number");
};

void Manager::SizeOfRomFilter(int sizeOfRom) const
{
    bool found = false;
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetSizeOfRom() == sizeOfRom)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        }
    };
    if (!found) throw Exeption("No computers found with this size of ROM");
};

void Manager::HasCdRomFilter(bool hasCdRom) const
{
    bool found = false;
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetHasCdRom() == hasCdRom){
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw Exeption("No computers found with this CD-ROM status");
};

void Manager::HasFloppyDiskFilter(bool hasFloppyDisk) const
{
    bool found = false;
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetHasFloppyDisk() == hasFloppyDisk)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw Exeption("No computers found with this Floppy Disk status");
};

void Manager::KeyboardFilter(string keyboard) const
{
    bool found = false;
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetKeyboard() == keyboard) {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw Exeption("No computers found with this keyboard");
};

void Manager::MonitorFilter(string monitor) const
{
    bool found = false;
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetMonitor() == monitor)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw Exeption("No computers found with this monitor");
};

void Manager::GpuFilter(string gpu) const
{
    bool found = false;
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetGpu() == gpu)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw Exeption("No computers found with this GPU");
};

void Manager::CpuFilter(string cpu) const
{
    bool found = false;
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetCpu() == cpu)
        {
        cout << (*it)->GetComputerFull() << endl;
        found = true;
        };
    };
    if (!found) throw Exeption("No computers found with this CPU");
};

void Manager::AddComputer(shared_ptr<Computer> computer)
{
    m_thisComputer.push_back(computer);
};

void Manager::RemoveComputer(int inventoryNumber) {
    bool found = false;
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetInventoryNumber()  == inventoryNumber)
        {
            m_thisComputer.erase(it);
            found = true;
            break;
        };
    };
    if (!found) {
        throw Exeption("No computer found with this inventory number");
    };
};

void Manager::ClearAll()
{
    m_thisComputer.clear();
}

void Manager::GetCount() const
{
    if (m_thisComputer.empty()) throw Exeption("No computers in the list");
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

void Manager::ChangeToBroken(int inventoryNumber)
{
    bool found = false;
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
            found = true;
            break;
        }
    }
    if (!found) throw Exeption("No computer found with this inventory number");
}

void Manager::ChangeToWorking(int inventoryNumber)
{
    bool found = false;
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
            found = true;
            break;
        }
    }
    if (!found) throw Exeption("No computer found with this inventory number");
}


Manager::~Manager()
{
    cout << "Destructor of manager class" << endl;
};
