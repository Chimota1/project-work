#ifndef WORKERCOMPUTER_H
#define WORKERCOMPUTER_H

#include "Computer.h"
#include "string"
using namespace std;

/**
 * @brief клас нащадок
 * @details містить інформацію про робочі пк
 */
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
    // методи з перевизначенням
	void ShowStatus() override;
	void ServiceCost(int serviceCost) override;
    // сеттери
    void SetDays(int days);
    void SetCountUsers(int users);
	void SetEmploymentStatus(const string& status);
    // геттери
    int GetDays() const;
	int GetCountUsers() const;
	int GetServiceCost() const;
	string GetEmploymentStatus() const;

    /**
     * @brief змінює статус зайнятості комп'ютера
     */
    void UpdateStatus();

    /**
     * @brief вмикає комп'ютер
     */
	void TurnOn();

    /**
     * @brief вимикає комп'ютер
     */
	void TurnOff();

    /**
     * @brief перевіряє чи комп'ютер працює
     * @return true 
     * @return false 
     */
	bool IsWorking();
	
    /**
     * @brief показує чи потрібне технічне обслуговування
     */
	void NeedsMaintenance() const;
	virtual ~WorkedComputer();
private:
    string m_statusOfWork;
	string m_employmentStatus;
    int m_serviceCostWorked;
    int m_daysWithoutRepair;
    int m_countUsers;
};

#endif //WORKERCOMPUTER_H