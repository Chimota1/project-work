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

void Manager::ViewAllUsers() const
{
    try
    {
        ifstream jsonFile("users.json");
        if (!jsonFile.is_open())
            throw Exeption("Cannot open users.json file.");

        json users;
        jsonFile >> users;

        cout << "List of all users:" << endl;
        for (const auto& user : users)
        {
            cout << "ID: " << user["id"] << ", Username: " << user["username"] << endl;
        }
    }
    catch (const Exeption& e)
    {
        throw Exeption("Error reading users.json: " + string(e.what()));
    }
};

void Manager::AddUser()
{
    try {
        bool isAdmin;
        string username, password;
        cout << "Is the new user an Admin? (1 for yes, 0 for no): ";
        cin >> isAdmin;

        cout << "Enter new username: ";
        cin >> username;

        if (isAdmin) {
            cout << "Enter new password: ";
            cin >> password;
        }

        srand(time(0));
        int newId = rand() % 900 + 100;

        json users;
        ifstream jsonFile("users.json");
        if (jsonFile.is_open()) {
            jsonFile >> users;
            jsonFile.close();
        }

        json newUser = {
            {"id", newId},
            {"username", username},
            {"isAdmin", isAdmin}
        };

        users.push_back(newUser);

        ofstream outJsonFile("users.json");
        if (!outJsonFile.is_open())
            throw Exeption("Cannot open users.json file for writing.");
        outJsonFile << setw(4) << users;
        outJsonFile.close();

        if (isAdmin) {
            ofstream passFile("passwords.txt", ios::app);
            if (!passFile.is_open())
                throw Exeption("Cannot open passwords.txt file for writing.");
            passFile << username << " " << password << endl;
            passFile.close();
        }

        cout << "User added successfully!" << endl;
        cout << "Assigned ID: " << newId << endl;
    }
    catch (const Exeption& e)
    {
        cerr << "Error adding user: " << e.what() << endl;
    }
}

void Manager::RemoveUser()
{
    try {
        int userId;
        cout << "Enter the ID of the user to remove: ";
        cin >> userId;

        json users;
        ifstream jsonFile("users.json");
        if (!jsonFile.is_open())
            throw Exeption("Cannot open users.json file.");
        jsonFile >> users;
        jsonFile.close();

        auto it = remove_if(users.begin(), users.end(),
                            [userId](const json& user) { return user["id"] == userId; });

        if (it == users.end()) {
            cout << "User with ID " << userId << " not found." << endl;
            return;
        }

        users.erase(it, users.end());

        ofstream outJsonFile("users.json");
        if (!outJsonFile.is_open())
            throw Exeption("Cannot open users.json file for writing.");
        outJsonFile << setw(4) << users;
        outJsonFile.close();

        cout << "User removed successfully!" << endl;
    }
    catch (const Exeption& e) {
        cerr << "Error removing user: " << e.what() << endl;
    }
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

    cout << "Enter Keyboard Type: ";
    cin >> keyboard;
    newComputer->SetKeyboard(keyboard);

    cout << "Enter Monitor Type: ";
    cin >> monitor;
    newComputer->SetMonitor(monitor);

    cout << "Enter GPU Type: ";
    cin >> gpu;
    newComputer->SetGpu(gpu);

    cout << "Enter CPU Type: ";
    cin >> cpu;
    newComputer->SetCpu(cpu);

    if (choice == 1)
    {
        auto workedComp = dynamic_cast<WorkedComputer*>(newComputer.get());
        if (workedComp)
        {
            int daysWithoutRepair, countUsers;
            string statusOfWork;

            cout << "Enter Days Without Repair: ";
            cin >> daysWithoutRepair;
            workedComp->SetDays(daysWithoutRepair);
            cout << "Enter Count of Users: ";
            cin >> countUsers;
            workedComp->SetCountUsers(countUsers);
            cout << "Enter Status of Work (Working/Turned off): ";
            cin >> statusOfWork;
            if (statusOfWork == "Working")
                workedComp->TurnOn();
            else
                workedComp->TurnOff();
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
    if (m_thisComputer.empty()) throw Exeption("list is empty, cannot sort");
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
};

void Manager::SortByAuditoriumNumber()
{
    if (m_thisComputer.empty()) throw Exeption("list is empty, cannot sort");
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
            compJson["statusOfWork"] = wc->IsWorking() ? "Working" : "Turned off";
            compJson["daysWithoutRepair"] = wc->GetDays();
            compJson["countUsers"] = wc->GetCountUsers();
            compJson["isWorking"] = wc->IsWorking();

        }
        else if (auto* rc = dynamic_cast<RepairComputer*>(computer.get()))
        {
            compJson["status"] = "broken";
            compJson["repairStatus"] = rc->GetRepairStatus();
            compJson["dateOfRepair"] = rc->GetDate();
            compJson["describeOfProblem"] = rc->GetDescribe();
            compJson["cause"] = rc->GetCause();
            compJson["repairCost"] = rc->GetRepairCost();
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
            computer = wc;
        }
        else if (compJson["status"] == "broken")
        {
            auto rc = make_shared<RepairComputer>();
            rc->SetDate(compJson.value("dateOfRepair", ""));
            rc->SetDescribe(compJson.value("describeOfProblem", ""));
            rc->SetCause(compJson.value("cause", ""));
            rc->RepairCost(compJson.value("repairCost", 0));
            rc->UpdateRepairStatus();
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
