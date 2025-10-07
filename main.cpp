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
    bool IsAdmin = false;
    ifstream userFile("users.txt");
    if (!userFile.is_open())
        throw Exeption("Cannot open users.txt file.");
    userFile.seekg(0, ios::end);

    if (userFile.tellg() == 0)
    {
        cout << "No users found. Please create an admin account." << endl;
        manager.AddUser();
    }
    cout << "Are you an admin? (1 for Yes, 0 for No): ";
    cin >> IsAdmin;
    if (IsAdmin)
    {
        user = new Admin();
        user->Login();
        delete user;
    }
    else
    {
        user = new DefaultUser();
        user->Login();
        delete user;
    }
    return 0;
};