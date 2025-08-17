#ifndef REPAIRCOMPUTER_H
#define REPAIRCOMPUTER_H

#include "Computer.h"
using namespace std;

class RepairComputer : public Computer
{
public:
	RepairComputer();
	void ShowStatus() override;

private:
	string dateOfRepair;
};

#endif //REPAIRCOMPUTER_H