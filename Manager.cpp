#include "Manager.h"
#include "Computer.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "WorkedComputer.h"
#include "RepairComputer.h"
#include "Exeption.h"
#include "json.hpp"
#include <fstream>
#include <memory>
#include <cstdlib>


using namespace std;
using json = nlohmann::json;

Manager::Manager() :
m_thisComputer{}
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

vector<shared_ptr<Computer>>& Manager::GetManager()
{
    return m_thisComputer;
};

void Manager::SetManager(shared_ptr<Computer> thisComputer)
{
    m_thisComputer.push_back(thisComputer);
};

void Manager::ViewAllUsers() const
{
    try
    {
        ifstream userFile("users.txt");
        if (!userFile.is_open())
            throw Exeption("Cannot open users.json file.");
        cout << "List of all users:" << endl;
        string line;
        while (getline(userFile, line))
        {
            cout << line << endl;
        }
        userFile.close();
    }
    catch (const Exeption& e)
    {
        throw Exeption("Error reading users.json: " + string(e.what()));
    }
};

void Manager::AddUser()
{
    try {
        string username, password, role;
        int newID;
        cout << "Enter new username: ";
        cin >> username;
        cout << "Enter new password: ";
        cin >> password;
        cout << "Enter role (admin/user): ";
        cin >> role;
        ofstream userFile("users.txt", ios::app);
        GenerateID(newID);
        if (!userFile.is_open())
            throw Exeption("Cannot open users.txt file.");
        userFile << newID << " " << username << ":" << password << " " << role << endl;
        userFile.close();
        cout << "User added successfully!" << endl;
        cout << "Assigned ID: " << newID << endl;
        m_lastID = newID;
    }
    catch (const Exeption& e)
    {
        cerr << "Error adding user: " << e.what() << endl;
    }
}

void Manager::RemoveUser() {
    try {
        int userId;
        cout << "Enter the ID of the user to remove: ";
        cin >> userId;

        ifstream userFile("users.txt");
        if (!userFile.is_open())
            throw Exeption("Cannot open users.txt file.");

        string line;
        vector<string> lines;
        bool found = false;
        while (getline(userFile, line)) {
            if (line.find(to_string(userId) + " ") != 0) {
                lines.push_back(line);
            } else {
                found = true;
            }
        }
        userFile.close();

        if (!found) {
            cout << "User with ID " << userId << " not found." << endl;
            return;
        }

        ofstream outFile("users.txt");
        for (const auto& l : lines) {
            outFile << l << endl;
        }
        outFile.close();

        cout << "User removed successfully!" << endl;
    }
    catch (const Exeption& e) {
        cerr << "Error removing user: " << e.what() << endl;
    }
}

int Manager::GetLastID() const
{
    return m_lastID;
}

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

int Manager::GenerateID(int& id)
{
    srand(time(0));
    id = rand() % 999 + 100;
    return id;
}

void Manager::ViewAllComputer() const
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        cout << (*it)->GetComputerFull() << endl;
    }
};


void Manager::InitComputer() {
    int choice;
    cout << "Choose type of computer to add:" << endl;
    cout << "1. Worked Computer" << endl;
    cout << "2. Repair Computer" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    shared_ptr<Computer> newComputer;

    if (choice == 1)
    {
        newComputer = make_shared<WorkedComputer>();
    }
    else if (choice == 2)
    {
        newComputer = make_shared<RepairComputer>();
    }
    else
    {
        throw Exeption("Invalid choice for computer type.");
    }

    int inventoryNumber, auditoriumNumber, sizeOfRom;
    bool hasCdRom, hasFloppyDisk;
    string keyboard, monitor, gpu, cpu;

    cout << "Enter Inventory Number: ";
    cin >> inventoryNumber;
    newComputer->SetInventoryNumber(inventoryNumber);

    cout << "Enter Auditorium Number: ";
    cin >> auditoriumNumber;
    newComputer->SetAuditoriumNumber(auditoriumNumber);

    cout << "Enter Size of ROM (GB): ";
    cin >> sizeOfRom;
    newComputer->SetSizeOfRom(sizeOfRom);

    cout << "Has CD-ROM (1 for yes, 0 for no): ";
    cin >> hasCdRom;
    newComputer->SetHasCdRom(hasCdRom);

    cout << "Has Floppy Disk (1 for yes, 0 for no): ";
    cin >> hasFloppyDisk;
    newComputer->SetHasFloppyDisk(hasFloppyDisk);

    cin.ignore();

    cout << "Enter Keyboard Type: ";
    getline(cin, keyboard);
    newComputer->SetKeyboard(keyboard);

    cout << "Enter Monitor Type: ";
    getline(cin, monitor);
    newComputer->SetMonitor(monitor);

    cout << "Enter GPU Type: ";
    getline(cin, gpu);
    newComputer->SetGpu(gpu);

    cout << "Enter CPU Type: ";
    getline(cin, cpu);
    newComputer->SetCpu(cpu);

    if (choice == 1)
    {
        auto workedComp = dynamic_cast<WorkedComputer*>(newComputer.get());
        if (workedComp)
        {
            int daysWithoutRepair, countUsers,serviceCost,statusOfWork;
            cout << "Enter Days Without Repair: ";
            cin >> daysWithoutRepair;
            workedComp->SetDays(daysWithoutRepair);
            cout << "Enter Count of Users: ";
            cin >> countUsers;
            workedComp->SetCountUsers(countUsers);
            cout << "Enter Status of Work (1 if Turned on/ 2. if Turned off): ";
            cin >> statusOfWork;
            if (statusOfWork == 1)
            {
                workedComp->TurnOn();
            }
            else if (statusOfWork == 2)
            {
                workedComp->TurnOff();
            }
            cout << "Enter Service Cost: ";
            cin >> serviceCost;
            workedComp->ServiceCost(serviceCost);
        }
    }
    else if (choice == 2) {
        auto repairComp = dynamic_cast<RepairComputer*>(newComputer.get());
        if (repairComp)
        {
            string dateOfRepair, describeOfProblem, cause;
            int repairCost;
            cout << "Enter Date of Repair (YYYY-MM-DD): ";
            cin >> dateOfRepair;
            repairComp->SetDate(dateOfRepair);
            cout << "Enter Description of Problem: ";
            cin.ignore();
            getline(cin, describeOfProblem);
            repairComp->SetDescribe(describeOfProblem);
            cout << "Enter Cause of Problem: ";
            cin.ignore();
            getline(cin, cause);
            repairComp->SetCause(cause);
            cout << "Enter Repair Cost: ";
            cin >> repairCost;
            repairComp->RepairCost(repairCost);
        }
    }
    m_thisComputer.push_back(newComputer);
    SaveToJson("database.json");
}

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
    if (m_thisComputer.empty()) throw Exeption("list is empty, cannot clear");
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
    if (m_thisComputer.empty()) throw Exeption("list is empty, cannot sort");
    sort(m_thisComputer.begin(), m_thisComputer.end(),
         [](const shared_ptr<Computer>& first, const shared_ptr<Computer>& last)
         {
             return first->GetInventoryNumber() < last->GetInventoryNumber();
         });
    SaveToJson("database.json");
};

void Manager::SortByAuditoriumNumber()
{
    if (m_thisComputer.empty()) throw Exeption("list is empty, cannot sort");
    sort(m_thisComputer.begin(), m_thisComputer.end(),
         [](const shared_ptr<Computer>& first, const shared_ptr<Computer>& last)
         {
             return first->GetAuditoriumNumber() < last->GetAuditoriumNumber();
         });
    SaveToJson("database.json");
};

void Manager::ChangeToBroken(int inventoryNumber)
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetInventoryNumber() == inventoryNumber)
        {
            auto brokenComputer = make_shared<RepairComputer>();

            brokenComputer->SetGpu((*it)->GetGpu());
            brokenComputer->SetCpu((*it)->GetCpu());
            brokenComputer->SetMonitor((*it)->GetMonitor());
            brokenComputer->SetKeyboard((*it)->GetKeyboard());
            brokenComputer->SetSizeOfRom((*it)->GetSizeOfRom());
            brokenComputer->SetHasCdRom((*it)->GetHasCdRom());
            brokenComputer->SetHasFloppyDisk((*it)->GetHasFloppyDisk());
            brokenComputer->SetAuditoriumNumber((*it)->GetAuditoriumNumber());
            brokenComputer->SetInventoryNumber((*it)->GetInventoryNumber());
            string dateOfRepair, describeOfProblem, cause;
            int repairCost;

            cout << "Enter Date of Repair (YYYY-MM-DD): ";
            cin >> dateOfRepair;
            brokenComputer->SetDate(dateOfRepair);

            cout << "Enter Problem Description: ";
            cin.ignore();
            getline(cin, describeOfProblem);
            brokenComputer->SetDescribe(describeOfProblem);

            cout << "Enter Cause of Problem: ";
            cin.ignore();
            getline(cin, cause);
            brokenComputer->SetCause(cause);

            cout << "Enter Repair Cost: ";
            cin >> repairCost;
            brokenComputer->RepairCost(repairCost);

            brokenComputer->UpdateRepairStatus();

            *it = brokenComputer;
            SaveToJson("database.json");
            cout << "Computer status changed to BROKEN successfully!\n";
            return;
        }
    }

    cout << "Computer with inventory number " << inventoryNumber << " not found.\n";
}


void Manager::ChangeToWorking(int inventoryNumber)
{
    for (auto it = m_thisComputer.begin(); it != m_thisComputer.end(); ++it)
    {
        if ((*it)->GetInventoryNumber() == inventoryNumber)
        {
            auto workingComputer = make_shared<WorkedComputer>();
            workingComputer->SetGpu((*it)->GetGpu());
            workingComputer->SetCpu((*it)->GetCpu());
            workingComputer->SetMonitor((*it)->GetMonitor());
            workingComputer->SetKeyboard((*it)->GetKeyboard());
            workingComputer->SetSizeOfRom((*it)->GetSizeOfRom());
            workingComputer->SetHasCdRom((*it)->GetHasCdRom());
            workingComputer->SetHasFloppyDisk((*it)->GetHasFloppyDisk());
            workingComputer->SetAuditoriumNumber((*it)->GetAuditoriumNumber());
            workingComputer->SetInventoryNumber((*it)->GetInventoryNumber());

            int daysWithoutRepair, countUsers;
            cout << "Enter Days Without Repair: ";
            cin >> daysWithoutRepair;
            workingComputer->SetDays(daysWithoutRepair);

            cout << "Enter Count of Users: ";
            cin >> countUsers;
            workingComputer->SetCountUsers(countUsers);

            string status;
            cout << "Enter Status (Working/Turned off): ";
            cin >> status;
            if (status == "Working")
                workingComputer->TurnOn();
            else
                workingComputer->TurnOff();

            *it = workingComputer;

            SaveToJson("database.json");
            cout << "Computer status changed to WORKING successfully!\n";
            return;
        }
    }

    cout << "Computer with inventory number " << inventoryNumber << " not found.\n";
}


void Manager::SaveToJson(const string& filename) const
{
    json j;
    for (const auto& computer : m_thisComputer)
    {
        json compJson;
        compJson["inventoryNumber"] = computer->GetInventoryNumber();
        compJson["auditoriumNumber"] = computer->GetAuditoriumNumber();
        compJson["sizeOfRom"] = computer->GetSizeOfRom();
        compJson["hasCdRom"] = computer->GetHasCdRom();
        compJson["hasFloppyDisk"] = computer->GetHasFloppyDisk();
        compJson["keyboard"] = computer->GetKeyboard();
        compJson["monitor"] = computer->GetMonitor();
        compJson["gpu"] = computer->GetGpu();
        compJson["cpu"] = computer->GetCpu();

        if (auto* wc = dynamic_cast<WorkedComputer*>(computer.get()))
        {
            compJson["status"] = "working";
            compJson["statusOfWork"] = wc->IsWorking() ? "Turned on" : "Turned off";
            compJson["daysWithoutRepair"] = wc->GetDays();
            compJson["countUsers"] = wc->GetCountUsers();
            compJson["isWorking"] = wc->IsWorking();
            compJson["serviceCost"] = wc->GetServiceCost();
            compJson["employmentStatus"] = wc->GetEmploymentStatus();

        }
        else if (auto* rc = dynamic_cast<RepairComputer*>(computer.get()))
        {
            compJson["status"] = "broken";
            compJson["repairStatus"] = rc->GetRepairStatus();
            compJson["dateOfRepair"] = rc->GetDate();
            compJson["describeOfProblem"] = rc->GetDescribe();
            compJson["cause"] = rc->GetCause();
            compJson["repairCost"] = rc->GetRepairCost();
            compJson["needNewParts"] = rc->GetNeedNewParts();
        }

        j.push_back(compJson);
    }

    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        throw Exeption("Could not open file for writing: " + filename);
    }
    outFile << setw(4) << j << endl;
    outFile.close();
}

void Manager::LoadFromJson(const string& filename)
{
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        throw Exeption("Could not open file for reading: " + filename);
    }

    json j;
    inFile >> j;
    inFile.close();

    m_thisComputer.clear();

    for (const auto& compJson : j)
    {
        shared_ptr<Computer> computer;

        if (compJson["status"] == "working")
        {
            auto wc = make_shared<WorkedComputer>();
            wc->SetDays(compJson.value("daysWithoutRepair", 0));
            wc->SetCountUsers(compJson.value("countUsers", 0));
            if (compJson.value("isWorking", false))
                wc->TurnOn();
            else
                wc->TurnOff();
            wc->SetEmploymentStatus(compJson.value("employmentStatus","Freely"));
            computer = wc;
        }
        else if (compJson["status"] == "broken")
        {
            auto rc = make_shared<RepairComputer>();
            rc->SetDate(compJson.value("dateOfRepair", "Unknown"));
            rc->SetDescribe(compJson.value("describeOfProblem", "Unknown"));
            rc->SetCause(compJson.value("cause", "Unknown"));
            rc->SetRepairStatus(compJson.value("repairStatus","waiting diagnostic"));
            rc->RepairCost(compJson.value("repairCost", 0));
            rc->SetNeedParts(compJson.value("needNewParts", true));
            computer = rc;
        }
        else
        {
            throw Exeption("Unknown computer status in JSON");
        }

        computer->SetInventoryNumber(compJson.value("inventoryNumber", 0));
        computer->SetAuditoriumNumber(compJson.value("auditoriumNumber", 0));
        computer->SetSizeOfRom(compJson.value("sizeOfRom", 0));
        computer->SetHasCdRom(compJson.value("hasCdRom", false));
        computer->SetHasFloppyDisk(compJson.value("hasFloppyDisk", false));
        computer->SetKeyboard(compJson.value("keyboard", ""));
        computer->SetMonitor(compJson.value("monitor", ""));
        computer->SetGpu(compJson.value("gpu", ""));
        computer->SetCpu(compJson.value("cpu", ""));

        m_thisComputer.push_back(computer);
    }
}

Manager::~Manager()
{
    cout << "Destructor of manager class" << endl;
};
