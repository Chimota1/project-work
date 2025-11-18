#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

using namespace std;

/**
 * @brief абстрактний клас
 * @details містить інформацію про комп'ютер
 */
class Computer
{
public:
	Computer();
    Computer(
    	const string& cpu,
        const string& gpu,
        const string& monitor,
        const string& keyboard,
        bool hasCdRom,
        bool hasFloppyDisk,
        int sizeOfRom,
        int inventoryNumber,
        int auditoriumNumber);
    Computer(const Computer &other);
    Computer(Computer &&other) noexcept;
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

	/**
	 * @brief чисто віртуальна функція, яка виводить інформацію про статус ПК
	 */
	virtual void ShowStatus() = 0;
	
	/**
	 * @brief чисто віртуальна функція, яка виводить вартість обслуговування пк
	 * @param serviceCost 
	 */

	virtual void ServiceCost(int serviceCost) = 0;

	/**
	 * @brief змінює номер авдиторії пк
	 * @param number 
	 */
    void MoveAuditorium(int number);

	/**
	 * @brief оновлює інформацію про наявність CD-ROM
	 * @param hasCdRom 
	 */
	void HasCdRomUpdate(bool hasCdRom);

	/**
	 * @brief оновлює інформацію про наявність Floppy-Disk
	 * @param hasFloppyDisk 
	 */
	void HasFloppyDiskUpdate(bool hasFloppyDisk);

	virtual ~Computer();

private:
	string cpu;
	string gpu;
	string monitor;
	string keyboard;
    bool hasCdRom;
    bool hasFloppyDisk;
	int sizeOfRom;
    int inventoryNumber;
    int auditoriumNumber;
};
#endif // COMPUTER_H