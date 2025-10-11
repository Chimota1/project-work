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

class Manager
{
public:
	Manager();
	Manager(vector<shared_ptr<Computer>> thisComputer);
	Manager (const Manager &other);
	Manager (Manager &&other) noexcept;
	vector<shared_ptr<Computer>>& GetManager();
	void SetManager(shared_ptr<Computer> thisComputer);

	void ViewAllUsers() const;
	void AddUser();
    void RemoveUser();
	int GetLastID() const;

	// Фільтри
	void AuditoriumFilter(int auditoriumNumber) const;
	void InventoryFilter(int inventoryNumber) const;
	void SizeOfRomFilter(int sizeOfRom) const;
	void HasCdRomFilter(bool hasCdRom) const;
	void HasFloppyDiskFilter(bool hasFloppyDisk) const;
	void KeyboardFilter(string keyboard) const;
	void MonitorFilter(string monitor) const;
	void GpuFilter(string gpu) const;
	void CpuFilter(string cpu) const;

	int GenerateID(int& id);
	void ViewAllComputer() const;
	void InitComputer();
	void RemoveComputer(int inventoryNumber);
	void ClearAll();
	void GetCount() const;

	void CountBrokenComputers() const;
    void CountWorkingComputers() const;

	void SortByInventoryNumber();
	void SortByAuditoriumNumber();


	void ChangeToBroken(int inventoryNumber);
	void ChangeToWorking(int inventoryNumber);

	void SaveToJson(const string& filename) const;
	void LoadFromJson(const string& filename);
	virtual ~Manager();
private:
	vector<shared_ptr<Computer>> m_thisComputer;
	int m_lastID;
};

#endif //MANAGER_H