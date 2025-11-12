#include "DefaultUser.h"
#include "IUser.h"
#include "Manager.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Exeption.h"

using namespace std;

DefaultUser::DefaultUser()
    : m_id(0), m_username(""), m_password(""), m_status("користувач")
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
    cout << "Введіть ім'я користувача: ";
    cin >> username;
    cout << "Введіть пароль: ";
    cin >> password;

    bool found = false;

    ifstream userFile("users.txt");
    if (!userFile.is_open())
        throw Exeption("Не вдалося відкрити файл users.txt.");

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
                    m_username = fileUsername;
                    m_password = filePassword;
                    m_id = id;
           			m_status = role;
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
        throw Exeption("Невірне ім'я користувача або пароль");
}

void DefaultUser::MainMenu(Manager& manager)
{
    int choice;
    manager.LoadFromJson("database.json");
    try {
        do
        {
            cout << "\nГоловне меню користувача" << endl;
            cout << "1. Переглянути всі комп’ютери" << endl;
            cout << "2. Переглянути мій ID" << endl;
            cout << "3. Відфільтрувати комп’ютери" << endl;
            cout << "4. Відсортувати комп’ютери за:" << endl;
            cout << "5. Підрахувати кількість комп’ютерів" << endl;
            cout << "6. Підрахувати кількість зламаних комп’ютерів" << endl;
            cout << "7. Підрахувати кількість робочих комп’ютерів" << endl;
            cout << "8. Довідка" << endl;
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
                    cout << "Фільтрація комп’ютерів..." << endl;
                    FilterMenu(manager);
                    break;

                case 4:
                    cout << "Сортування комп’ютерів..." << endl;
                    SortMenu(manager);
                    break;

                case 5:
                    cout << "Загальна кількість комп’ютерів: ";
                    manager.GetCount();
                    cout << endl;
                    break;

                case 6:
                    cout << "Кількість зламаних комп’ютерів: ";
                    manager.CountBrokenComputers();
                    cout << endl;
                    break;

                case 7:
                    cout << "Кількість робочих комп’ютерів: ";
                    manager.CountWorkingComputers();
                    cout << endl;
                    break;

                case 8:
                    HelpMenu();
                    break;

                case 0:
                    cout << "Вихід із системи..." << endl;
                    break;

                default:
                    throw Exeption("Неправильне введення");
            }
            manager.SaveToJson("database.json");
        } while (choice != 0);
    }
    catch (Exeption e)
    {
        cerr << "Помилка: " << e.what() << endl;
    }
};

int DefaultUser::GetID() const
{
    return m_id;
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
	return m_status;
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
            throw Exeption("Неправильне введення");
    };
}

void DefaultUser::SortMenu(Manager& manager)
{
    int sortOption;
    cout << "Відсортувати комп’ютери за: " << endl;
    cout << "1. Інвентарним номером" << endl;
    cout << "2. Номером аудиторії" << endl;
    cout << "Ваш вибір: ";
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
        throw Exeption("Неправильне введення");
    };
};

DefaultUser::~DefaultUser()
{
    cout << "Викликано деструктор DefaultUser" << endl;
};
