#pragma once
#include <string>

namespace ERR{
    inline const std::string FILE_OPEN_FAIL = "Не вдається відкрити файл users.txt.";
    inline const std::string INVALID_INPUT = "Невірне введення.";
    inline const std::string INVALID_TYPE = "Невірний тип введення. Очікувалось число.";

    inline const std::string ADMIN_LOGIN_FAIL = "Невірні дані для входу або ви не адміністратор.";
    inline const std::string USER_NOT_FOUND = "Користувача з таким ID не існує.";

    inline const std::string EMPTY_COMPUTER_LIST = "Список комп'ютерів пустий.";
    inline const std::string COMPUTER_NOT_FOUND = "Комп'ютер з таким інвентарним номером не знайдено.";
    inline const std::string FILTER_NOT_FOUND = "Не знайдено комп'ютерів, що відповідають критеріям.";

    inline const std::string JSON_READ_FAIL = "Помилка читання JSON-файлу.";
    inline const std::string JSON_WRITE_FAIL = "Помилка запису JSON-файлу.";
}
