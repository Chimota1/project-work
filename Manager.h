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
	~Manager();
private:
shared_ptr<vector<Computer>> thisComputer;
};

#endif //MANAGER_H