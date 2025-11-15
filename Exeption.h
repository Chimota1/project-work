#ifndef EXEPTION_H
#define EXEPTION_H

#include <string>
#include <exception>

using namespace std;

/**
 * @brief Клас для перезавантаженння виводу винятків
 * 
 */
class Exeption : public exception{
    public:
    Exeption();
    Exeption(string message);
    Exeption(const Exeption &other);
    Exeption(Exeption &&other) noexcept;

    /**
     * @brief перезавантаження виводу помилки 
     * @details Перевантажує метод what() базового класу std::exception, 
     * повертаючи повідомлення про помилку, збережене в цьому об'єкті винятку.
     * @return const char* 
     */
    const char* what() const noexcept override;
    virtual ~Exeption();
    private:
    string m_message;
};



#endif //EXEPTION_H
