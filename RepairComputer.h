#ifndef REPAIRCOMPUTER_H
#define REPAIRCOMPUTER_H

#include "Computer.h"
#include <string>

using namespace std;

class RepairComputer : public Computer
{
public:
	RepairComputer();
	void ShowStatus() override;
	virtual ~RepairComputer();
private:
	string m_dateOfRepair;
	string m_describeOfProblem;
	string m_cause;
};

#endif //REPAIRCOMPUTER_H