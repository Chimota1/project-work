#ifndef REPAIRCOMPUTER_H
#define REPAIRCOMPUTER_H

#include "Computer.h"
#include <string>

using namespace std;

class RepairComputer : public Computer
{
public:
	RepairComputer();
	RepairComputer(
		string dateOfRepair,
		string describeOfProblem,
		string cause,
		string repairStatus,
		int repairCost,
		int serviceCost
	);
	RepairComputer(const RepairComputer &other);
	RepairComputer(RepairComputer &&other) noexcept;
	void SetDate(string date);
	void SetDescribe(string describe);
	void SetCause(string cause);
	string GetDate () const;
	string GetDescribe () const;
	string GetCause () const;
	string GetRepairStatus() const;
	int GetRepairCost() const;
	int GetServiceCost() const;
	bool GetNeedNewParts() const;

	void ShowFullInfo();
	void UpdateRepairStatus();
	int RepairCost(int cost);
	void NeedsSpareParts(bool needNewParts);
	void ShowInfoAboutRepair() const;
	void ShowStatus() override;
	void ServiceCost(int serviceCost) override;
	virtual ~RepairComputer();
private:
	string m_dateOfRepair;
	string m_describeOfProblem;
	string m_cause;
	string m_repairStatus;
	int m_repairCost;
	int m_serviceCostRepair;
	bool m_needNewParts;
};

#endif //REPAIRCOMPUTER_H