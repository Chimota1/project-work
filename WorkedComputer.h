#ifndef WORKERCOMPUTER_H
#define WORKERCOMPUTER_H

#include "Computer.h"
#include "string"
using namespace std;

class WorkedComputer : public Computer
{
public:
	WorkedComputer();
    WorkedComputer(
    string statusOfWork,
    int serviceCostWorked,
    int daysWithoutRepair,
    int countUsers);
    WorkedComputer(const WorkedComputer &other);
	WorkedComputer(WorkedComputer &&other) noexcept;
    virtual void ShowStatus() override;
    virtual int ServiceCost() override;
    void SetDays(int days);
    void SetCountUsers(int users);
    int GetDays();
	int GetCountUsers();
    void UpdateStatus();
	void TurnOn();
	void TurnOff();
	bool IsWorking();
	virtual ~WorkedComputer();
private:
    string m_statusOfWork;
    int m_serviceCostWorked;
    int m_daysWithoutRepair;
    int m_countUsers;
};

#endif //WORKERCOMPUTER_H