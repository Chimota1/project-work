#include <iostream>
#include "Manager.h"
#include "IUser.h"
#include "Admin.h"
#include "Exeption.h"
#include "DefaultUser.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;

int main()
{
    IUser* user = nullptr;
    Manager manager;
    bool isRunning = true;
    int choiceInMenu;

    ifstream userFile("users.txt");
    if (!userFile.is_open())
        throw Exeption("Cannot open users.txt file.");
    userFile.seekg(0, ios::end);
    if (userFile.tellg() == 0)
    {
        cout << "No users found. Please create an admin account." << endl;
        manager.AddUser();
    }
    userFile.close();

    do
    {
        cout << "\n1. Start \n";
        cout << "2. End Program \n";
        cout << "Enter your choice: ";
        cin >> choiceInMenu;

        if (choiceInMenu == 1)
        {
            int adminChoice;
            try {
                cout << "Are you an admin? (1. YES, 2. NO, 3. EXIT) \n";
                cin >> adminChoice;
                if (adminChoice != 1 && adminChoice != 2 && adminChoice != 3)
                    throw Exeption("wrong input");
            }
            catch (const Exeption& e) {
                cerr << "Error: " << e.what() << endl;
                continue;
            }

            if (adminChoice == 1)
            {
                Admin* admin = new Admin();
                try {
                    admin->Login();
                }
                catch (const Exeption& e) {
                    cerr << "Error: " << e.what() << endl;
                }
                delete admin;
            }
            else if (adminChoice == 2)
            {
                DefaultUser* userDefault = new DefaultUser();
                try {
                    userDefault->Login();
                }
                catch (const Exeption& e) {
                    cerr << "Error: " << e.what() << endl;
                }
                delete userDefault;
            }
            else if (adminChoice == 3)
            {
                continue;
            }
        }
        else if (choiceInMenu == 2)
        {
            isRunning = false;
        }
        else
        {
            cout << "Invalid menu choice. Try again.\n";
        }

    } while (isRunning);

    return 0;
}
