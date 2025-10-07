#ifndef DEFAULTUSER_H
#define DEFAULTUSER_H

#include "IUser.h"


class DefaultUser : public IUser
{
public:
    DefaultUser();
    DefaultUser(int id, const string& username);
    DefaultUser(const DefaultUser& other);
    DefaultUser(DefaultUser&& other) noexcept;
    void Login() override;
    void MainMenu(Manager& manager) override;
    int GetID() const override;
    void FilterMenu(Manager& manager);
    void SortMenu(Manager& manager);
    virtual ~DefaultUser();
private:
    int m_id;
    string m_username;
};



#endif //DEFAULTUSER_H
