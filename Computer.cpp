#include "Computer.h"
#include <iostream>
#include "Exeption.h"
#include <string>

using namespace std;

Computer::Computer():
	m_cpu{"unknown"},
	m_gpu{"unknown"},
	m_monitor{"unknown"},
	m_keyboard{"unknown"},
	m_hasCdRom{false},
	m_hasFloppyDisk{false},
	m_sizeOfRom{0},
	m_inventoryNumber{0},
	m_auditoriumNumber{0}
{
};

//Конструктор з параметрами
Computer::Computer(
    string cpu,
    string gpu,
    string monitor,
    string keyboard,
    bool hasCdRom,
    bool hasFloppyDisk,
    int sizeOfRom,
    int inventoryNumber,
    int auditoriumNumber):
		m_cpu{cpu},
		m_gpu{gpu},
		m_monitor{monitor},
		m_keyboard{keyboard},
		m_hasCdRom{hasCdRom},
		m_hasFloppyDisk{hasFloppyDisk},
		m_sizeOfRom{sizeOfRom},
		m_inventoryNumber{inventoryNumber},
		m_auditoriumNumber{auditoriumNumber}
{
};

void Computer::SetCpu(string cpu) {
	if (cpu.empty()) throw Exeption("Рядок CPU порожній");
	m_cpu = cpu;
};

void Computer::SetGpu(string gpu) {
	if (gpu.empty()) throw Exeption("Рядок GPU порожній");
	m_gpu = gpu;
};

void Computer::SetMonitor(string monitor) {
	if (monitor.empty()) throw Exeption("Рядок монітора порожній");
	m_monitor = monitor;
};

void Computer::SetKeyboard(string keyboard) {
	if (keyboard.empty()) throw Exeption("Рядок клавіатури порожній");
	m_keyboard = keyboard;
};

void Computer::SetHasCdRom(bool hasCdRom) {
	if (hasCdRom != 0 && hasCdRom != 1) throw Exeption("Значення CD-ROM має бути 0 або 1");
	m_hasCdRom = hasCdRom;
};

void Computer::SetHasFloppyDisk(bool hasFloppyDisk) {
	if (hasFloppyDisk != 0 && hasFloppyDisk != 1) throw Exeption("Значення FloppyDisk має бути 0 або 1");
	m_hasFloppyDisk = hasFloppyDisk;
};

void Computer::SetSizeOfRom(int sizeOfRom) {
	if (sizeOfRom <= 0) throw Exeption("Обсяг ROM має бути додатнім числом");
	m_sizeOfRom = sizeOfRom;
};

void Computer::SetInventoryNumber(int inventoryNumber) {
	if (inventoryNumber <= 0) throw Exeption("Інвентарний номер має бути більшим за 0");
	m_inventoryNumber = inventoryNumber;
};

void Computer::SetAuditoriumNumber(int auditoriumNumber) {
	if (auditoriumNumber <= 0) throw Exeption("Номер аудиторії має бути більшим за 0");
	m_auditoriumNumber = auditoriumNumber;
};


string Computer::GetCpu() const
{
	return m_cpu;
};

string Computer::GetGpu() const
{
	return m_gpu;
};

string Computer::GetMonitor() const
{
	return m_monitor;
};

string Computer::GetKeyboard() const
{
	return m_keyboard;
};

bool Computer::GetHasCdRom() const
{
	return m_hasCdRom;
};

bool Computer::GetHasFloppyDisk() const
{
	return m_hasFloppyDisk;
};

int Computer::GetSizeOfRom() const
{
	return m_sizeOfRom;
};

int Computer::GetInventoryNumber() const
{
	return m_inventoryNumber;
};

int Computer::GetAuditoriumNumber() const
{
	return m_auditoriumNumber;
}


//Get-метод
string Computer::GetComputerFull() const
{
	return
	 "Процесор: " + m_cpu +
	 " Відеокарта: " + m_gpu +
	 " Монітор: " + m_monitor +
	 " Клавіатура: " + m_keyboard +
	 " Наявність CD-ROM: " + (m_hasCdRom ? "Так" : "Ні") +
	 " Наявність дискети: " + (m_hasFloppyDisk ? "Так" : "Ні") +
	 " Обсяг ROM: " + to_string(m_sizeOfRom) +
	 " Інвентарний номер: " + to_string(m_inventoryNumber) +
	 " Номер аудиторії: " + to_string(m_auditoriumNumber);
};
//Копіювальний конструктор
Computer::Computer(const Computer &other)
{
	this->m_cpu = other.m_cpu;
	this->m_gpu = other.m_gpu;
	this->m_keyboard = other.m_keyboard;
	this->m_monitor = other.m_monitor;
	this->m_auditoriumNumber = other.m_auditoriumNumber;
	this->m_inventoryNumber = other.m_inventoryNumber;
	this->m_hasCdRom = other.m_hasCdRom;
	this->m_hasFloppyDisk = other.m_hasFloppyDisk;
	this->m_sizeOfRom = other.m_sizeOfRom;
};

//Конструктор переміщення
Computer::Computer(Computer &&other) noexcept
{
	this->m_cpu = other.m_cpu;
	this->m_gpu = other.m_gpu;
	this->m_keyboard = other.m_keyboard;
	this->m_monitor = other.m_monitor;
	this->m_auditoriumNumber = other.m_auditoriumNumber;
	this->m_inventoryNumber = other.m_inventoryNumber;
	this->m_hasCdRom = other.m_hasCdRom;
	this->m_hasFloppyDisk = other.m_hasFloppyDisk;
	this->m_sizeOfRom = other.m_sizeOfRom;
};

void Computer::MoveAuditorium(int number)
{
	if (number <= 0)
		throw Exeption("Номер має бути більшим за 0");
	m_auditoriumNumber = number;
};

void Computer::HasCdRomUpdate(bool hasCdRom)
{
	m_hasCdRom = hasCdRom;
};

void Computer::HasFloppyDisk(bool hasFloppyDisk)
{
	if (hasFloppyDisk != 0 && hasFloppyDisk != 1) throw Exeption("Значення FloppyDisk має бути 0 або 1");
	m_hasFloppyDisk = hasFloppyDisk;
};

//Деструктор
Computer::~Computer()
{
	cout << "Викликано деструктор абстрактного класу" << endl;
};