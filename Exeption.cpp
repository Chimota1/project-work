//
// Created by Користувач on 05.09.2025.
//

#include "Exeption.h"
#include <string>
#include <exception>
#include <iostream>

using namespace std;

Exeption::Exeption():
    m_message{"Unknown exeption"}
{
};

Exeption::Exeption(string message):
    m_message{message}
{
};

Exeption::Exeption(const Exeption &other)
{
    this->m_message = other.m_message;
};

Exeption::Exeption(Exeption &&other) noexcept
{
    this->m_message = other.m_message;
};

Exeption::~Exeption()
{
    cout << "Destructor of Exception class" <<endl;
};