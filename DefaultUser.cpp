#include "DefaultUser.h"
#include "IUser.h"
#include "Manager.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Exeption.h"

using namespace std;

DefaultUser::DefaultUser()
    : m_id(0), m_username(""), m_password(""), m_status("user")
{
};

DefaultUser::DefaultUser(int id, const string& username, const string& password, const string status)
    : m_id(id), m_username(username), m_password(password), m_status(status)
{
};

DefaultUser::DefaultUser(const DefaultUser& other)
    : m_id(other.m_id), m_username(other.m_username), m_password(other.m_password), m_status(other.m_status)
{
};

DefaultUser::DefaultUser(DefaultUser&& other) noexcept
    : m_id(other.m_id), m_username(other.m_username), m_password(other.m_password), m_status(other.m_status)
{
}

void DefaultUser::Login()
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

                if (username == fileUsername && password == filePassword && role == "user") {
                    found = true;
                    m_username = fileUsername;
                    m_password = filePassword;
                    m_id = id;
           			m_status = role;
                    break;
                }
            }
        }
    }

    userFile.close();

    if (found)
        cout << "Login successful!" << endl;
    else
        throw Exeption("Invalid username or password");
}

void DefaultUser::MainMenu(Manager& manager)
{
    int choice;
    manager.LoadFromJson("database.json");
    do
    {
        cout << "\nUser Main Menu" << endl;
        cout << "1. View all Computers" << endl;
        cout << "2. See my ID" << endl;
        cout << "3. Filter Computers" << endl;
        cout << "4. Sort Computers by:" << endl;
        cout << "5. Count Computers" << endl;
        cout << "6. Count Broken Computers" << endl;
        cout << "7. Count Working Computers" << endl;
        cout << "8. Help\n";
        cout << "0. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Viewing all computers..." << endl;
                manager.ViewAllComputer();
                break;

            case 2:
                cout << "Your ID is: " << GetID() << endl;
                break;

            case 3:
                cout << "Filtering computers..." << endl;
                FilterMenu(manager);
                break;

            case 4:
                cout << "Sorting computers..." << endl;
                SortMenu(manager);
                break;

            case 5:
				cout << "Total computers: ";
                manager.GetCount();
                cout << endl;
                break;

            case 6:
				cout << "Total broken computers: ";
                manager.CountBrokenComputers();
                cout << endl;
                break;

            case 7:
                 cout << "Total working computers: ";
				 manager.CountWorkingComputers();
                 cout << endl;
                break;

            case 0:
                cout << "Logging out..." << endl;
                break;

            default:
                 cout << "Invalid choice. Please try again." << endl;
        	}
        	manager.SaveToJson("database.json");
    	} while (choice != 8);
	};

int DefaultUser::GetID() const
{
    return m_id;
};

void DefaultUser::HelpMenu() const
{
    cout << "\n==================== USER HELP MENU ====================\n";
    cout << "Welcome to the Computer Management System (CMS)\n";
    cout << "This section will help you understand how to use the program as a regular user.\n";
    cout << "---------------------------------------------------------\n";

    cout << "\nUSER MAIN MENU OVERVIEW:\n";
    cout << "1. View all Computers     → Shows all computers stored in the database\n";
    cout << "2. See my ID              → Displays your user ID from the system\n";
    cout << "3. Filter Computers       → Allows you to filter computers by various parameters\n";
    cout << "4. Sort Computers by      → Sorts computers by inventory or auditorium number\n";
    cout << "5. Count Computers        → Shows the total number of computers\n";
    cout << "6. Count Broken Computers → Displays how many computers are currently broken\n";
    cout << "7. Count Working Computers→ Displays how many computers are working\n";
    cout << "8. Help                   → Displays this help information\n";
    cout << "9. Logout                 → Exits to the login screen\n";
    cout << "---------------------------------------------------------\n";

    cout << "\nPROGRAM DESCRIPTION:\n";
    cout << " - As a regular user, you can only *view and analyze* computer data.\n";
    cout << " - You CANNOT add, delete, or modify computers or users.\n";
    cout << " - All information you see comes from 'database.json'.\n";
    cout << "---------------------------------------------------------\n";

    cout << "\nINPUT RULES:\n";
    cout << " - Use numbers for choosing menu options.\n";
    cout << " - When asked YES/NO questions, use 1 for YES and 0 for NO.\n";
    cout << " - Do not leave empty input fields (e.g., when entering text).\n";
    cout << " - Dates, if requested, must be in the format YYYY-MM-DD.\n";
    cout << "---------------------------------------------------------\n";

    cout << "\nFILTER & SORT EXAMPLES:\n";
    cout << " - Filter by 'Inventory Number' to find a specific computer.\n";
    cout << " - Filter by 'CPU' or 'GPU' to find certain configurations.\n";
    cout << " - Sort computers by 'Auditorium Number' to group them by room.\n";
    cout << "---------------------------------------------------------\n";

    cout << "\nADDITIONAL NOTES:\n";
    cout << " - Data is automatically loaded from and saved to 'database.json'.\n";
    cout << " - You can explore data safely — changes are not allowed in this mode.\n";
    cout << " - If you get an error message (Exeption), check your input format.\n";
    cout << "---------------------------------------------------------\n";

    cout << "Tip: Use 'Filter Computers' to quickly find what you need.\n";
    cout << "===========================================================\n";
}


string DefaultUser::GetStatus() const
{
	return m_status;
}

void DefaultUser::FilterMenu(Manager& manager)
{
    int sortChoice;
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
    cin >> sortChoice;
    switch(sortChoice)
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
    };
}

void DefaultUser::SortMenu(Manager& manager)
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
    }
    else if (sortOption == 2)
    {
        manager.SortByAuditoriumNumber();
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
    };
};

DefaultUser::~DefaultUser()
{
    cout << "DefaultUser destructor called" << endl;
};
