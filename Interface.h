#ifndef INTERFACE_H
#define INTERFACE_H

#include "Computer.h"
#include <string>
#include "WorkedComputer.h"
#include "RepairComputer.h"
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Interface
{
public:
	virtual void AuditoriumFilter(int auditoriumNumber) const = 0;
	virtual void InventoryFilter(int inventoryNumber) const = 0;
	virtual void SizeOfRomFilter(int sizeOfRom) const = 0;
	virtual void HasCdRomFilter(bool hasCdRom) const = 0;
	virtual void HasFloppyDiskFilter(bool hasFloppyDisk) const = 0;
	virtual void KeyboardFilter(string keyboard) const = 0;
	virtual void MonitorFilter(string monitor) const = 0;
	virtual void GpuFilter(string gpu) const = 0;
	virtual void CpuFilter(string cpu) const = 0;

	virtual void RemoveComputer(int inventoryNumber) = 0;
	virtual void ClearAll() = 0;
	virtual void GetCount() const = 0;

	virtual void CountBrokenComputers() const = 0;
	virtual void CountWorkingComputers() const = 0;

	virtual void SortByInventoryNumber() = 0;
	virtual void SortByAuditoriumNumber() = 0;

	virtual void ChangeToBroken(int inventoryNumber) = 0;
	virtual void ChangeToWorking(int inventoryNumber) = 0;

	virtual ~Interface() {cout << "Interface destructor called" << endl;};

};
#endif //INTERFACE_H