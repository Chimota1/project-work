#include "DefaultUser.h"
#include "IUser.h"
#include "Manager.h"
#include <iostream>
#include <string>
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
    Manager manager;
    string username, password;
    cout << "Введіть ім'я користувача: ";
    cin >> username;
    cout << "Введіть пароль: ";
    cin >> password;

    bool found = false;

    ifstream userFile("users.txt");
    if (!userFile.is_open())
        throw MyException("Не вдалося відкрити файл users.txt.");

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
                    username = fileUsername;
                    password = filePassword;
                    id = id;
           			status = role;
                    MainMenu(manager);
                    break;
                }
            }
        }
    }

    userFile.close();

    if (found)
        cout << "Вхід успішний!" << endl;
    else
        throw MyException("Невірне ім'я користувача або пароль");
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
            cout << "11. Довідка" << endl;
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
                    throw MyException("Неправильне введення");
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
    cout << "\n==================== МЕНЮ ДОВІДКИ КОРИСТУВАЧА ====================\n";
    cout << "Ласкаво просимо до системи керування комп’ютерами (CMS)\n";
    cout << "Цей розділ допоможе вам зрозуміти, як користуватись програмою як звичайному користувачу.\n";
    cout << "---------------------------------------------------------\n";

    cout << "\nОГЛЯД ГОЛОВНОГО МЕНЮ КОРИСТУВАЧА:\n";
    cout << "1. Переглянути всі комп’ютери     → Показує всі комп’ютери з бази даних\n";
    cout << "2. Переглянути мій ID             → Відображає ваш системний ID\n";
    cout << "3. Відфільтрувати комп’ютери     → Дає змогу фільтрувати комп’ютери за параметрами\n";
    cout << "4. Відсортувати комп’ютери       → Сортує за інвентарним або аудиторним номером\n";
    cout << "5. Підрахувати кількість          → Показує загальну кількість комп’ютерів\n";
    cout << "6. Зламані комп’ютери             → Показує кількість зламаних\n";
    cout << "7. Робочі комп’ютери              → Показує кількість робочих\n";
    cout << "8. Довідка                        → Виводить це меню допомоги\n";
    cout << "0. Вийти                          → Повертає до входу\n";
    cout << "---------------------------------------------------------\n";

    cout << "\nОПИС ПРОГРАМИ:\n";
    cout << " - Як звичайний користувач, ви можете лише *переглядати та аналізувати* дані.\n";
    cout << " - Ви НЕ МОЖЕТЕ додавати, видаляти або змінювати інформацію.\n";
    cout << " - Всі дані беруться з файлу 'database.json'.\n";
    cout << "---------------------------------------------------------\n";

    cout << "\nПРАВИЛА ВВЕДЕННЯ:\n";
    cout << " - Використовуйте цифри для вибору пунктів меню.\n";
    cout << " - Для запитань типу ТАК/НІ використовуйте 1 (так) або 0 (ні).\n";
    cout << " - Не залишайте порожніх полів під час введення.\n";
    cout << " - Дати (якщо потрібно) вводьте у форматі РРРР-ММ-ДД.\n";
    cout << "---------------------------------------------------------\n";

    cout << "\nПРИКЛАДИ ФІЛЬТРАЦІЇ ТА СОРТУВАННЯ:\n";
    cout << " - За 'інвентарним номером' — знайти конкретний комп’ютер.\n";
    cout << " - За 'CPU' або 'GPU' — знайти потрібну конфігурацію.\n";
    cout << " - За 'аудиторією' — згрупувати за приміщенням.\n";
    cout << "---------------------------------------------------------\n";

    cout << "\nДОДАТКОВІ ПРИМІТКИ:\n";
    cout << " - Дані автоматично зберігаються у 'database.json'.\n";
    cout << " - Ви можете безпечно переглядати інформацію, зміни не зберігаються.\n";
    cout << " - Якщо з’явилася помилка — перевірте правильність введення.\n";
    cout << "---------------------------------------------------------\n";

    cout << "Порада: використовуйте 'Фільтрацію', щоб швидко знайти потрібні дані.\n";
    cout << "===========================================================\n";
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
    cout << "3. Обсягом ПЗП" << endl;
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
            throw MyException("Неправильне введення");
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
        throw MyException("Невірне введення. Очікувалось число.");
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
            throw MyException("Невірне введення");
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
        throw MyException("Невірне введення. Очікувалось число.");
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
                    throw MyException("Невірний тип введення. Очікувалось число.");
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
                    throw MyException("Невірний тип введення. Очікувалось число.");
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
                    throw MyException("Невірний тип введення. Очікувалось число.");
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
                    throw MyException("Невірне введення. Введіть 1 або 0.");
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
                    throw MyException("Невірне введення. Введіть 1 або 0.");
                }
                manager.SearchByHasFloppyDisk(hasFloppyDisk);
                break;
            }

            default:
                throw MyException("Невірне введення");
        }
    }
    catch (MyException& e)
    {
        cerr << "Помилка: " << e.what() << endl;
    }
}

DefaultUser::~DefaultUser()
{
    cout << "Викликано деструктор DefaultUser" << endl;
};
