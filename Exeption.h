#ifndef EXEPTION_H
#define EXEPTION_H

#include <string>
#include <exception>

using namespace std;

class Exeption : public exception{
    public:
    Exeption();
    Exeption(string message);
    Exeption(const Exeption &other);
    Exeption(Exeption &&other) noexcept;
    virtual const char* what() const noexcept override;
    ~Exeption();
    private:
    string m_message;
};



#endif //EXEPTION_H
