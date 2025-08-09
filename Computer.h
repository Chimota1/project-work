#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

using namespace std;

class Computer
{
public:
	Computer();//Конструктор за замовчуванням
    Computer(
    	string cpu,
        string gpu,
        string monitor,
        string keyboard,
        bool hasCdRom,
        bool hasFloppyDisk,
        int sizeOfRom,
        int inventoryNumber,
        int auditoriumNumber); //Конструктор з параметрами
    void SetComputer(
        string cpu,
        string gpu,
        string monitor,
        string keyboard,
        bool hasCdRom,
        bool hasFloppyDisk,
        int sizeOfRom,
        int inventoryNumber,
        int auditoriumNumber); //Set-метод
    string GetComputer(); //Get-метод
    Computer(const Computer &other); //Копіювальний конструктор
    Computer(const Computer &&other); //Конструктор переміщення
	virtual void ShowStatus() = 0; // Метод демонстрування стану
	virtual void ServiceCost()= 0; // Метод демонстрування вартості осблуговування
	virtual void ShowCount() = 0; // Метод демонстрування кількості
    virtual void ShowOwner() = 0;// Метод який показує власника
	virtual void ShowYear() = 0;// Метод який показує якого року комп'ютер
	~Computer(); //Деструктор

private:
	string m_cpu;
	string m_gpu;
	string m_monitor;
	string m_keyboard;
    bool m_hasCdRom;
    bool m_hasFloppyDisk;
	int m_sizeOfRom;
    int m_inventoryNumber;
    int m_auditoriumNumber;
};
#endif // COMPUTER_H