#ifndef IUSER_H
#define IUSER_H
#include <string>
#include <iostream>
#include "Manager.h"

using namespace std;

/**
 * @brief Клас інтерфейс для користувачів системи
 */
class IUser
{
     public:
     virtual void Login() = 0;
     virtual void MainMenu(Manager& manager) = 0;
     virtual int GetID() const = 0;
     /**
      * @brief повертає статус користувача (адмін чи звичайний користувач)
      * @return string 
      */
     virtual string GetStatus() const = 0;
     /**
      * @brief Меню з довідкою по використанню системи
      */
     virtual void HelpMenu() const = 0;
     virtual ~IUser()
     {
           cout << "Викликано IUser деструктор" << endl;
     };
};

#endif //IUSER_H
