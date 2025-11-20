#include "Admin.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "json.hpp"
#include "MyException.h"
#include "Manager.h"
#include <limits>

using json = nlohmann::json;
using namespace std;

Admin::Admin():
    id(0),
    username("Anonymus"),
    password("null"),
    status("admin")
{
};

Admin::Admin(int id, const string& username, const string& password,const string& status):
    id(id),
    username(username),
    password(password),
    status(status)
{
};

Admin::Admin(const Admin& other)
{
    this->id = other.id;
    this->username = other.username;
    this->password = other.password;
    this->status = other.status;
};

Admin::Admin(Admin&& other) noexcept
{
    this->id = other.id;
    this->username = other.username;
    this->password = other.password;
    this->status = other.status;
};

void Admin::Login()
{
    string username, password;

    cout << "Введіть ім'я користувача: ";
    cin >> username;

    cout << "Введіть пароль: ";
    cin >> password;

    ifstream userFile("users.txt");
    if (!userFile.is_open())
        throw MyException("Неможливо відкрити файл users.txt.");

    bool found = false;
    string line;

    while (getline(userFile, line))
    {
        istringstream iss(line);

        int id;
        string loginData, role;

        if (!(iss >> id >> loginData >> role))
            continue;

        size_t colonPos = loginData.find(':');
        if (colonPos == string::npos)
            continue;

        string fileUsername = loginData.substr(0, colonPos);
        string filePassword = loginData.substr(colonPos + 1);

        if (username == fileUsername &&
            password == filePassword &&
            role == "admin")
        {
            found = true;
            status = "admin";
            break;
        }
    }

    if (!found)
        throw MyException("Невірні дані для входу або ви не адміністратор");

    cout << "Вхід успішний!" << endl;

    Manager manager;
    MainMenu(manager);
}





void Admin::MainMenu(Manager& manager)
{
    int choice;
    bool inMenu = true;
    manager.LoadFromJson("database.json");
        do {
            try
            {
                cout << "\nГоловне меню адміністратора\n";
                cout << "1. Переглянути всіх користувачів\n";
                cout << "2. Додати користувача\n";
                cout << "3. Переглянути всі комп'ютери\n";
                cout << "4. Видалити користувача\n";
                cout << "5. Додати новий комп'ютер\n";
                cout << "6. Подивитися мій ID\n";
                cout << "7. Подивитись мій статус\n";
                cout << "8. Фільтрувати комп'ютери \n";
                cout << "9. Сортувати комп'ютери \n";
                cout << "10. Пошук комп'ютера за атрибутами \n";
                cout << "11. Очистити всі комп'ютери\n";
                cout << "12. Підрахувати всі комп'ютери\n";
                cout << "13. Меню робочого комп'ютера\n";
                cout << "14. Меню комп'ютера в ремонті\n";
                cout << "15. Видалити комп'ютер\n";
                cout << "16. Меню зміни атрибутів комп'ютера\n";
                cout << "17. Допомога\n";
                cout << "18. Вийти з системи\n";
                cout << "Введіть ваш вибір: ";

                cin >> choice;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw MyException("Невірний тип введення. Очікувалось число.");
                }

                switch (choice)
                {
                    case 1:
                        cout << "Перегляд усіх користувачів..." << endl;
                    manager.ViewAllUsers();
                    break;

                    case 2:
                        cout << "Додавання користувача..." << endl;
                    manager.AddUser();
                    break;

                    case 3:
                        cout << "Всі комп'ютери: " << endl;
                        manager.ViewAllComputer();
                    break;

                    case 4:
                        cout << "Видалення користувача..." << endl;
                    manager.RemoveUser();
                    break;

                    case 5:
                        cout << "Додавання нового комп'ютера..." << endl;
                    manager.InitComputer();
                    break;

                    case 6:
                        cout << "Ваш ID: " << GetID() << endl;
                    break;

                    case 7:
                        cout << "Ваш статус: " << GetStatus() << endl;
                    break;

                    case 8:
                        FilterMenu(manager);
                    break;

                    case 9:
                        SortMenu(manager);
                    break;

                    case 10:
                        SearchMenu(manager);
                    break;

                    case 11:
                        cout << "Очищення всіх комп'ютерів..." << endl;
                    manager.ClearAll();
                    break;

                    case 12:
                        cout << "Підрахунок усіх комп'ютерів..." << endl;
                    manager.GetCount();
                    break;

                    case 13:
                        WorkedMenu(manager);
                    break;

                    case 14:
                        RepairMenu(manager);
                    break;

                    case 15:
                        cout << "Видалення комп'ютера..." << endl;
                    {
                        int inventoryNumber;
                        cout << "Введіть інвентарний номер комп'ютера для видалення: ";
                        cin >> inventoryNumber;
                        if (cin.fail() || inventoryNumber < 0)
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            throw MyException("Невірний тип введення. Очікувалось додатнє число.");
                        }
                        manager.RemoveComputer(inventoryNumber);
                    }
                    break;

                    case 16:
                        ChangesMenu(manager);
                    break;

                    case 17:
                        HelpMenu();
                    break;

                    case 18:
                        cout << "Вихід із системи..." << endl;
                        inMenu = false;
                    break;

                    default:
                        throw MyException("Невірне введення");
                }
                manager.SaveToJson("database.json");
            }
            catch (MyException& e)
            {
                cout << "\nПОМИЛКА: " << e.what() << endl;
            }
        } while (inMenu);
};

int Admin::GetID() const
{
    return id;
};


void Admin::HelpMenu() const
    {
        cout << "\n==================== МЕНЮ ДОПОМОГИ ====================\n";
        cout << "Ласкаво просимо до Бази даних \"Облік\" \n";
        cout << "Ця програма дозволяє адміністраторам керувати комп'ютерами та користувачами.\n";
        cout << "Ви можете додавати, видаляти, редагувати та переглядати комп'ютери, а також керувати обліковими записами користувачів.\n";
        cout << "----------------------------------------------------\n";
        cout << "\nОГЛЯД ГОЛОВНОГО МЕНЮ:\n";
        cout << "1. Переглянути всіх користувачів → Показує всіх зареєстрованих користувачів з users.txt\n";
        cout << "2. Додати користувача          → Створює нового користувача (адміна або звичайного)\n";
        cout << "3. Видалити користувача       → Видаляє існуючого користувача за ID або ім'ям\n";
        cout << "4. Додати новий комп'ютер  → Створює новий робочий або комп'ютер в ремонті\n";
        cout << "5. Подивитися мій ID         → Показує ваш поточний ID адміністратора\n";
        cout << "6. Фільтрувати комп'ютери  → Фільтрує комп'ютери за обраним параметром\n";
        cout << "7. Сортувати комп'ютери за → Сортує за інвентарним номером або номером аудиторії\n";
        cout << "8. Очистити всі комп'ютери → Видаляє всі комп'ютери з database.json\n";
        cout << "9. Підрахувати комп'ютери   → Показує загальну кількість комп'ютерів\n";
        cout << "10. Меню робочого комп'ютера → Доступ до налаштувань робочого комп'ютера\n";
        cout << "11. Меню комп'ютера в ремонті → Доступ до налаштувань комп'ютера в ремонті\n";
        cout << "12. Видалити комп'ютер     → Видалити конкретний комп'ютер за інвентарним номером\n";
        cout << "13. Меню змін             → Редагувати базову інформацію будь-якого комп'ютера\n";
        cout << "14. Допомога             → Показує це меню допомоги\n";
        cout << "15. Вийти з системи        → Вийти з режиму адміністратора та повернутися до входу\n";
        cout << "----------------------------------------------------\n";

        cout << "\nОПИС ПРОГРАМИ:\n";
        cout << " - Є два основних типи користувачів: Admin та DefaultUser.\n";
        cout << " - Адміністратор може керувати комп'ютерами та користувачами.\n";
        cout << " - DefaultUser може лише переглядати, фільтрувати та сортувати дані.\n";
        cout << " - Всі дані комп'ютерів зберігаються у 'database.json'.\n";
        cout << " - Дані користувачів (логін та ролі) зберігаються у 'users.txt'.\n";
        cout << "----------------------------------------------------\n";

        cout << "\nПРАВИЛА ВВЕДЕННЯ:\n";
        cout << " - Використовуйте цифри для вибору в меню.\n";
        cout << " - Використовуйте 1 для 'ТАК' та 0 для 'НІ' у логічних питаннях.\n";
        cout << " - Не залишайте текстові поля порожніми (наприклад, клавіатура, GPU, CPU, причина).\n";
        cout << " - Формат дати: РРРР-ММ-ДД.\n";
        cout << " - Кожна зміна автоматично зберігається у 'database.json'.\n";
        cout << "----------------------------------------------------\n";

        cout << "\nДОДАТКОВІ ПРИМІТКИ:\n";
        cout << " - Якщо ви отримуєте помилки 'MyException', перевірте введені значення.\n";
        cout << " - Ви завжди можете повернутися до головного меню за допомогою опції 0 або 16.\n";
        cout << " - Після кожної сесії дані надійно зберігаються у файлах.\n";
        cout << "----------------------------------------------------\n";

        cout << "Порада: Використовуйте 'Меню змін', щоб швидко оновити дані комп'ютера!\n";
        cout << "=====================================================\n";
    }

void Admin::FilterMenu(Manager& manager)
{
    int filterChoice;
    manager.LoadFromJson("database.json");
    cout << "Фільтрувати комп'ютери за: " << endl;
    cout << "1. Інвентарний номер" << endl;
    cout << "2. Номер аудиторії" << endl;
    cout << "3. Розмір ПЗП" << endl;
    cout << "4. Наявність CD-ROM" << endl;
    cout << "5. Наявність дискети" << endl;
    cout << "6. Клавіатура" << endl;
    cout << "7. Монітор" << endl;
    cout << "8. Відеокарта" << endl;
    cout << "9. Процесор" << endl;
    cout << "Введіть ваш вибір: ";
    cin >> filterChoice;

    try
    {
        switch (filterChoice)
        {
            case 1: {
                int inventoryNumber;
                cout << "Введіть інвентарний номер: ";
                cin >> inventoryNumber;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw MyException("Невірний тип введення. Очікувалось число.");
                }
                manager.InventoryFilter(inventoryNumber);
                break;
            }

            case 2: {
                int auditoriumNumber;
                cout << "Введіть номер аудиторії: ";
                cin >> auditoriumNumber;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw MyException("Невірний тип введення. Очікувалось число.");
                }
                manager.AuditoriumFilter(auditoriumNumber);
                break;
            }

            case 3: {
                int sizeOfRom;
                cout << "Введіть розмір диску: ";
                cin >> sizeOfRom;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw MyException("Невірний тип введення. Очікувалось число.");
                }
                manager.SizeOfRomFilter(sizeOfRom);
                break;
            }

            case 4: {
                bool hasCdRom;
                cout << "Має CD-ROM (1 - так, 0 - ні): ";
                cin >> hasCdRom;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw MyException("Невірне введення. Введіть 1 або 0.");
                }
                manager.HasCdRomFilter(hasCdRom);
                break;
            }

            case 5: {
                bool hasFloppyDisk;
                cout << "Має дискету (1 - так, 0 - ні): ";
                cin >> hasFloppyDisk;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw MyException("Невірне введення. Введіть 1 або 0.");
                }
                manager.HasFloppyDiskFilter(hasFloppyDisk);
                break;
            }

            case 6: {
                string keyboard;
                cout << "Введіть тип клавіатури: ";
                cin >> keyboard;
                if (keyboard.empty())
                    throw MyException("Рядок клавіатури порожній");
                manager.KeyboardFilter(keyboard);
                break;
            }

            case 7: {
                string monitor;
                cout << "Введіть тип монітора: ";
                cin >> monitor;
                if (monitor.empty())
                    throw MyException("Рядок монітора порожній");
                manager.MonitorFilter(monitor);
                break;
            }

            case 8: {
                string gpu;
                cout << "Введіть тип відеокарти: ";
                cin >> gpu;
                if (gpu.empty())
                    throw MyException("Рядок GPU порожній");
                manager.GpuFilter(gpu);
                break;
            }

            case 9: {
                string cpu;
                cout << "Введіть тип процесора: ";
                cin >> cpu;
                if (cpu.empty())
                    throw MyException("Рядок CPU порожній");
                manager.CpuFilter(cpu);
                break;
            }

            default:
                throw MyException("Невірне введення — виберіть від 1 до 9.");
        }
    }
    catch (MyException& e)
    {
        cout << "ПОМИЛКА: " << e.what() << endl;
    }
}


void Admin::SortMenu(Manager& manager)
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
        cout << "ПОМИЛКА: " << e.what() << endl;
    }
};

void Admin::SearchMenu(Manager& manager)
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
        cout << "ПОМИЛКА: " << e.what() << endl;
    }
}

void Admin::WorkedMenu(Manager& manager)
{
    int inventoryNumber;
    cout << "Введіть інвентарний номер робочого комп'ютера: ";
    cin >> inventoryNumber;

    if (cin.fail() || inventoryNumber <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw MyException("Невірне введення. Інвентарний номер має бути додатним числом.");
    }

    bool found = false;
    auto& computers = manager.GetManager();

    for (auto& comp : computers)
    {
        auto worked = dynamic_cast<WorkedComputer*>(comp.get());
        if (worked && worked->GetInventoryNumber() == inventoryNumber)
        {
            found = true;
            int choice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw MyException ("ПОМИЛКА: Невірне введення. Будь ласка, введіть число.");
                continue;
            }
            do
            {
                cout << "\n--- Меню робочого комп'ютера ---\n";
                cout << "1. Показати статус\n";
                cout << "2. Оновити статус зайнятості\n";
                cout << "3. Підрахувати робочі комп'ютери\n";
                cout << "4. Встановити днів без ремонту\n";
                cout << "5. Змінити статус комп'ютера на 'Зламаний'\n";
                cout << "6. Встановити кількість користувачів\n";
                cout << "7. Встановити вартість обслуговування\n";
                cout << "8. Увімкнути\n";
                cout << "9. Вимкнути\n";
                cout << "10. Показати статус зайнятості\n";
                cout << "11. Показати днів без ремонту\n";
                cout << "12. Показати кількість користувачів\n";
                cout << "13. Показати вартість обслуговування\n";
                cout << "14. Показати чи потрібне технічне обслуговування\n";
                cout << "0. Повернутися до меню адміністратора\n";
                cout << "Ваш вибір: ";

                cin >> choice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw MyException ("ПОМИЛКА: Невірне введення. Будь ласка, введіть число.");
                    continue;
                }

                try
                {
                    switch (choice)
                    {
                        case 1:
                            worked->ShowStatus();
                            break;

                        case 2:
                            worked->UpdateStatus();
                            break;

                        case 3:
                            cout << "Підрахунок робочих комп'ютерів..." << endl;
                            manager.CountWorkingComputers();
                            break;

                        case 4:
                        {
                            int days;
                            cout << "Введіть кількість днів без ремонту: ";
                            cin >> days;
                            if (cin.fail() || days < 0)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                throw MyException("Невірне введення. Кількість днів має бути 0 або додатним числом.");
                            }
                            worked->SetDays(days);
                            break;
                        }

                        case 5:
                            cout << "Зміна статусу комп'ютера на 'Зламаний'..." << endl;
                            manager.ChangeToBroken(inventoryNumber);
                            break;

                        case 6:
                        {
                            int users;
                            cout << "Введіть кількість користувачів: ";
                            cin >> users;
                            if (cin.fail() || users < 0)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                throw MyException("Невірне введення. Кількість користувачів має бути 0 або додатним числом.");
                            }
                            worked->SetCountUsers(users);
                            break;
                        }

                        case 7:
                        {
                            int cost;
                            cout << "Введіть вартість обслуговування: ";
                            cin >> cost;
                            if (cin.fail() || cost < 0)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                throw MyException("Невірне введення. Вартість обслуговування має бути 0 або додатним числом.");
                            }
                            worked->ServiceCost(cost);
                            break;
                        }

                        case 8:
                            worked->TurnOn();
                            cout << "Комп'ютер увімкнено!\n";
                            break;

                        case 9:
                            worked->TurnOff();
                            cout << "Комп'ютер вимкнено!\n";
                            break;

                        case 10:
                            cout << "Статус зайнятості: " << worked->GetEmploymentStatus() << endl;
                            break;

                        case 11:
                            cout << "Днів без ремонту: " << worked->GetDays() << endl;
                            break;

                        case 12:
                            cout << "Кількість користувачів: " << worked->GetCountUsers() << endl;
                            break;

                        case 13:
                            cout << "Вартість обслуговування: " << worked->GetServiceCost() << endl;
                            break;

                        case 14:
                            cout << "Потрібне технічне обслуговування: ";
                            worked->NeedsMaintenance();
                            cout << endl;

                        case 0:
                            cout << "Повернення до меню адміністратора...\n";
                            break;

                        default:
                            throw MyException("Невірний вибір меню. Будь ласка, оберіть від 0 до 13.");
                    }
                }
                catch (const MyException& e)
                {
                    cout << "ПОМИЛКА: " << e.what() << endl;
                }

            } while (choice != 0);

            manager.SaveToJson("database.json");
            break;
        }
    }

    if (!found)
    {
        cout << "Робочий комп'ютер з таким інвентарним номером не знайдено!\n";
    }
}

void Admin::RepairMenu(Manager& manager)
{
    int inventoryNumber;
    cout << "Введіть інвентарний номер комп'ютера в ремонті: ";
    cin >> inventoryNumber;

    if (cin.fail() || inventoryNumber <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw MyException("Невірне введення. Інвентарний номер має бути додатним числом.");
    }

    bool found = false;
    auto& computers = manager.GetManager();

    for (auto& comp : computers)
    {
        auto repair = dynamic_cast<RepairComputer*>(comp.get());
        if (repair && repair->GetInventoryNumber() == inventoryNumber)
        {
            found = true;
            int choice;

            do
            {
                cout << "\n--- Меню комп'ютера в ремонті ---\n";
                cout << "1. Показати повну інформацію\n";
                cout << "2. Оновити статус ремонту\n";
                cout << "3. Показати кількість комп'ютерів у ремонті\n";
                cout << "4. Встановити дату ремонту\n";
                cout << "5. Встановити опис проблеми\n";
                cout << "6. Встановити причину проблеми\n";
                cout << "7. Встановити вартість ремонту\n";
                cout << "8. Встановити потребу в нових деталях\n";
                cout << "9. Показати статус ремонту\n";
                cout << "10. Показати дату ремонту\n";
                cout << "11. Показати опис проблеми\n";
                cout << "12. Показати причину проблеми\n";
                cout << "13. Показати вартість ремонту\n";
                cout << "14. Показати повну інформацію про ремонт\n";
                cout << "15. Показати, чи потрібні нові деталі\n";
                cout << "16. Змінити на 'Робочий комп'ютер'\n";
                cout << "0. Повернутися до меню адміністратора\n";
                cout << "Ваш вибір: ";
                cin >> choice;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "ПОМИЛКА: Невірне введення. Будь ласка, введіть число.\n";
                    continue;
                }

                try
                {
                    switch (choice)
                    {
                        case 1:
                            repair->ShowFullInfo();
                            break;

                        case 2:
                            repair->UpdateRepairStatus();
                            break;

                        case 3:
                            cout << "Підрахунок зламаних комп'ютерів..." << endl;
                            manager.CountBrokenComputers();
                            break;

                        case 4:
                        {
                            string date;
                            cout << "Введіть нову дату ремонту (РРРР-ММ-ДД): ";
                            cin >> date;

                            if (cin.fail() || date.length() != 10)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                throw MyException("Невірний формат дати. Очікується РРРР-ММ-ДД.");
                            }

                            repair->SetDate(date);
                            break;
                        }

                        case 5:
                        {
                            string desc;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Введіть опис проблеми: ";
                            getline(cin, desc);
                            if (desc.empty())
                                throw MyException("Опис не може бути порожнім.");
                            repair->SetDescribe(desc);
                            break;
                        }

                        case 6:
                        {
                            string cause;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Введіть причину проблеми: ";
                            getline(cin, cause);
                            if (cause.empty())
                                throw MyException("Причина не може бути порожньою.");
                            repair->SetCause(cause);
                            break;
                        }

                        case 7:
                        {
                            int cost;
                            cout << "Введіть вартість ремонту: ";
                            cin >> cost;
                            if (cin.fail() || cost < 0)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                throw MyException("Невірне введення. Вартість ремонту має бути 0 або додатним числом.");
                            }
                            repair->RepairCost(cost);
                            break;
                        }

                        case 8:
                        {
                            int val;
                            cout << "Чи потрібні цьому комп'ютеру нові деталі? (1 = Так, 0 = Ні): ";
                            cin >> val;
                            if (cin.fail() || (val != 0 && val != 1))
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                throw MyException("Невірне введення. Введіть 1 для 'Так' або 0 для 'Ні'.");
                            }
                            repair->NeedsSpareParts(val);
                            break;
                        }

                        case 9:
                            repair->ShowStatus();
                            break;

                        case 10:
                            cout << "Дата ремонту: " << repair->GetDate() << endl;
                            break;

                        case 11:
                            cout << "Опис проблеми: " << repair->GetDescribe() << endl;
                            break;

                        case 12:
                            cout << "Причина проблеми: " << repair->GetCause() << endl;
                            break;

                        case 13:
                            cout << "Вартість ремонту: " << repair->GetRepairCost() << endl;
                            break;

                        case 14:
                            cout << "Повна інформація про ремонт:\n";
                            repair->ShowInfoAboutRepair();
                            break;

                        case 15:
                            cout << "Потрібні нові деталі: " << (repair->GetNeedNewParts() ? "Так" : "Ні") << endl;
                            break;

                        case 16:
                            cout << "Зміна статусу на 'РОБОЧИЙ'..." << endl;
                            manager.ChangeToWorking(inventoryNumber);
                            break;

                        case 0:
                            cout << "Повернення до меню адміністратора...\n";
                            break;

                        default:
                            throw MyException("Невірний вибір меню. Будь ласка, оберіть від 0 до 16.");
                    }
                }
                catch (const MyException& e)
                {
                    cout << "ПОМИЛКА: " << e.what() << endl;
                }

            } while (choice != 0);

            manager.SaveToJson("database.json");
            break;
        }
    }

    if (!found)
    {
        cout << "Комп'ютер в ремонті з таким інвентарним номером не знайдено!\n";
    }
}

void Admin::ChangesMenu(Manager& manager)
{
    int inventoryNumber;
    cout << "Введіть інвентарний номер комп'ютера для редагування: ";
    cin >> inventoryNumber;

    bool found = false;
    auto& computers = manager.GetManager();

    for (auto& comp : computers)
    {
        if (comp->GetInventoryNumber() == inventoryNumber)
        {
            found = true;
            int choice;

            do
            {
                cout << "\n--- Меню зміни полів комп'ютера ---\n";
                    cout << "1. Змінити номер аудиторії\n";
                    cout << "2. Змінити розмір жорсткого диску\n";
                    cout << "3. Змінити наявність CD-ROM\n";
                    cout << "4. Змінити наявність дискети\n";
                    cout << "5. Змінити клавіатуру\n";
                    cout << "6. Змінити монітор\n";
                    cout << "7. Змінити відеокарту\n";
                    cout << "8. Змінити процесор\n";
                    cout << "9. Повернутися до меню адміністратора\n";
                cout << "Введіть ваш вибір: ";
                cin >> choice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "ПОМИЛКА: Невірне введення.\n";
                    continue;
                }

                try
                {
                    switch (choice)
                    {
                        case 1:
                        {
                            int newAuditorium;
                            cout << "Введіть новий номер аудиторії: ";
                            cin >> newAuditorium;
                            if (cin.fail() || newAuditorium <= 0)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                throw MyException("Невірне введення. Номер аудиторії має бути додатним числом.");
                            }
                            comp->MoveAuditorium(newAuditorium);
                            break;
                        }

                        case 2:
                        {
                            int newRom;
                            cout << "Введіть новий розмір ПЗП (ГБ): ";
                            cin >> newRom;
                            if (cin.fail() || newRom <= 0)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                throw MyException("Невірне введення. Розмір жорсткого диску має бути додатним числом.");
                            }
                            comp->SetSizeOfRom(newRom);
                            break;
                        }

                        case 3:
                        {
                            bool newCdRom;
                            cout << "Має CD-ROM (1 - так, 0 - ні): ";
                            cin >> newCdRom;
                            if (cin.fail() || (newCdRom != 0 && newCdRom != 1))
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                throw MyException("Невірне введення. Введіть 1 для 'Так' або 0 для 'Ні'.");
                            }
                            comp->HasCdRomUpdate(newCdRom);
                            break;
                        }

                        case 4:
                        {
                            bool newFloppy;
                            cout << "Має дискету (1 - так, 0 - ні): ";
                            cin >> newFloppy;
                            if (cin.fail() || (newFloppy != 0 && newFloppy != 1))
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                throw MyException("Невірне введення. Введіть 1 для 'Так' або 0 для 'Ні'.");
                            }
                            comp->HasFloppyDiskUpdate(newFloppy);
                            break;
                        }

                        case 5:
                        {
                            string newKeyboard;
                            cin.ignore();
                            cout << "Введіть новий тип клавіатури: ";
                            getline(cin, newKeyboard);
                            comp->SetKeyboard(newKeyboard);
                            break;
                        }

                        case 6:
                        {
                            string newMonitor;
                            cout << "Введіть новий тип монітора: ";
                            getline(cin, newMonitor);
                            comp->SetMonitor(newMonitor);
                            break;
                        }

                        case 7:
                        {
                            string newGpu;
                            cout << "Введіть новий тип відеокарти: ";
                            getline(cin, newGpu);
                            comp->SetGpu(newGpu);
                            break;
                        }

                        case 8:
                        {
                            string newCpu;
                            cout << "Введіть новий тип процесора: ";
                            getline(cin, newCpu);
                            comp->SetCpu(newCpu);
                            break;
                        }

                        case 9:
                            cout << "Повернення до меню адміністратора...\n";
                            break;

                        default:
                            throw MyException("Невірне введення");
                            break;
                    }
                    manager.SaveToJson("database.json");
                }
                catch (const MyException& e)
                {
                    cout << "ПОМИЛКА: " << e.what() << endl;
                }

            } while (choice != 9);

            break;
        }
    }

    if (!found)
    {
        cout << "Комп'ютер з інвентарним номером " << inventoryNumber << " не знайдено.\n";
    }
}


string Admin::GetStatus() const
{
    return status;
}

Admin::~Admin()
{
    cout << "\nДеструктор класу Admin\n";
};