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
    Computer(const Computer &other); //Копіювальний конструктор
    Computer(Computer &&other) noexcept; //Конструктор переміщення
	void SetCpu(string cpu);
	void SetGpu(string gpu);
	void SetMonitor(string monitor);
	void SetKeyboard(string keyboard);
	void SetHasCdRom(bool hasCdRom);
	void SetHasFloppyDisk(bool hasFloppyDisk);
	void SetSizeOfRom(int sizeOfRom);
	void SetInventoryNumber(int inventoryNumber);
	void SetAuditoriumNumber(int auditoriumNumber);
	string GetGpu() const;
	string GetCpu() const;
	string GetMonitor() const;
	string GetKeyboard() const;
	bool GetHasCdRom() const;
	bool GetHasFloppyDisk() const;
	int GetSizeOfRom() const;
	int GetInventoryNumber() const;
	int GetAuditoriumNumber() const;
	string GetComputerFull() const;
	virtual void ShowStatus() = 0; // Метод демонстрування стану
	virtual int ServiceCost() = 0; // Метод демонстрування вартості осблуговування
    void MoveAuditorium(int number); // Метод який змінює номер аудиторії де знаходиться ПК
	void HasCdRomUpdate(bool hasCdRom); // Метод який оновлює значення чи є Cd-ROM
	void HasFloppyDisk(bool hasFloppyDisk); // Метод який оновлює значення чи є Floppy Disk
	virtual ~Computer(); //Деструктор

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