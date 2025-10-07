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

                if (username == fileUsername && password == filePassword) {
                    found = true;
                    m_username = fileUsername;
                    m_password = filePassword;
                    m_id = manager.GetLastID();
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
        cout << "8. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Viewing all computers..." << endl;
                manager.GetManager();
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

            case 8:
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
