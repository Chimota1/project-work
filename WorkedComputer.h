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
    string employmentStatus,
    int serviceCostWorked,
    int daysWithoutRepair,
    int countUsers);
    WorkedComputer(const WorkedComputer &other);
	WorkedComputer(WorkedComputer &&other) noexcept;
	void ShowStatus() override;
	void ServiceCost(int serviceCost) override;
    void SetDays(int days);
    void SetCountUsers(int users);
	void SetEmploymentStatus(const string& status);
    int GetDays() const;
	int GetCountUsers() const;
	int GetServiceCost() const;
	string GetEmploymentStatus() const;
    void UpdateStatus();
	void TurnOn();
	void TurnOff();
	bool IsWorking();
	virtual ~WorkedComputer();
private:
    string m_statusOfWork;
	string m_employmentStatus;
    int m_serviceCostWorked;
    int m_daysWithoutRepair;
    int m_countUsers;
};

#endif //WORKERCOMPUTER_H