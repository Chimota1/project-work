#ifndef IUSER_H
#define IUSER_H
#include <string>
#include <iostream>
#include "Manager.h"

using namespace std;

class IUser
{
     public:
     virtual void Login() = 0;
     virtual void MainMenu(Manager& manager) = 0;
     virtual int GetID() const = 0;
     virtual string GetStatus() const = 0;
     virtual void HelpMenu() const = 0;
     virtual ~IUser()
     {
           cout << "Викликано IUser деструктор" << endl;
     };
};

#endif //IUSER_H
