#include <windows.h>
#include <iostream>
#include <fstream>
#include "Manager.h"
#include "IUser.h"
#include "Admin.h"
#include "DefaultUser.h"
#include "MyException.h"
#include "ErrorMessage.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    bool isRunning = true;
    int choiceInMenu;

    Manager manager;

    ifstream userFile("users.txt");
    if (!userFile.is_open())
        throw MyException(ERR::FILE_OPEN_FAIL);

    userFile.seekg(0, ios::end);
    if (userFile.tellg() == 0)
    {
        cout << "Користувачів не знайдено. Створіть обліковий запис адміністратора." << endl;
        manager.AddUser();
    }
    userFile.close();


    while (isRunning)
    {
        try
        {
            cout << "\n1. Почати" << endl;
            cout << "2. Закрити програму" << endl;
            cout << "Введіть свій вибір: ";
            cin >> choiceInMenu;

            cin.peek();

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw MyException(ERR::INVALID_TYPE);
            }

            if (choiceInMenu == 1)
            {
                int adminChoice;

                cout << "Ви адміністратор? (1. ТАК, 2. ЗВИЧАЙНИЙ КОРИСТУВАЧ, 3. ВИХІД)\n";
                cin >> adminChoice;
                cin.peek();
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw MyException(ERR::INVALID_INPUT);
                }

                if (adminChoice == 1)
                {

                    IUser* admin = new Admin();

                    try
                    {
                        admin->Login();
                    }
                    catch (const MyException& e)
                    {
                        cout << "\nПомилка: " << e.what() << endl;
                        delete admin;
                        continue;
                    }

                    delete admin;
                }
                else if (adminChoice == 2)
                {

                    IUser* u = new DefaultUser();

                    try {
                        u->Login();
                    }
                    catch (const MyException& e)
                    {
                        cout << "\nПомилка: " << e.what() << endl;
                        delete u;
                        continue;
                    }

                    delete u;
                }
                else if (adminChoice == 3)
                {
                    continue;
                }
                else {
                    throw MyException("Невірний вибір.");
                }
            }

            else if (choiceInMenu == 2)
            {
                isRunning = false;
            }
            else
            {
                throw MyException("Невірний пункт меню.");
            }
        }
        catch (const MyException& e)
        {
            cout << "\nПомилка: " << e.what() << endl;
        }
    }

    return 0;
}
