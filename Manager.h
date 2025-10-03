#ifndef MANAGER_H
#define MANAGER_H
#include "Computer.h"
#include <string>
#include "WorkedComputer.h"
#include "RepairComputer.h"
#include <iostream>
#include <algorithm>
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
	void GetManager() const;
	void SetManager(shared_ptr<Computer> thisComputer);

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

	void RemoveComputer(int inventoryNumber);
	void ClearAll();
	void GetCount() const;

	void CountBrokenComputers() const;
    void CountWorkingComputers() const;

	void SortByInventoryNumber();
	void SortByAuditoriumNumber();

	void ChangeToBroken(int inventoryNumber);
	void ChangeToWorking(int inventoryNumber);
	virtual ~Manager();
private:
	vector<shared_ptr<Computer>> m_thisComputer;
};

#endif //MANAGER_H