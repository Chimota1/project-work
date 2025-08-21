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
		int repairCost
	);
	RepairComputer(const RepairComputer &other);
	RepairComputer(RepairComputer &&other) noexcept;
	void SetDate(string date);
	void SetDescribe(string describe);
	void SetCause(string cause);
	string GetDate ();
	string GetDescribe ();
	string GetCause ();
	void ShowFullInfo();
	void UpdateRepairStatus();
	int RepairCost(int cost);
	bool NeedsSpareParts();
	void ShowStatus() override;
	virtual ~RepairComputer();
private:
	string m_dateOfRepair;
	string m_describeOfProblem;
	string m_cause;
	string m_repairStatus;
	int m_repairCost;
	bool m_needNewParts;
};

#endif //REPAIRCOMPUTER_H