//
// Created by Tolya on 04.10.2025.
//

#include "Admin.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "json.hpp"
#include "Exeption.h"
#include "Manager.h"

using json = nlohmann::json;
using namespace std;

Admin::Admin()
    : m_id(0), m_username(""), m_password("")
{
};

Admin::Admin(int id, const string& username, const string& password)
    : m_id(id), m_username(username), m_password(password)
{
};

Admin::Admin(const Admin& other)
    : m_id(other.m_id), m_username(other.m_username), m_password(other.m_password)
{
};

Admin::Admin(Admin&& other) noexcept
    : m_id(other.m_id), m_username(other.m_username), m_password(other.m_password)
{
}

void Admin::Login()
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    bool found = false;

    ifstream jsonFile("users.json");
    ifstream passFile("password.txt");

    if (!jsonFile.is_open() || !passFile.is_open())
        throw Exeption("Cannot open user data files.");

    json users;
    jsonFile >> users;

    string fileUser, filePass;
    while (passFile >> fileUser >> filePass)
    {
        if (fileUser == username && filePass == password)
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        cout << "Login successful!" << endl;
        for (auto& user : users)
        {
            if (user["username"] == username)
            {
                cout << "Welcome, " << user["role"] << "!" << endl;
                m_id = user["id"];
                m_username = username;
                break;
            }
        }
        Manager manager;
        MainMenu(manager);
    }
    else
    {
        throw Exeption("Invalid username or password");
    }

    jsonFile.close();
    passFile.close();
}



void Admin::MainMenu(Manager& manager)
{
    int choice;
    do
    {
        cout << "\nAdmin Main Menu" << endl;
        cout << "1. View all Users" << endl;
        cout << "2. Add User" << endl;
        cout << "3. Remove User" << endl;
        cout << "4. Show Users Computer" << endl;
        cout << "5. See my ID" << endl;
        cout << "6. Filter Computers" << endl;
        cout << "7. Sort Computers by:" << endl;
        cout << "8. Clear All Computers" << endl;
        cout << "9. Count Computers" << endl;
        cout << "10. Count Broken Computers" << endl;
        cout << "11. Count Working Computers" << endl;
        cout << "12. Change Computer Status to Broken" << endl;
        cout << "13. Change Computer Status to Working" << endl;
        cout << "14. Remove Computer" << endl;
        cout << "15. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Viewing all users..." << endl;
                break;

            case 2:
                cout << "Adding a user..." << endl;
                // Implement add user functionality
                break;

            case 3:
                cout << "Removing a user..." << endl;
                // Implement remove user functionality
                break;

            case 4:
                cout << "Showing users computer..." << endl;
                manager.GetManager();
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
                cout << "Counting broken computers..." << endl;
                manager.CountBrokenComputers();
                break;

            case 11:
                cout << "Counting working computers..." << endl;
                manager.CountWorkingComputers();
                break;

            case 12:
                 cout << "Changing computer status to Broken..." << endl;
                 int inventoryNumber;
                 cout << "Enter inventory number of the computer: ";
                 cin >> inventoryNumber;
                 manager.ChangeToBroken(inventoryNumber);
            break;

            case 13:
                 cout << "Changing computer status to Working..." << endl;
                 {
                    int inventoryNumber;
                    cout << "Enter inventory number of the computer: ";
                    cin >> inventoryNumber;
                    manager.ChangeToWorking(inventoryNumber);
                 }
            break;

            case 14:
                cout << "Removing a computer..." << endl;
                {
                    int inventoryNumber;
                    cout << "Enter inventory number of the computer to remove: ";
                    cin >> inventoryNumber;
                    manager.RemoveComputer(inventoryNumber);
                }
            break;

            case 15:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 15);
};

void Admin::SetID()
{
    try {
        ifstream jsonFile("users.json");
        if (!jsonFile.is_open())
            throw Exeption("Cannot open users.json file.");

        json users;
        jsonFile >> users;
        jsonFile.close();

        bool found = false;

        for (const auto& user : users)
        {
            if (user.contains("username") && user["username"] == m_username)
            {
                if (user.contains("id"))
                    m_id = user["id"];
                if (user.contains("username"))
                    m_username = user["username"];
                found = true;
                break;
            }
        }

        if (!found)
            throw Exeption("User not found in users.json");
    }
    catch (const Exeption& e) {
        cerr << "Error while setting ID: " << e.what() << endl;
    }
}
void Admin::FilterMenu(Manager& manager)
{
    int sortChoice;
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
        case 1:
            int inventoryNumber;
            cout << "Enter inventory number: ";
            cin >> inventoryNumber;
            manager.InventoryFilter(inventoryNumber);
        break;

        case 2:
            int auditoriumNumber;
            cout << "Enter auditorium number: ";
            cin >> auditoriumNumber;
            manager.AuditoriumFilter(auditoriumNumber);
        break;

        case 3:
            int sizeOfRom;
            cout << "Enter size of ROM: ";
            cin >> sizeOfRom;
            manager.SizeOfRomFilter(sizeOfRom);
        break;

        case 4:
            bool hasCdRom;
            cout << "Has CD-ROM (1 for yes, 0 for no): ";
            cin >> hasCdRom;
            manager.HasCdRomFilter(hasCdRom);
        break;

        case 5:
            bool hasFloppyDisk;
            cout << "Has Floppy Disk (1 for yes, 0 for no): ";
            cin >> hasFloppyDisk;
            manager.HasFloppyDiskFilter(hasFloppyDisk);
        break;

        case 6:
            string keyboard;
            cout << "Enter keyboard type: ";
            cin >> keyboard;
            manager.KeyboardFilter(keyboard);
        break;

        case 7:
            string monitor;
            cout << "Enter monitor type: ";
            cin >> monitor;
            manager.MonitorFilter(monitor);
        break;

        case 8:
            string gpu;
            cout << "Enter GPU type: ";
            cin >> gpu;
            manager.GpuFilter(gpu);
        break;

        case 9:
            string cpu;
            cout << "Enter CPU type: ";
            cin >> cpu;
            manager.CpuFilter(cpu);
        break;

        default:
            cout << "Invalid choice. Please try again." << endl;
    };
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

Admin::~Admin()
{
    cout << "Destructor of Admin class" << endl;
};
