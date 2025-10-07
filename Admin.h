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
    void FilterMenu(Manager& manager);
    void SortMenu(Manager& manager);
    string GetStatus() const override;
    virtual ~Admin();


    private:
        int m_id;
        string m_username;
        string m_password;
        string m_status;
    };

#endif //ADMIN_H
