#include <iostream>
#include "Computer.h"
#include "RepairComputer.h"
#include "WorkedComputer.h"
#include "Manager.h"
#include "Interface.h"
#include <memory>
#include <fstream>
using namespace std;

void fileCheck(fstream &file)
{
    if (!file.is_open()) throw Exeption("File not found");
};

int main() {
    bool isRunning = true;
    bool isAdmin = false;
    int chooseAccount;
    int k;
    fstream file("password.txt", ios::in | ios::out | ios::app);
    string password;
    Manager manager;

    try
    {
        fileCheck(file);
    }
    catch (const Exeption &e)
    {
        cerr << "Exсeption: " << e.what() << endl;
        return 1;
    };

    cout << "Welcome to the Computer Management System" << endl;
    cout << "Choose account type: 1 - Admin, 2 - User" << endl;
    cin >> chooseAccount;
    while (isRunning)
    {
        if (chooseAccount == 1 && isAdmin == false)
        {
            cout << "You are using Admin account, please enter password" << endl;
            cin >> password;
            cin >> k;
            switch (k)
            {
                default:
                    cout << "Wrong key, try again" << endl;
                break;
                case 6:
                    isRunning = false;
                break;
            }
        }
        return 0;
    }
};