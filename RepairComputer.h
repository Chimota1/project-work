#ifndef REPAIRCOMPUTER_H
#define REPAIRCOMPUTER_H

#include "Computer.h"
#include <string>

using namespace std;

/**
 * @brief клас нащадок
 * @details містить іфнормацію про несправних пк	
 * 
 */
class RepairComputer : public Computer
{
public:
	RepairComputer();
	RepairComputer(
		const string& dateOfRepair,
		const string& describeOfProblem,
		const string& cause,
		const string& repairStatus,
		int repairCost,
		int serviceCost
	);
	RepairComputer(const RepairComputer &other);
	RepairComputer(RepairComputer &&other) noexcept;
	void SetDate(string date);
	void SetDescribe(string describe);
	void SetCause(string cause);
	void SetNeedParts(bool needNewParts);
	void SetRepairStatus (string repairStatus);
	string GetDate () const;
	string GetDescribe () const;
	string GetCause () const;
	string GetRepairStatus() const;
	int GetRepairCost() const;
	int GetServiceCost() const;
	bool GetNeedNewParts() const;

	/**
	 * @brief Виводить всю повну інформацію про несправний пк
	 */
	void ShowFullInfo();

	/**
	 * @brief змінює статус лагодження пк
	 * @details є 3 статуса: 1. в діагностиці, 2. в процессі лагодження, 3. готова до відправки назад
	 */
	void UpdateRepairStatus();
	/**
	 * @brief показує вартість ремонту
	 * @param cost 
	 * @return int 
	 */
	int RepairCost(int cost);
	void NeedsSpareParts(bool needNewParts);
	void ShowInfoAboutRepair() const;
	void ShowStatus() override;
	void ServiceCost(int serviceCost) override;
	virtual ~RepairComputer();
private:
	string dateOfRepair;
	string describeOfProblem;
	string cause;
	string repairStatus;
	int repairCost;
	int serviceCostRepair;
	bool needNewParts;
};

#endif //REPAIRCOMPUTER_H