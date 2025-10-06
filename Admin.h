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
    Admin(int id, const string& username, const string& password);
    Admin(const Admin& other);
    Admin(Admin&& other) noexcept;
    void Login() override;
    void MainMenu(Manager& manager) override;
    void SetID();
    int GetID() const override;
    void FilterMenu(Manager& manager);
    void SortMenu(Manager& manager);
    virtual ~Admin();


    private:
        int m_id;
        string m_username;
        string m_password;
    };

#endif //ADMIN_H
