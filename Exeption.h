#ifndef EXEPTION_H
#define EXEPTION_H

#include <string>
#include <exception>

using namespace std;

class Exeption {
    public:
    Exeption();
    Exeption(string message);
    Exeption(const Exeption &other);
    Exeption(Exeption &&other) noexcept;

    private:
    string m_message;
};



#endif //EXEPTION_H
