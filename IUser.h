#ifndef IUSER_H
#define IUSER_H
#include <string>
#include <iostream>

using namespace std;

class IUser
{
     public:
     virtual void MainMenu() = 0;
     virtual int GetID() const = 0;
     virtual ~IUser()
     {
           cout << "IUser destructor called" << endl;
     };
};

#endif //IUSER_H
