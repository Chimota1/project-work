#ifndef MANAGER_H
#define MANAGER_H
#include "Computer.h"
#include <string>
#include "WorkedComputer.h"
#include "RepairComputer.h"
#include <iostream>
#include <algorithm>
#include "json.hpp"
#include <vector>
#include <memory>

using namespace std;

/**
 * @brief Клас-менеджер для керування колекцією об'єктів Computer.
 * 
 */
class Manager
{
public:
	Manager();
	Manager(vector<shared_ptr<Computer>> thisComputer);
	Manager (const Manager &other);
	Manager (Manager &&other) noexcept;
	vector<shared_ptr<Computer>>& GetManager();
	void SetManager(shared_ptr<Computer> thisComputer);

	// методи для роботи з користувачами
	void ViewAllUsers() const;
	void AddUser();
    void RemoveUser();

	/**
	 * @brief Дає ID останнього користувача
	 * 
	 * @return int 
	 */
	int GetLastID() const;

	// Фільтри по комплектуючими
	void AuditoriumFilter(int auditoriumNumber) const;
	void InventoryFilter(int inventoryNumber) const;
	void SizeOfRomFilter(int sizeOfRom) const;
	void HasCdRomFilter(bool hasCdRom) const;
	void HasFloppyDiskFilter(bool hasFloppyDisk) const;
	void KeyboardFilter(string keyboard) const;
	void MonitorFilter(string monitor) const;
	void GpuFilter(string gpu) const;
	void CpuFilter(string cpu) const;

	/**
	 * @brief генерує ID користувача
	 * 
	 * @param id 
	 * @return int 
	 */
	int GenerateID(int& id);

	// методи для роботи з комп'ютерами
	void ViewAllComputer() const;
	void InitComputer();
	void RemoveComputer(int inventoryNumber);

	/**
	 * @brief очищує весь JSON
	 * 
	 */
	void ClearAll();

	/**
	 * @brief дає кількість комп'ютерів
	 * 
	 */
	void GetCount() const;

	/**
	 * @brief виводить кількість несправних комп'ютерів
	 * 
	 */
	void CountBrokenComputers() const;

	/**
	 * @brief виводить кількість робочих комп'ютерів
	 * 
	 */
    void CountWorkingComputers() const;

	//Сортування
	void SortByInventoryNumber();
	void SortByAuditoriumNumber();

	void SearchByInventoryNumber(int inventoryNumber) const;
	void SearchByAuditoriumNumber(int auditoriumNumber) const;
	void SearchByCpu(string cpu) const;
	void SearchByGpu(string gpu) const;
	void SearchByMonitor(string monitor) const;
	void SearchByKeyboard(string keyboard) const;
	void SearchBySizeOfRom(int sizeOfRom) const;
	void SearchByHasCdRom(bool hasCdRom) const;
	void SearchByHasFloppyDisk(bool hasFloppyDisk) const;

	// Зміна статусу
	void ChangeToBroken(int inventoryNumber);
	void ChangeToWorking(int inventoryNumber);

	/**
	 * @brief зберігає всі данні в JSON
	 * 
	 * @param filename 
	 */
	void SaveToJson(const string& filename) const;

	/**
	 * @brief завантажує данні з JSON
	 * 
	 * @param filename 
	 */
	void LoadFromJson(const string& filename);
	virtual ~Manager();
private:
	vector<shared_ptr<Computer>> m_thisComputer;
	int m_lastID;
};

#endif //MANAGER_H