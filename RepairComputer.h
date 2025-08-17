#ifndef REPAIRCOMPUTER_H
#define REPAIRCOMPUTER_H

#include "Computer.h"
using namespace std;

class RepairComputer : public Computer
{
public:
	RepairComputer();
    virtual void ShowStatus() override;
	virtual ~RepairComputer();
};

#endif //REPAIRCOMPUTER_H