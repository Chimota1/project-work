#include "Manager.h"
#include "Computer.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "WorkedComputer.h"
#include "RepairComputer.h"
#include "MyException.h"
#include "json.hpp"
#include <fstream>
#include <memory>
#include <cstdlib>
#include <limits>

using namespace std;
using json = nlohmann::json;

Manager::Manager() :
thisComputer{}
{
};

Manager::Manager(vector<shared_ptr<Computer>> thisComputer):
    thisComputer{thisComputer}
{
};

Manager::Manager(const Manager &other)
{
    this->thisComputer = other.thisComputer;
};

Manager::Manager(Manager &&other) noexcept
{
    this->thisComputer = other.thisComputer;
};

vector<shared_ptr<Computer>>& Manager::GetManager()
{
    return thisComputer;
};

void Manager::SetManager(shared_ptr<Computer> thisComputer)
{
    this->thisComputer.push_back(thisComputer);
};

void Manager::ViewAllUsers() const
{
    try
    {
        ifstream userFile("users.txt");
        if (!userFile.is_open())
            throw MyException("Не вдається відкрити файл users.txt.");
        string line;
        while (getline(userFile, line))
        {
            cout << line << endl;
        }
        userFile.close();
    }
    catch (const MyException& e)
    {
        throw MyException("Помилка зчитування users.json: " + string(e.what()));
    }
};

void Manager::AddUser()
{
    ifstream checkFile("users.txt");
    bool fileIsEmpty = false;

    checkFile.seekg(0, ios::end);
    if (checkFile.tellg() == 0)
        fileIsEmpty = true;
    checkFile.close();

    bool accountCreated = false;

    while (!accountCreated)
    {
        try {
            string username, password, role;
            int newID;

            cout << "Введіть нове ім'я користувача: ";
            cin >> username;

            cout << "Введіть новий пароль: ";
            cin >> password;

            cout << "Введіть роль (admin/user): ";
            cin >> role;

            if (role != "admin" && role != "user")
                throw MyException("Неправильна роль. Доступні: admin або user.");

            ifstream userFileCheck("users.txt");
            if (!userFileCheck.is_open())
                throw MyException("Не вдається відкрити users.txt файл.");

            bool adminExists = false;
            string line;

            while (getline(userFileCheck, line))
            {
                if (line.find(" admin") != string::npos)
                {
                    adminExists = true;
                    break;
                }
            }
            userFileCheck.close();

            if (!adminExists && role == "user")
                throw MyException("Неможливо створити простого користувача, поки не існує жодного адміністратора.");

            ofstream userFile("users.txt", ios::app);
            if (!userFile.is_open())
                throw MyException("Не вдається відкрити users.txt файл.");

            GenerateID(newID);

            userFile << newID << " " << username << ":" << password << " " << role << endl;
            userFile.close();

            cout << "Користувач успішно доданий!" << endl;
            cout << "Присвоєно ID: " << newID << endl;

            lastID = newID;
            accountCreated = true;

            break;
        }
        catch (const MyException& e)
        {
            cout << "Помилка при додаванні користувача: " << e.what() << endl;
            if (!fileIsEmpty)
                break;
        }
    }
}




void Manager::RemoveUser() {
    try {
        int userId;
        cout << "Введіть ID користувача, щоб видалити: ";
        cin >> userId;

        ifstream userFile("users.txt");
        if (!userFile.is_open())
            throw MyException("Не вдається відкрити файл users.txt.");

        string line;
        vector<string> lines;
        bool found = false;
        while (getline(userFile, line)) {
            if (line.find(to_string(userId) + " ") != 0) {
                lines.push_back(line);
            } else {
                found = true;
            }
        }
        userFile.close();

        if (!found) {
            throw MyException ("Користувача з таким ID не існує");
        }

        ofstream outFile("users.txt");
        for (const auto& l : lines) {
            outFile << l << endl;
        }
        outFile.close();

        cout << "Користувач успішно видалений!" << endl;
    }
    catch (const MyException& e) {
        cout << "Помилка при видаленні користувача: " << e.what() << endl;
    }
}

int Manager::GetLastID() const
{
    return lastID;
}

void Manager::AuditoriumFilter(int auditoriumNumber) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetAuditoriumNumber() == auditoriumNumber) {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw MyException ("Не знайдено комп'ютерів, які б відповідали заданим критеріям.");
};

void Manager::InventoryFilter(int inventoryNumber) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetInventoryNumber() == inventoryNumber)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw MyException ("Не знайдено комп'ютерів, які б відповідали заданим критеріям.");
};

void Manager::SizeOfRomFilter(int sizeOfRom) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it) {
        if ((*it)->GetSizeOfRom() == sizeOfRom){
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw MyException ("Не знайдено комп'ютерів, які б відповідали заданим критеріям.");
};

void Manager::HasCdRomFilter(bool hasCdRom) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetHasCdRom() == hasCdRom)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw MyException ("Не знайдено комп'ютерів, які б відповідали заданим критеріям.");
};

void Manager::HasFloppyDiskFilter(bool hasFloppyDisk) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetHasFloppyDisk() == hasFloppyDisk)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw MyException ("Не знайдено комп'ютерів, які б відповідали заданим критеріям.");
};

void Manager::KeyboardFilter(string keyboard) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetKeyboard() == keyboard)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw MyException ("Не знайдено комп'ютерів, які б відповідали заданим критеріям.");
};

void Manager::MonitorFilter(string monitor) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetMonitor() == monitor)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw MyException ("Не знайдено комп'ютерів, які б відповідали заданим критеріям.");
};

void Manager::GpuFilter(string gpu) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetGpu() == gpu)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw MyException ("Не знайдено комп'ютерів, які б відповідали заданим критеріям.");
};

void Manager::CpuFilter(string cpu) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it) {
        if ((*it)->GetCpu() == cpu)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
        };
    };
    if (!found) throw MyException ("Не знайдено комп'ютерів, які б відповідали заданим критеріям.");
};

int Manager::GenerateID(int& id)
{
    srand(time(0));
    id = rand() % 999 + 100;
    return id;
}

void Manager::ViewAllComputer() const
{
    if (thisComputer.empty())
        throw MyException("Список комп'ютерів пустий");
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        cout << (*it)->GetComputerFull() << endl;
    }
};


void Manager::InitComputer()
{
    int choice;
    cout << "Виберіть тип комп'ютера, який потрібно додати:" << endl;
    cout << "1. Справний комп'ютер" << endl;
    cout << "2. Несправний комп'ютер" << endl;
    cout << "Введіть свій вибір: ";
    cin >> choice;

    if (cin.fail() || (choice != 1 && choice != 2))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw MyException("Невірне введення. Введіть 1 або 2.");
    }

    shared_ptr<Computer> newComputer;

    if (choice == 1)
        newComputer = make_shared<WorkedComputer>();
    else
        newComputer = make_shared<RepairComputer>();

    int inventoryNumber, auditoriumNumber, sizeOfRom;
    bool hasCdRom, hasFloppyDisk;
    string keyboard, monitor, gpu, cpu;

    cout << "Введіть інвентарний номер: ";
    cin >> inventoryNumber;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw MyException("Невірний тип введення. Очікувалось число.");
    }
    newComputer->SetInventoryNumber(inventoryNumber);

    cout << "Введіть номер аудиторії: ";
    cin >> auditoriumNumber;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw MyException("Невірний тип введення. Очікувалось число.");
    }
    newComputer->SetAuditoriumNumber(auditoriumNumber);

    cout << "Введіть розмір ROM (GB): ";
    cin >> sizeOfRom;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw MyException("Невірний тип введення. Очікувалось число.");
    }
    newComputer->SetSizeOfRom(sizeOfRom);

    cout << "Має CD-ROM (1 якщо так, 0 якщо ні): ";
    cin >> hasCdRom;
    if (cin.fail() || (hasCdRom != 0 && hasCdRom != 1))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw MyException("Невірне введення. Введіть 1 або 0.");
    }
    newComputer->SetHasCdRom(hasCdRom);

    cout << "Має Floppy Disk (1 якщо так, 0 якщо ні): ";
    cin >> hasFloppyDisk;
    if (cin.fail() || (hasFloppyDisk != 0 && hasFloppyDisk != 1))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw MyException("Невірне введення. Введіть 1 або 0.");
    }
    newComputer->SetHasFloppyDisk(hasFloppyDisk);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Введіть тип клавіатури: ";
    getline(cin, keyboard);
    newComputer->SetKeyboard(keyboard);

    cout << "Введіть тип монітора: ";
    getline(cin, monitor);
    newComputer->SetMonitor(monitor);

    cout << "Введіть тип графічного процесора: ";
    getline(cin, gpu);
    newComputer->SetGpu(gpu);

    cout << "Введіть тип процесора: ";
    getline(cin, cpu);
    newComputer->SetCpu(cpu);

    if (choice == 1)
    {
        auto workedComp = dynamic_cast<WorkedComputer*>(newComputer.get());
        if (workedComp)
        {
            int daysWithoutRepair, countUsers, serviceCost, statusOfWork;

            cout << "Введіть дні без ремонту: ";
            cin >> daysWithoutRepair;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw MyException("Невірний тип введення. Очікувалось число.");
            }
            workedComp->SetDays(daysWithoutRepair);

            cout << "Введіть кількість користувачів: ";
            cin >> countUsers;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw MyException("Невірний тип введення. Очікувалось число.");
            }
            workedComp->SetCountUsers(countUsers);

            cout << "Введіть статус роботи (1 якщо включено / 2 якщо вимкнено): ";
            cin >> statusOfWork;
            if (cin.fail() || (statusOfWork != 1 && statusOfWork != 2))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw MyException("Невірне введення. Введіть 1 або 2.");
            }

            if (statusOfWork == 1) workedComp->TurnOn();
            else workedComp->TurnOff();

            cout << "Введіть вартість послуги: ";
            cin >> serviceCost;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw MyException("Невірний тип введення. Очікувалось число.");
            }
            workedComp->ServiceCost(serviceCost);
        }
    }

    else if (choice == 2)
    {
        auto repairComp = dynamic_cast<RepairComputer*>(newComputer.get());
        if (repairComp)
        {
            string dateOfRepair, describeOfProblem, cause;
            int repairCost;

            cout << "Введіть дату ремонту (YYYY-MM-DD): ";
            cin >> dateOfRepair;
            if (cin.fail() || dateOfRepair.length() != 10)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw MyException("Неприпустимий формат дати. Очікуваний YYYY-MM-DD.");
            }
            repairComp->SetDate(dateOfRepair);

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введіть опис проблеми: ";
            getline(cin, describeOfProblem);
            repairComp->SetDescribe(describeOfProblem);

            cout << "Введіть причину проблеми: ";
            getline(cin, cause);
            repairComp->SetCause(cause);

            cout << "Введіть вартість ремонту: ";
            cin >> repairCost;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw MyException("Невірний тип введення. Очікувалось число.");
            }
            repairComp->RepairCost(repairCost);
        }
    }

    thisComputer.push_back(newComputer);
    SaveToJson("database.json");
}

void Manager::RemoveComputer(int inventoryNumber)
{
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetInventoryNumber()  == inventoryNumber)
        {
            cout << "Видалення успішне!" << endl;
            thisComputer.erase(it);
            return;
        }
    }
    throw MyException("Комп'ютер з таким інвентарним номером не знайдено");
};

void Manager::ClearAll()
{
    int choice;
    cout << "Ви впевнені, що хочете очистити весь список комп'ютерів? (1 - так, 2 - ні): ";
    cin >> choice;
    if (cin.fail() || (choice != 1 && choice != 2))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw MyException("Невірне введення. Введіть 1 або 2.");
    }
    if (choice == 1) {
        if (thisComputer.empty()) throw MyException("список порожній, не можливо очистити");
        thisComputer.clear();
    }

    else if (choice == 2) {
        cout << "Очищення скасовано." << endl;
    };
}

void Manager::GetCount() const
{
    if (thisComputer.empty()) throw MyException("масив порожній, не можливо порахувати");
    cout << "Кількість всіх комп'ютерів " << thisComputer.size();
}

void Manager::CountBrokenComputers() const
{
    int count = 0;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if (dynamic_cast<RepairComputer*>(it->get()) != nullptr)
        {
            count++;
        }
        if (count == 0) throw MyException("У базі даних не знайдено зламаних комп'ютерів!");
    }
    cout << "Кількість зламаних комп'ютерів: " << count << endl;
}

void Manager::CountWorkingComputers() const
{
    int count = 0;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if (dynamic_cast<WorkedComputer*>(it->get()) != nullptr)
        {
            count++;
        }
        if (count == 0) throw MyException("У базі даних не знайдено робочих комп'ютерів!");
    }
    cout << "Кількість робочих комп'ютерів: " << count << endl;
}

void Manager::SortByInventoryNumber()
{
    if (thisComputer.empty()) throw MyException("масив порожній, не можливо відсортувати");
    sort(thisComputer.begin(), thisComputer.end(),
         [](const shared_ptr<Computer>& first, const shared_ptr<Computer>& last)
         {
             return first->GetInventoryNumber() < last->GetInventoryNumber();
         });
    SaveToJson("database.json");
};

void Manager::SortByAuditoriumNumber()
{
    if (thisComputer.empty()) throw MyException("масив порожній, не можливо відсортувати");
    sort(thisComputer.begin(), thisComputer.end(),
         [](const shared_ptr<Computer>& first, const shared_ptr<Computer>& last)
         {
             return first->GetAuditoriumNumber() < last->GetAuditoriumNumber();
         });
    SaveToJson("database.json");
};

void Manager::SearchByInventoryNumber(int inventoryNumber) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetInventoryNumber() == inventoryNumber)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
            break;
        }
    }
    if (!found) throw MyException("Комп'ютер з таким інвентарним номером не знайдено");
};

void Manager::SearchByAuditoriumNumber(int auditoriumNumber) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetAuditoriumNumber() == auditoriumNumber)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
            break;
        }
    }
    if (!found) throw MyException("Комп'ютер з таким номером аудиторії не знайдено");
};

void Manager::SearchByCpu(string cpu) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetCpu() == cpu)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
            break;
        }
    }
    if (!found) throw MyException("Комп'ютер з таким процесором не знайдено");
};

void Manager::SearchByGpu(string gpu) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetGpu() == gpu)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
            break;
        }
    }
    if (!found) throw MyException("Комп'ютер з таким графічним процесором не знайдено");
};

void Manager::SearchByMonitor(string monitor) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetMonitor() == monitor)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
            break;
        }
    }
    if (!found) throw MyException("Комп'ютер з таким монітором не знайдено");
};

void Manager::SearchByKeyboard(string keyboard) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetKeyboard() == keyboard)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
            break;
        }
    }
    if (!found) throw MyException("Комп'ютер з такою клавіатурою не знайдено");
};

void Manager::SearchBySizeOfRom(int sizeOfRom) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetSizeOfRom() == sizeOfRom)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
            break;
        }
    }
    if (!found) throw MyException("Комп'ютер з таким розміром ROM не знайдено");
};

void Manager::SearchByHasCdRom(bool hasCdRom) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetHasCdRom() == hasCdRom)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
            break;
        }
    }
    if (!found) throw MyException("Комп'ютер з таким параметром CD-ROM не знайдено");
};

void Manager::SearchByHasFloppyDisk(bool hasFloppyDisk) const
{
    bool found = false;
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetHasFloppyDisk() == hasFloppyDisk)
        {
            cout << (*it)->GetComputerFull() << endl;
            found = true;
            break;
        }
    }
    if (!found) throw MyException("Комп'ютер з таким параметром Floppy-Disk не знайдено");
};



void Manager::ChangeToBroken(int inventoryNumber)
{
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetInventoryNumber() == inventoryNumber)
        {
            auto brokenComputer = make_shared<RepairComputer>();

            brokenComputer->SetGpu((*it)->GetGpu());
            brokenComputer->SetCpu((*it)->GetCpu());
            brokenComputer->SetMonitor((*it)->GetMonitor());
            brokenComputer->SetKeyboard((*it)->GetKeyboard());
            brokenComputer->SetSizeOfRom((*it)->GetSizeOfRom());
            brokenComputer->SetHasCdRom((*it)->GetHasCdRom());
            brokenComputer->SetHasFloppyDisk((*it)->GetHasFloppyDisk());
            brokenComputer->SetAuditoriumNumber((*it)->GetAuditoriumNumber());
            brokenComputer->SetInventoryNumber((*it)->GetInventoryNumber());
            string dateOfRepair, describeOfProblem, cause;
            int repairCost;

            cout << "Введіть дату ремонту (YYYY-MM-DD): ";
            cin >> dateOfRepair;
            brokenComputer->SetDate(dateOfRepair);

            cout << "Введіть опис проблеми: ";
            cin.ignore();
            getline(cin, describeOfProblem);
            brokenComputer->SetDescribe(describeOfProblem);

            cout << "Введіть причину проблеми: ";
            cin.ignore();
            getline(cin, cause);
            brokenComputer->SetCause(cause);

            cout << "Введіть вартість ремонту: ";
            cin >> repairCost;
            brokenComputer->RepairCost(repairCost);

            brokenComputer->UpdateRepairStatus();

            *it = brokenComputer;
            SaveToJson("database.json");
            cout << "Статус комп'ютера успішно змінено на несправний!\n";
            return;
        }
    }

    cout << "Комп'ютер з інвентарним номером " << inventoryNumber << " не знайдено.\n";
}


void Manager::ChangeToWorking(int inventoryNumber)
{
    for (auto it = thisComputer.begin(); it != thisComputer.end(); ++it)
    {
        if ((*it)->GetInventoryNumber() == inventoryNumber)
        {
            auto workingComputer = make_shared<WorkedComputer>();
            workingComputer->SetGpu((*it)->GetGpu());
            workingComputer->SetCpu((*it)->GetCpu());
            workingComputer->SetMonitor((*it)->GetMonitor());
            workingComputer->SetKeyboard((*it)->GetKeyboard());
            workingComputer->SetSizeOfRom((*it)->GetSizeOfRom());
            workingComputer->SetHasCdRom((*it)->GetHasCdRom());
            workingComputer->SetHasFloppyDisk((*it)->GetHasFloppyDisk());
            workingComputer->SetAuditoriumNumber((*it)->GetAuditoriumNumber());
            workingComputer->SetInventoryNumber((*it)->GetInventoryNumber());

            int daysWithoutRepair, countUsers;
            cout << "Введіть дні без ремонту: ";
            cin >> daysWithoutRepair;
            workingComputer->SetDays(daysWithoutRepair);

            cout << "Введіть кількість користувачів: ";
            cin >> countUsers;
            workingComputer->SetCountUsers(countUsers);

            string status;
            cout << "Введіть статус (Working/Turned off): ";
            cin >> status;
            if (status == "Working")
                workingComputer->TurnOn();
            else
                workingComputer->TurnOff();

            *it = workingComputer;

            SaveToJson("database.json");
            cout << "Статус комп'ютера змінено на справний!\n";
            return;
        }
    }

    cout << "Комп'ютер з інвентарним номером " << inventoryNumber << " не знайдено.\n";
}


void Manager::SaveToJson(const string& filename) const
{
    json j;
    for (const auto& computer : thisComputer)
    {
        json compJson;
        compJson["inventoryNumber"] = computer->GetInventoryNumber();
        compJson["auditoriumNumber"] = computer->GetAuditoriumNumber();
        compJson["sizeOfRom"] = computer->GetSizeOfRom();
        compJson["hasCdRom"] = computer->GetHasCdRom();
        compJson["hasFloppyDisk"] = computer->GetHasFloppyDisk();
        compJson["keyboard"] = computer->GetKeyboard();
        compJson["monitor"] = computer->GetMonitor();
        compJson["gpu"] = computer->GetGpu();
        compJson["cpu"] = computer->GetCpu();

        if (auto* wc = dynamic_cast<WorkedComputer*>(computer.get()))
        {
            compJson["status"] = "working";
            compJson["statusOfWork"] = wc->IsWorking() ? "Turned on" : "Turned off";
            compJson["daysWithoutRepair"] = wc->GetDays();
            compJson["countUsers"] = wc->GetCountUsers();
            compJson["isWorking"] = wc->IsWorking();
            compJson["serviceCost"] = wc->GetServiceCost();
            compJson["employmentStatus"] = wc->GetEmploymentStatus();

        }
        else if (auto* rc = dynamic_cast<RepairComputer*>(computer.get()))
        {
            compJson["status"] = "broken";
            compJson["repairStatus"] = rc->GetRepairStatus();
            compJson["dateOfRepair"] = rc->GetDate();
            compJson["describeOfProblem"] = rc->GetDescribe();
            compJson["cause"] = rc->GetCause();
            compJson["repairCost"] = rc->GetRepairCost();
            compJson["needNewParts"] = rc->GetNeedNewParts();
        }

        j.push_back(compJson);
    }

    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        throw MyException("Не вдалося відкрити файл для запису: " + filename);
    }
    outFile << setw(4) << j << endl;
    outFile.close();
}

void Manager::LoadFromJson(const string& filename)
{
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        throw MyException("Не вдалося відкрити файл для читання: " + filename);
    }

    json j;
    inFile >> j;
    inFile.close();

    thisComputer.clear();

    for (const auto& compJson : j)
    {
        shared_ptr<Computer> computer;

        if (compJson["status"] == "working")
        {
            auto wc = make_shared<WorkedComputer>();
            wc->SetDays(compJson.value("daysWithoutRepair", 0));
            wc->SetCountUsers(compJson.value("countUsers", 0));
            if (compJson.value("isWorking", false))
                wc->TurnOn();
            else
                wc->TurnOff();
            wc->SetEmploymentStatus(compJson.value("employmentStatus","Freely"));
            computer = wc;
        }
        else if (compJson["status"] == "broken")
        {
            auto rc = make_shared<RepairComputer>();
            rc->SetDate(compJson.value("dateOfRepair", "Unknown"));
            rc->SetDescribe(compJson.value("describeOfProblem", "Unknown"));
            rc->SetCause(compJson.value("cause", "Unknown"));
            rc->SetRepairStatus(compJson.value("repairStatus","waiting diagnostic"));
            rc->RepairCost(compJson.value("repairCost", 0));
            rc->SetNeedParts(compJson.value("needNewParts", true));
            computer = rc;
        }
        else
        {
            throw MyException("Невідомий статус комп'ютера в JSON");
        }

        computer->SetInventoryNumber(compJson.value("inventoryNumber", 0));
        computer->SetAuditoriumNumber(compJson.value("auditoriumNumber", 0));
        computer->SetSizeOfRom(compJson.value("sizeOfRom", 0));
        computer->SetHasCdRom(compJson.value("hasCdRom", false));
        computer->SetHasFloppyDisk(compJson.value("hasFloppyDisk", false));
        computer->SetKeyboard(compJson.value("keyboard", ""));
        computer->SetMonitor(compJson.value("monitor", ""));
        computer->SetGpu(compJson.value("gpu", ""));
        computer->SetCpu(compJson.value("cpu", ""));

        thisComputer.push_back(computer);
    }
}

Manager::~Manager()
{
    cout << "\nДеструктор класу менеджер\n";
};
