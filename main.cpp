#define NOMINMAX
#define byte win_byte_override
#include <windows.h>
#undef byte

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
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    IUser* user = nullptr;
    Manager manager;
    bool isRunning = true;
    int choiceInMenu;

    ifstream userFile("users.txt");
    if (!userFile.is_open())
        throw Exeption("Не вдається відкрити users.txt файл.");
    userFile.seekg(0, ios::end);
    if (userFile.tellg() == 0)
    {
        cout << "Користувачів не знайдено. Будь ласка, створіть обліковий запис адміністратора." << endl;
        manager.AddUser();
    }
    userFile.close();

    do
    {
        cout << "\n1. Почати \n";
        cout << "2. Закрити програму \n";
        cout << "Введіть свій вибір: ";
        cin >> choiceInMenu;

        if (choiceInMenu == 1)
        {
            int adminChoice;
            try {
                cout << "Ви адміністратор? (1. ТАК, 2. НІ, 3. ВИХІД) \n";
                cin >> adminChoice;
                if (adminChoice != 1 && adminChoice != 2 && adminChoice != 3)
                    throw Exeption("Неправильне введення");
            }
            catch (const Exeption& e) {
                cerr << "Помилка: " << e.what() << endl;
                continue;
            }

            if (adminChoice == 1)
            {
                Admin* admin = new Admin();
                try {
                    admin->Login();
                }
                catch (const Exeption& e) {
                    cerr << "Помилка: " << e.what() << endl;
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
                    cerr << "Помилка: " << e.what() << endl;
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
            cout << "Невірний вибір меню. Спробуй ще раз.\n";
        }

    } while (isRunning);

    return 0;
}
