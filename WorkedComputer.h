#ifndef WORKERCOMPUTER_H
#define WORKERCOMPUTER_H

#include "Computer.h"
#include "string"
using namespace std;

class WorkedComputer : public Computer
{
public:
	WorkedComputer();
    virtual void ShowStatus() override;
    virtual int ServiceCost() override;
    void UpdateStatus();
	virtual ~WorkedComputer();
private:
    string m_statusOfWork;
    int m_serviceCostWorked;
    int m_daysWithoutRepair;
};

#endif //WORKERCOMPUTER_H