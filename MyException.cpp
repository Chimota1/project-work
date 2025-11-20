//
// Created by Користувач on 05.09.2025.
//

#include "MyException.h"
#include <string>
#include <exception>
#include <iostream>

using namespace std;

MyException::MyException():
    message{"Невідома помилка"}
{
};

MyException::MyException(string message):
    message{message}
{
};

MyException::MyException(const MyException &other)
{
    this->message = other.message;
};

MyException::MyException(MyException &&other) noexcept
{
    this->message = other.message;
};

const char* MyException::what() const noexcept
{
    return message.c_str();
};

MyException::~MyException()
{
    cout << "\nДеструктор класу винятків\n";
};