#ifndef WORKERCOMPUTER_H
#define WORKERCOMPUTER_H

#include "Computer.h"
#include "string"
using namespace std;

class WorkedComputer : public Computer
{
public:
	WorkedComputer();
    void ShowStatus() override;
    void UpdateStatus();
	~WorkedComputer();
private:
    string m_statusOfWork;
};

#endif //WORKERCOMPUTER_H