#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "IUser.h"
#include "Manager.h"

using namespace std;

class Admin : public IUser
{
    public:
    Admin();
    Admin(int id, const string& username, const string& password, const string& status);
    Admin(const Admin& other);
    Admin(Admin&& other) noexcept;
    void Login() override;
    void MainMenu(Manager& manager) override;
    int GetID() const override;
    void HelpMenu() const override;
    /**
     * @brief меню з фільтрації комп'ютерів
     * @param manager 
     */
    void FilterMenu(Manager& manager);

    /**
     * @brief меню з сортування комп'ютерів
     * @param manager 
     */
    void SortMenu(Manager& manager);

    /**
     * @brief меню з пошуку комп'ютерів заданими параметрами
     * @param manager 
     */
    void SearchMenu(Manager& manager);

    /**
     * @brief меню для роботи з робочими комп'ютерами
     * @param manager 
     */
    void WorkedMenu(Manager& manager);

    /**
     * @brief меню для роботи з несправними комп'ютерами
     * @param manager 
     */
    void RepairMenu(Manager& manager);

    /**
     * @brief меню для зміни атрибутів комп'ютерів
     * @param manager 
     */
    void ChangesMenu(Manager& manager);
    string GetStatus() const override;

    virtual ~Admin();


    private:
        int id;
        string username;
        string password;
        string status;
    };

#endif //ADMIN_H
