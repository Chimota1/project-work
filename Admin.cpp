#include "Admin.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "json.hpp"
#include "Exeption.h"
#include "Manager.h"

using json = nlohmann::json;
using namespace std;

Admin::Admin()
    : m_id(0), m_username("Anonymus"), m_password("null"), m_status("admin")
{
};

Admin::Admin(int id, const string& username, const string& password,const string& status)
    : m_id(id), m_username(username), m_password(password), m_status(status)
{
};

Admin::Admin(const Admin& other)
{
    this->m_id = other.m_id;
    this->m_username = other.m_username;
    this->m_password = other.m_password;
    this->m_status = other.m_status;
};

Admin::Admin(Admin&& other) noexcept
{
    this->m_id = other.m_id;
    this->m_username = other.m_username;
    this->m_password = other.m_password;
    this->m_status = other.m_status;
};

void Admin::Login()
{
    Manager manager;
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    bool found = false;

    ifstream userFile("users.txt");
    if (!userFile.is_open())
        throw Exeption("Cannot open users.txt file.");

    string line;
    while (getline(userFile, line)) {
        istringstream iss(line);
        int id;
        string loginData, role;

        if (iss >> id >> loginData >> role) {
            size_t colonPos = loginData.find(':');
            if (colonPos != string::npos) {
                string fileUsername = loginData.substr(0, colonPos);
                string filePassword = loginData.substr(colonPos + 1);
                if (username == fileUsername && password == filePassword && role == "admin") {
                    found = true;
                    m_username = fileUsername;
                    m_password = filePassword;
                    m_id = id;
                    m_status = role;
                    break;
                }
                else {
                    throw Exeption("wrong login data or you are not a admin");
                    break;
                }
            }
        }
    }
    userFile.close();

    if (found) {
        cout << "Login successful!" << endl;
        MainMenu(manager);
    }
    else {
        throw Exeption("Invalid username or password");
    }
}


void Admin::MainMenu(Manager& manager)
{
    int choice;
    manager.LoadFromJson("database.json");
    do
    {
        cout << "\nAdmin Main Menu\n";
        cout << "1. View all Users\n";
        cout << "2. Add User\n";
        cout << "3. Remove User\n";
        cout << "4. Add new Computer\n";
        cout << "5. See my ID\n";
        cout << "6. Filter Computers \n";
        cout << "7. Sort Computers by: \n";
        cout << "8. Clear All Computers\n";
        cout << "9. Count Computers\n";
        cout << "10. Menu of Worked Computer\n";
        cout << "11. Menu of Repair Computer\n";
        cout << "12. Remove Computer\n";
        cout << "13. Changes Menu\n";
        cout << "14. Help\n";
        cout << "15. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Viewing all users..." << endl;
                manager.ViewAllUsers();
                break;

            case 2:
                cout << "Adding a user..." << endl;
                manager.AddUser();
                break;

            case 3:
                cout << "Removing a user..." << endl;
                manager.RemoveUser();
                break;

            case 4:
                cout << "Adding new computer..." << endl;
                manager.InitComputer();
                break;

            case 5:
                cout << "Your ID is: " << GetID() << endl;
                break;

            case 6:
                FilterMenu(manager);
                break;

            case 7:
                SortMenu(manager);
                break;

            case 8:
                cout << "Clearing all computers..." << endl;
                manager.ClearAll();
                break;

            case 9:
                cout << "Counting all computers..." << endl;
                manager.GetCount();
                break;

            case 10:
                WorkedMenu(manager);
                break;

            case 11:
                RepairMenu(manager);
                break;

            case 12:
                cout << "Removing a computer..." << endl;
                {
                    int inventoryNumber;
                    cout << "Enter inventory number of the computer to remove: ";
                    cin >> inventoryNumber;
                    manager.RemoveComputer(inventoryNumber);
                }
            break;

            case 13:
                ChangesMenu(manager);
                break;

            case 14:
                HelpMenu();
            case 15:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        manager.SaveToJson("database.json");
    } while (choice != 15);
};

int Admin::GetID() const
{
    return m_id;
};


void Admin::HelpMenu() const
    {
        cout << "\n==================== HELP MENU ====================\n";
        cout << "Welcome to the Computer Management System (CMS)\n";
        cout << "This program allows administrators to manage computers and users.\n";
        cout << "You can add, delete, edit, and view computers, as well as manage user accounts.\n";
        cout << "----------------------------------------------------\n";
        cout << "\nMAIN MENU OVERVIEW:\n";
        cout << "1. View all Users        → Shows all registered users from users.txt\n";
        cout << "2. Add User              → Creates a new user (admin or regular)\n";
        cout << "3. Remove User           → Deletes an existing user by ID or username\n";
        cout << "4. Add new Computer      → Creates a new Worked or Repair computer\n";
        cout << "5. See my ID             → Displays your current admin ID\n";
        cout << "6. Filter Computers      → Filters computers by chosen parameter\n";
        cout << "7. Sort Computers by     → Sorts by inventory or auditorium number\n";
        cout << "8. Clear All Computers   → Removes all computers from database.json\n";
        cout << "9. Count Computers       → Shows total number of computers\n";
        cout << "10. Worked Menu          → Access worked computer settings\n";
        cout << "11. Repair Menu          → Access repair computer settings\n";
        cout << "12. Remove Computer      → Delete specific computer by inventory number\n";
        cout << "13. Changes Menu         → Edit any computer’s basic information\n";
        cout << "14. Help                 → Shows this help menu\n";
        cout << "0. Logout                → Exit admin mode and return to login\n";
        cout << "----------------------------------------------------\n";

        cout << "\nPROGRAM DESCRIPTION:\n";
        cout << " - There are two main types of users: Admin and DefaultUser.\n";
        cout << " - Admin can manage computers and users.\n";
        cout << " - DefaultUser can only view, filter, and sort data.\n";
        cout << " - All computer data is stored in 'database.json'.\n";
        cout << " - User data (login & roles) is stored in 'users.txt'.\n";
        cout << "----------------------------------------------------\n";

        cout << "\nINPUT RULES:\n";
        cout << " - Use numbers for menu selections.\n";
        cout << " - Use 1 for 'YES' and 0 for 'NO' in logical questions.\n";
        cout << " - Do not leave text fields empty (e.g. keyboard, GPU, CPU, cause).\n";
        cout << " - Date format: YYYY-MM-DD.\n";
        cout << " - Every change is saved automatically to 'database.json'.\n";
        cout << "----------------------------------------------------\n";

        cout << "\nADDITIONAL NOTES:\n";
        cout << " - If you get 'Exeption' errors, check your input values.\n";
        cout << " - You can always return to main menu with option 0.\n";
        cout << " - After each session, data is safely stored in files.\n";
        cout << "----------------------------------------------------\n";

        cout << "Tip: Use 'Changes Menu' to update computer data quickly!\n";
        cout << "=====================================================\n";
    }

void Admin::FilterMenu(Manager& manager)
{
    int filterChoice;
    manager.LoadFromJson("database.json");
    cout << "Filter computers by: " << endl;
    cout << "1. Inventory Number" << endl;
    cout << "2. Auditorium Number" << endl;
    cout << "3. Size of ROM" << endl;
    cout << "4. Has CD-ROM" << endl;
    cout << "5. Has Floppy Disk" << endl;
    cout << "6. Keyboard" << endl;
    cout << "7. Monitor" << endl;
    cout << "8. GPU" << endl;
    cout << "9. CPU" << endl;
    cout << "Enter your choice: ";
    cin >> filterChoice;
    switch (filterChoice)
    {
        case 1: {
            int inventoryNumber;
            cout << "Enter inventory number: ";
            cin >> inventoryNumber;
            manager.InventoryFilter(inventoryNumber);
            break;
        }

        case 2: {
            int auditoriumNumber;
            cout << "Enter auditorium number: ";
            cin >> auditoriumNumber;
            manager.AuditoriumFilter(auditoriumNumber);
            break;
        }

        case 3: {
            int sizeOfRom;
            cout << "Enter size of ROM: ";
            cin >> sizeOfRom;
            manager.SizeOfRomFilter(sizeOfRom);
            break;
        }

        case 4: {
            bool hasCdRom;
            cout << "Has CD-ROM (1 for yes, 0 for no): ";
            cin >> hasCdRom;
            manager.HasCdRomFilter(hasCdRom);
            break;
        }

        case 5: {
            bool hasFloppyDisk;
            cout << "Has Floppy Disk (1 for yes, 0 for no): ";
            cin >> hasFloppyDisk;
            manager.HasFloppyDiskFilter(hasFloppyDisk);
            break;
        }

        case 6: {
            string keyboard;
            cout << "Enter keyboard type: ";
            cin >> keyboard;
            manager.KeyboardFilter(keyboard);
            break;
        }

        case 7: {
            string monitor;
            cout << "Enter monitor type: ";
            cin >> monitor;
            manager.MonitorFilter(monitor);
            break;
        }

        case 8: {
            string gpu;
            cout << "Enter GPU type: ";
            cin >> gpu;
            manager.GpuFilter(gpu);
            break;
        }

        case 9: {
            string cpu;
            cout << "Enter CPU type: ";
            cin >> cpu;
            manager.CpuFilter(cpu);
            break;
        }

        default:
            cout << "Invalid choice. Please try again." << endl;
        break;
    }
}

void Admin::SortMenu(Manager& manager)
{
    int sortOption;
    cout << "Sort computers by: " << endl;
    cout << "1. Inventory Number" << endl;
    cout << "2. Auditorium Number" << endl;
    cout << "Enter your choice: ";
    cin >> sortOption;
    if (sortOption == 1)
    {
        manager.SortByInventoryNumber();
        manager.ViewAllComputer();
    }
    else if (sortOption == 2)
    {
        manager.SortByAuditoriumNumber();
        manager.ViewAllComputer();
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
    };
};

void Admin::WorkedMenu(Manager& manager) {
    int inventoryNumber;
    cout << "Enter inventory number of the worked computer: ";
    cin >> inventoryNumber;

    bool found = false;
    auto& computers = manager.GetManager();

    for (auto& comp : computers)
    {
        auto worked = dynamic_cast<WorkedComputer*>(comp.get());
        if (worked && worked->GetInventoryNumber() == inventoryNumber)
        {
            found = true;
            int choice;
            do
            {
                cout << "\n--- Worked Computer Menu ---\n";
                cout << "1. Show Status\n";
                cout << "2. Update Status of Employment\n";
                cout << "3. Count Working Computers\n";
                cout << "4. Set Days Without Repair\n";
                cout << "5. Change Computer Status to Broken\n";
                cout << "6. Set Count of Users\n";
                cout << "7. Set Service Cost\n";
                cout << "8. Turn On\n";
                cout << "9. Turn Off\n";
                cout << "10. Show Employment Status\n";
                cout << "11. Show Days Without Repair\n";
                cout << "12. Show Count of Users\n";
                cout << "13. Show Service Cost\n";
                cout << "0. Back to Admin Menu\n";
                cout << "Your choice: ";
                cin >> choice;

                try
                {
                    switch (choice)
                    {
                        case 1:
                            worked->ShowStatus();
                            break;

                        case 2:
                            worked->UpdateStatus();
                            break;

                        case 3:
                            cout << "Counting working computers..." << endl;
                            manager.CountWorkingComputers();
                            break;
                        case 4:
                        {
                            int days;
                            cout << "Enter days without repair: ";
                            cin >> days;
                            worked->SetDays(days);
                        }
                            break;

                        case 5:
                            cout << "Changing computer status to Broken..." << endl;
                            manager.ChangeToBroken(inventoryNumber);
                            break;

                        case 6:
                        {
                            int users;
                            cout << "Enter count of users: ";
                            cin >> users;
                            worked->SetCountUsers(users);
                            break;
                        }

                        case 7:
                        {
                            int cost;
                            cout << "Enter service cost: ";
                            cin >> cost;
                            worked->ServiceCost(cost);
                            break;
                        }

                        case 8:
                            worked->TurnOn();
                            cout << "Computer turned on!\n";
                            break;

                        case 9:
                            worked->TurnOff();
                            cout << "Computer turned off!\n";
                            break;

                        case 10:
                            cout << "Employment Status: " << worked->GetEmploymentStatus() << endl;
                            break;

                        case 11:
                            cout << "Days without repair: " << worked->GetDays() << endl;
                            break;

                        case 12:
                            cout << "Count of users: " << worked->GetCountUsers() << endl;
                            break;

                        case 13:
                            cout << "Service cost: " << worked->GetServiceCost() << endl;
                            break;

                        case 0:
                            cout << "Returning to admin menu...\n";
                            break;

                        default:
                            cout << "Invalid option.\n";
                    }
                }
                catch (const Exeption& e)
                {
                    cout << "Error: " << e.what() << endl;
                }

            } while (choice != 0);

            manager.SaveToJson("database.json");
            break;
        }
    }

    if (!found)
    {
        cout << "Worked computer with that inventory number not found!\n";
    }
}

void Admin::RepairMenu(Manager& manager)
{
    int inventoryNumber;
    cout << "Enter inventory number of the repair computer: ";
    cin >> inventoryNumber;

    bool found = false;
    auto& computers = manager.GetManager();

    for (auto& comp : computers)
    {
        auto repair = dynamic_cast<RepairComputer*>(comp.get());
        if (repair && repair->GetInventoryNumber() == inventoryNumber)
        {
            found = true;
            int choice;

            do
            {
                cout << "\n--- Repair Computer Menu ---\n";
                cout << "1. Show Full Info\n";
                cout << "2. Update Repair Status\n";
                cout << "3. Show Count of Repair Computer\n";
                cout << "4. Set Repair Date\n";
                cout << "5. Set Problem Description\n";
                cout << "6. Set Cause of Problem\n";
                cout << "7. Set Repair Cost\n";
                cout << "8. Set if need new parts\n";
                cout << "9. Show Repair Status\n";
                cout << "10. Show Date of Repair\n";
                cout << "11. Show Problem Description\n";
                cout << "12. Show Cause of Problem\n";
                cout << "13. Show Repair Cost\n";
                cout << "14. Show if need new parts\n";
                cout << "15. Change to Working Computer\n";
                cout << "0. Back to Admin Menu\n";
                cout << "Your choice: ";
                cin >> choice;

                try
                {
                    switch (choice)
                    {
                        case 1:
                            repair->ShowFullInfo();
                            break;

                        case 2:
                            repair->UpdateRepairStatus();
                            break;

                        case 3:
                        cout << "Counting broken computers..." << endl;
                        manager.CountBrokenComputers();
                            break;

                        case 4:
                        {
                            string date;
                            cout << "Enter new repair date (YYYY-MM-DD): ";
                            cin >> date;
                            repair->SetDate(date);
                            break;
                        }

                        case 5:
                        {
                            string desc;
                            cin.ignore();
                            cout << "Enter problem description: ";
                            getline(cin, desc);
                            repair->SetDescribe(desc);
                            break;
                        }

                        case 6:
                        {
                            string cause;
                            cin.ignore();
                            cout << "Enter cause of problem: ";
                            getline(cin, cause);
                            repair->SetCause(cause);
                            break;
                        }

                        case 7:
                        {
                            int cost;
                            cout << "Enter repair cost: ";
                            cin >> cost;
                            repair->RepairCost(cost);
                            break;
                        }

                        case 8:
                        {
                            bool needNewParts;
                            repair->NeedsSpareParts(needNewParts);
                        }

                        case 9:
                            repair->ShowStatus();
                            break;

                        case 10:
                            cout << "Date of repair: " << repair->GetDate() << endl;
                            break;

                        case 11:
                            cout << "Problem description: " << repair->GetDescribe() << endl;
                            break;

                        case 12:
                            cout << "Cause of problem: " << repair->GetCause() << endl;
                            break;

                        case 13:
                            cout << "Repair cost: " << repair->GetRepairCost() << endl;
                            break;

                        case 14:
                            (repair->GetNeedNewParts() ? "Yes" : "No");
                        break;

                        case 15:
                            cout << "Changing status to WORKING..." << endl;
                            manager.ChangeToWorking(inventoryNumber);
                            break;

                        case 0:
                            cout << "Returning to Admin Menu...\n";
                            break;

                        default:
                            cout << "Invalid option. Please try again.\n";
                            break;
                    }
                }
                catch (const Exeption& e)
                {
                    cout << "Error: " << e.what() << endl;
                }

            } while (choice != 0);

            manager.SaveToJson("database.json");
            break;
        }
    }

    if (!found)
    {
        cout << "Repair computer with that inventory number not found!\n";
    }
}

void Admin::ChangesMenu(Manager& manager)
{
    int inventoryNumber;
    cout << "Enter the inventory number of the computer to modify: ";
    cin >> inventoryNumber;

    bool found = false;
    auto& computers = manager.GetManager();

    for (auto& comp : computers)
    {
        if (comp->GetInventoryNumber() == inventoryNumber)
        {
            found = true;
            int choice;

            do
            {
                cout << "\n--- Change Computer Fields Menu ---\n";
                cout << "1. Change Auditorium Number\n";
                cout << "2. Change Size of ROM\n";
                cout << "3. Change Has CD-ROM\n";
                cout << "4. Change Has Floppy Disk\n";
                cout << "5. Change Keyboard\n";
                cout << "6. Change Monitor\n";
                cout << "7. Change GPU\n";
                cout << "8. Change CPU\n";
                cout << "9. Back to Admin Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;

                try
                {
                    switch (choice)
                    {
                        case 1:
                        {
                            int newAuditorium;
                            cout << "Enter new Auditorium Number: ";
                            cin >> newAuditorium;
                            comp->MoveAuditorium(newAuditorium);
                            break;
                        }

                        case 2:
                        {
                            int newRom;
                            cout << "Enter new Size of ROM (GB): ";
                            cin >> newRom;
                            comp->SetSizeOfRom(newRom);
                            break;
                        }

                        case 3:
                        {
                            bool newCdRom;
                            cout << "Has CD-ROM (1 for yes, 0 for no): ";
                            cin >> newCdRom;
                            comp->HasCdRomUpdate(newCdRom);
                            break;
                        }

                        case 4:
                        {
                            bool newFloppy;
                            cout << "Has Floppy Disk (1 for yes, 0 for no): ";
                            cin >> newFloppy;
                            comp->HasFloppyDisk(newFloppy);
                            break;
                        }

                        case 5:
                        {
                            string newKeyboard;
                            cin.ignore();
                            cout << "Enter new Keyboard type: ";
                            getline(cin, newKeyboard);
                            comp->SetKeyboard(newKeyboard);
                            break;
                        }

                        case 6:
                        {
                            string newMonitor;
                            cout << "Enter new Monitor type: ";
                            getline(cin, newMonitor);
                            comp->SetMonitor(newMonitor);
                            break;
                        }

                        case 7:
                        {
                            string newGpu;
                            cout << "Enter new GPU type: ";
                            getline(cin, newGpu);
                            comp->SetGpu(newGpu);
                            break;
                        }

                        case 8:
                        {
                            string newCpu;
                            cout << "Enter new CPU type: ";
                            getline(cin, newCpu);
                            comp->SetCpu(newCpu);
                            break;
                        }

                        case 9:
                            cout << "Returning to Admin Menu...\n";
                            break;

                        default:
                            cout << "Invalid choice, try again.\n";
                            break;
                    }
                    manager.SaveToJson("database.json");
                }
                catch (const Exeption& e)
                {
                    cout << "Error: " << e.what() << endl;
                }

            } while (choice != 9);

            break;
        }
    }

    if (!found)
    {
        cout << "Computer with inventory number " << inventoryNumber << " not found.\n";
    }
}


string Admin::GetStatus() const
{
    return m_status;
}

Admin::~Admin()
{
    cout << "Destructor of Admin class" << endl;
};
