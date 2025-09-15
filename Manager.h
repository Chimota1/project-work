#ifndef MANAGER_H
#define MANAGER_H
#include "Computer.h"
#include <string>
#include "WorkedComputer.h"
#include "RepairComputer.h"
#include "Interface.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

using namespace std;

class Manager : public Interface
{
public:
	Manager();
	Manager(vector<shared_ptr<Computer>> thisComputer);
	Manager (const Manager &other);
	Manager (Manager &&other) noexcept;
	void GetManager() const;
	void SetManager(shared_ptr<Computer> thisComputer);

	// Фільтри
	void AuditoriumFilter(int auditoriumNumber) const override;
	void InventoryFilter(int inventoryNumber) const override;
	void SizeOfRomFilter(int sizeOfRom) const override;
	void HasCdRomFilter(bool hasCdRom) const override;
	void HasFloppyDiskFilter(bool hasFloppyDisk) const override;
	void KeyboardFilter(string keyboard) const override;
	void MonitorFilter(string monitor) const override;
	void GpuFilter(string gpu) const override;
	void CpuFilter(string cpu) const override;

	void AddComputer(shared_ptr<Computer> computer);
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