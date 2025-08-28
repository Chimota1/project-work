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
	virtual ~Manager();
private:
	vector<shared_ptr<Computer>> thisComputer;
};

#endif //MANAGER_H