#include <iostream>
#include "Computer.h"
#include "RepairComputer.h"
#include "WorkedComputer.h"
#include "Manager.h"
#include "Interface.h"
#include <memory>
using namespace std;

int main()
{
    bool isRunning = true;
    int k;
    Manager manager;

    cout << "Welcome to the Computer Management System" << endl;
    cout << "use key for using program" << endl;
    while (isRunning)
    {
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
};