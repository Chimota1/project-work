#include "DefaultUser.h"
#include "Manager.h"
#include <iostream>
#include <string>
#include "ErrorMessage.h"
#include <fstream>
#include "MyException.h"

using namespace std;

DefaultUser::DefaultUser():
    id(0),
    username(""),
    password(""),
    status("user")
{
};

DefaultUser::DefaultUser(int id, const string& username, const string& password, const string status)
    : id(id), username(username), password(password), status(status)
{
};

DefaultUser::DefaultUser(const DefaultUser& other)
    : id(other.id), username(other.username), password(other.password), status(other.status)
{
};

DefaultUser::DefaultUser(DefaultUser&& other) noexcept
    : id(other.id), username(other.username), password(other.password), status(other.status)
{
}

void DefaultUser::Login()
{
    try {
        Manager manager;
        string username, password;

        cout << "Введіть ім'я користувача: ";
        cin >> username;
        cout << "Введіть пароль: ";
        cin >> password;

        bool found = false;

        ifstream userFile("users.txt");
        if (!userFile.is_open())
            throw MyException(ERR::FILE_OPEN_FAIL);

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

                    if (username == fileUsername &&
                        password == filePassword &&
                        role == "user")
                    {
                        found = true;
                        status = role;
                        break;
                    }
                }
            }
        }
        userFile.close();

        if (!found)
            throw MyException("Невірне ім'я користувача або пароль");

        cout << "Вхід успішний!" << endl;
        MainMenu(manager);
    }
    catch (const MyException& e) {
        cerr << "\nПомилка: " << e.what() << endl;
        return;
    }
}


void DefaultUser::MainMenu(Manager& manager)
{
    int choice;
    bool inMenu = true;
    manager.LoadFromJson("database.json");
    try {
        do
        {
            cout << "\nГоловне меню користувача" << endl;
            cout << "1. Переглянути всі комп’ютери" << endl;
            cout << "2. Переглянути мій ID" << endl;
            cout << "3. Переглянути мій статус" << endl;
            cout << "4. Відфільтрувати комп’ютери" << endl;
            cout << "5. Переглянути всі комп'ютери" << endl;
            cout << "6. Відсортувати комп’ютери за" << endl;
            cout << "7. Пошук Комп'ютера меню" << endl;
            cout << "8. Підрахувати кількість комп’ютерів" << endl;
            cout << "9. Підрахувати кількість зламаних комп’ютерів" << endl;
            cout << "10. Підрахувати кількість робочих комп’ютерів" << endl;
            cout << "11. Допомога" << endl;
            cout << "0. Вийти з системи" << endl;
            cout << "Ваш вибір: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    cout << "Перегляд усіх комп’ютерів..." << endl;
                    manager.ViewAllComputer();
                break;

                case 2:
                    cout << "Ваш ID: " << GetID() << endl;
                break;

                case 3:
                    cout << "Ваш статус: " << GetStatus() << endl;
                break;

                case 4:
                    cout << "Фільтрація комп’ютерів..." << endl;
                    FilterMenu(manager);
                break;

                case 5:
                    cout << "Всі комп'ютери: " << endl;
                    manager.ViewAllComputer();
                break;

                case 6:
                    cout << "Сортування комп’ютерів..." << endl;
                    SortMenu(manager);
                break;

                case 7:
                    cout << "Пошук комп’ютера..." << endl;
                    SearchMenu(manager);
                break;

                case 8:
                    cout << "Загальна кількість комп’ютерів: ";
                    manager.GetCount();
                    cout << endl;
                    break;

                case 9:
                    cout << "Кількість зламаних комп’ютерів: ";
                    manager.CountBrokenComputers();
                    cout << endl;
                break;

                case 10:
                    cout << "Кількість робочих комп’ютерів: ";
                    manager.CountWorkingComputers();
                    cout << endl;
                break;

                case 11:
                    HelpMenu();
                break;

                case 0:
                    cout << "Вихід із системи..." << endl;
                    inMenu = false;
                    break;

                default:
                    throw MyException(ERR::INVALID_INPUT);
            }
            manager.SaveToJson("database.json");
        } while (inMenu);
    }
    catch (MyException e)
    {
        cerr << "Помилка: " << e.what() << endl;
    }
};

int DefaultUser::GetID() const
{
    return id;
};

void DefaultUser::HelpMenu() const
{
    cout << "\n=================== ДОВІДКА ДЛЯ КОРИСТУВАЧА ===================\n";
    cout << "Система управління базою даних «Облік» дозволяє переглядати,\n"
            "фільтрувати та аналізувати комп’ютери, що знаходяться у базі.\n";
    cout << "-----------------------------------------------------------------\n";

    cout << "\nГОЛОВНЕ МЕНЮ:\n";
    cout << "1. Переглянути всі комп’ютери      – виводить повну таблицю ПК.\n";
    cout << "2. Переглянути мій ID              – показує ваш системний ідентифікатор.\n";
    cout << "3. Переглянути мій статус          – ваш тип доступу (user).\n";
    cout << "4. Фільтрація комп’ютерів          – пошук за параметрами.\n";
    cout << "5. Переглянути всі комп’ютери      – дублююча функція виводу.\n";
    cout << "6. Сортування комп’ютерів          – за інвентарним або аудиторією.\n";
    cout << "7. Пошук комп’ютера                – точковий пошук за параметром.\n";
    cout << "8. Кількість комп’ютерів           – показує загальну кількість.\n";
    cout << "9. Кількість зламаних              – комп’ютери зі статусом Broken.\n";
    cout << "10. Кількість робочих              – комп’ютери зі статусом Worked.\n";
    cout << "11. Допомога                         – це меню.\n";
    cout << "0. Вихід                            – повернення до авторизації.\n";
    cout << "-----------------------------------------------------------------\n";

    cout << "\nОПИС МОЖЛИВОСТЕЙ КОРИСТУВАЧА:\n";
    cout << "• Ви можете переглядати інформацію про всі комп’ютери.\n";
    cout << "• Фільтрувати дані за будь-яким параметром (CPU, GPU, інв. номер тощо).\n";
    cout << "• Шукати конкретний комп’ютер через швидке меню пошуку.\n";
    cout << "• Отримувати статистику кількості: загальної, робочих, зламаних.\n";
    cout << "• Сортувати комп’ютери за різними критеріями.\n";
    cout << "• Усі дані зчитуються з файлу database.json.\n";
    cout << "\n Звичайний користувач НЕ може редагувати або видаляти дані.\n";
    cout << "-----------------------------------------------------------------\n";

    cout << "\nПРАВИЛА ВВЕДЕННЯ:\n";
    cout << "• Вибір у меню здійснюється цифрами.\n";
    cout << "• Для параметрів типу «так/ні» використовуйте 1 або 0.\n";
    cout << "• Порожні значення не допускаються.\n";
    cout << "• Невірний ввід викликає повідомлення про помилку.\n";
    cout << "-----------------------------------------------------------------\n";

    cout << "\nПРИКЛАДИ ПРАКТИЧНОГО ВИКОРИСТАННЯ:\n";
    cout << "• Щоб знайти всі ПК у певній аудиторії → Фільтрація → № аудиторії.\n";
    cout << "• Щоб знайти комп’ютери з певним GPU → Пошук → GPU.\n";
    cout << "• Щоб дізнатись кількість робочих ПК → Пункт 10.\n";
    cout << "• Щоб побачити всі ПК → Пункт 1 або 5.\n";
    cout << "-----------------------------------------------------------------\n";

    cout << "Порада: найшвидший спосіб знайти потрібний ПК — використовувати меню пошуку.\n";
    cout << "=================================================================\n";
}


string DefaultUser::GetStatus() const
{
	return status;
}

void DefaultUser::FilterMenu(Manager& manager)
{
    int sortChoice;
    manager.LoadFromJson("database.json");
    cout << "Фільтрувати комп’ютери за: " << endl;
    cout << "1. Інвентарним номером" << endl;
    cout << "2. Номером аудиторії" << endl;
    cout << "3. Обсягом ROM" << endl;
    cout << "4. Наявністю CD-ROM" << endl;
    cout << "5. Наявністю дисководу" << endl;
    cout << "6. Типом клавіатури" << endl;
    cout << "7. Типом монітора" << endl;
    cout << "8. Типом GPU" << endl;
    cout << "9. Типом CPU" << endl;
    cout << "Ваш вибір: ";
    cin >> sortChoice;

    switch(sortChoice)
    {
        case 1: {
            int inventoryNumber;
            cout << "Введіть інвентарний номер: ";
            cin >> inventoryNumber;
            manager.InventoryFilter(inventoryNumber);
            break;
        }

        case 2: {
            int auditoriumNumber;
            cout << "Введіть номер аудиторії: ";
            cin >> auditoriumNumber;
            manager.AuditoriumFilter(auditoriumNumber);
            break;
        }

        case 3: {
            int sizeOfRom;
            cout << "Введіть обсяг ПЗП: ";
            cin >> sizeOfRom;
            manager.SizeOfRomFilter(sizeOfRom);
            break;
        }

        case 4: {
            bool hasCdRom;
            cout << "Чи є CD-ROM (1 — так, 0 — ні): ";
            cin >> hasCdRom;
            manager.HasCdRomFilter(hasCdRom);
            break;
        }

        case 5: {
            bool hasFloppyDisk;
            cout << "Чи є дисковод (1 — так, 0 — ні): ";
            cin >> hasFloppyDisk;
            manager.HasFloppyDiskFilter(hasFloppyDisk);
            break;
        }

        case 6: {
            string keyboard;
            cout << "Введіть тип клавіатури: ";
            cin >> keyboard;
            manager.KeyboardFilter(keyboard);
            break;
        }

        case 7: {
            string monitor;
            cout << "Введіть тип монітора: ";
            cin >> monitor;
            manager.MonitorFilter(monitor);
            break;
        }

        case 8: {
            string gpu;
            cout << "Введіть тип GPU: ";
            cin >> gpu;
            manager.GpuFilter(gpu);
            break;
        }

        case 9: {
            string cpu;
            cout << "Введіть тип CPU: ";
            cin >> cpu;
            manager.CpuFilter(cpu);
            break;
        }

        default:
            throw MyException(ERR::INVALID_INPUT);
    };
}

void DefaultUser::SortMenu(Manager& manager)
{
    int sortOption;
    cout << "Сортувати комп'ютери за: " << endl;
    cout << "1. Інвентарний номер" << endl;
    cout << "2. Номер аудиторії" << endl;
    cout << "Введіть ваш вибір: ";
    cin >> sortOption;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw MyException(ERR::INVALID_TYPE);
    }
    try {
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
            throw MyException(ERR::INVALID_INPUT);
        };
    }
    catch (MyException e)
    {
        cerr << "Помилка: " << e.what() << endl;
    }
};

void DefaultUser::SearchMenu(Manager& manager)
{
    int searchOption;
    cout << "Пошук комп'ютера за: " << endl;
    cout << "1. Інвентарним номером" << endl;
    cout << "2. Номером аудиторії" << endl;
    cout << "3. Процесором" << endl;
    cout << "4. Відеокартою" << endl;
    cout << "5. Монітором" << endl;
    cout << "6. Клавіатурою" << endl;
    cout << "7. Розміром диску" << endl;
    cout << "8. Наявністю CD-ROM" << endl;
    cout << "9. Наявністю дискети" << endl;
    cout << "Введіть ваш вибір: ";
    cin >> searchOption;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw MyException(ERR::INVALID_TYPE);
    }
    try
    {
        switch (searchOption)
        {
            case 1:
                {
                int inventoryNumber;
                cout << "Введіть інвентарний номер: ";
                cin >> inventoryNumber;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw MyException(ERR::INVALID_TYPE);
                }
                manager.SearchByInventoryNumber(inventoryNumber);
                break;
                }
            case 2:
            {
                int auditoriumNumber;
                cout << "Введіть номер аудиторії: ";
                cin >> auditoriumNumber;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw MyException(ERR::INVALID_TYPE);
                }
                manager.SearchByAuditoriumNumber(auditoriumNumber);
                break;
            }

            case 3:
            {
                string cpu;
                cout << "Введіть тип процесора: ";
                cin >> cpu;
                if (cpu.empty())
                    throw MyException("Рядок CPU порожній");
                manager.SearchByCpu(cpu);
                break;
            }

            case 4:
            {
                string gpu;
                cout << "Введіть тип відеокарти: ";
                cin >> gpu;
                if (gpu.empty())
                    throw MyException("Рядок GPU порожній");
                manager.SearchByGpu(gpu);
                break;
            }

            case 5:
            {
                string monitor;
                cout << "Введіть тип монітора: ";
                cin >> monitor;
                if (monitor.empty())
                    throw MyException("Рядок монітора порожній");
                manager.SearchByMonitor(monitor);
                break;
            }

            case 6:
            {
                string keyboard;
                cout << "Введіть тип клавіатури: ";
                cin >> keyboard;
                if (keyboard.empty())
                    throw MyException("Рядок клавіатури порожній");
                manager.SearchByKeyboard(keyboard);
                break;
            }

            case 7:
            {
                int sizeOfRom;
                cout << "Введіть розмір диску: ";
                cin >> sizeOfRom;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw MyException(ERR::INVALID_TYPE);
                }
                manager.SearchBySizeOfRom(sizeOfRom);
                break;
            }

            case 8:
            {
                bool hasCdRom;
                cout << "Має CD-ROM (1 - так, 0 - ні): ";
                cin >> hasCdRom;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw MyException(ERR::INVALID_INPUT + "Введіть 1 або 0.");
                }
                manager.SearchByHasCdRom(hasCdRom);
                break;
            }

            case 9:
            {
                bool hasFloppyDisk;
                cout << "Має дискету (1 - так, 0 - ні): ";
                cin >> hasFloppyDisk;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw MyException(ERR::INVALID_TYPE + "Введіть 1 або 0.");
                }
                manager.SearchByHasFloppyDisk(hasFloppyDisk);
                break;
            }

            default:
                throw MyException(ERR::INVALID_TYPE);
        }
    }
    catch (MyException& e)
    {
        cerr << "Помилка: " << e.what() << endl;
    }
}

DefaultUser::~DefaultUser()
{
    cout << "\nВикликано деструктор DefaultUser\n";
};
