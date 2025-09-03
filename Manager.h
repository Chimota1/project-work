#ifndef MANAGER_H
#define MANAGER_H
#include "Computer.h"
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
	void const GetManager();
	void SetManager(shared_ptr<Computer> thisComputer);
	void const AuditoriumFilter(int auditoriumNumber);
	void const InventoryFilter(int inventoryNumber);
	void const SizeOfRomFilter(int sizeOfRom);
	void  HasCdRomFilter(bool hasCdRom) const;
	virtual ~Manager();
private:
	vector<shared_ptr<Computer>> m_thisComputer;
};

#endif //MANAGER_H