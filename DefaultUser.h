#ifndef DEFAULTUSER_H
#define DEFAULTUSER_H

#include "IUser.h"

using namespace std;

class DefaultUser : public IUser
{
public:
    DefaultUser();
    DefaultUser(int id, const string& username, const string& password, const string status);
    DefaultUser(const DefaultUser& other);
    DefaultUser(DefaultUser&& other) noexcept;
    void Login() override;
    void MainMenu(Manager& manager) override;
    int GetID() const override;
    string GetStatus() const override;
    void HelpMenu() const override;
    void FilterMenu(Manager& manager);
    void SortMenu(Manager& manager);
    void SearchMenu(Manager& manager);
    virtual ~DefaultUser();
private:
    int id;
    string username;
    string password;
    string status;
};



#endif //DEFAULTUSER_H