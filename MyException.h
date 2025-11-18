#ifndef MYEXCEPTION_H
#define MYECXEPTION_H

#include <string>
#include <exception>

using namespace std;

/**
 * @brief Клас для перезавантаженння виводу винятків
 * 
 */
class MyException : public exception{
    public:
    MyException();
    MyException(string message);
    MyException(const MyException &other);
    MyException(MyException &&other) noexcept;

    /**
     * @brief перезавантаження виводу помилки 
     * @details Перевантажує метод what() базового класу exception, 
     * повертаючи повідомлення про помилку, збережене в цьому об'єкті винятку.
     * @return const char* 
     */
    const char* what() const noexcept override;
    virtual ~MyException();
    private:
    string message;
};



#endif //MYEXCEPTION_H
