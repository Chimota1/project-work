#include "Computer.h"
#include <iostream>
#include "MyException.h"
#include <string>

using namespace std;

Computer::Computer():
	cpu{"unknown"},
	gpu{"unknown"},
	monitor{"unknown"},
	keyboard{"unknown"},
	hasCdRom{false},
	hasFloppyDisk{false},
	sizeOfRom{0},
	inventoryNumber{0},
	auditoriumNumber{0}
{
};

//Конструктор з параметрами
Computer::Computer(
    const string& cpu,
    const string& gpu,
    const string& monitor,
    const string& keyboard,
    bool hasCdRom,
    bool hasFloppyDisk,
    int sizeOfRom,
    int inventoryNumber,
    int auditoriumNumber):
		cpu{cpu},
		gpu{gpu},
		monitor{monitor},
		keyboard{keyboard},
		hasCdRom{hasCdRom},
		hasFloppyDisk{hasFloppyDisk},
		sizeOfRom{sizeOfRom},
		inventoryNumber{inventoryNumber},
		auditoriumNumber{auditoriumNumber}
{
};

void Computer::SetCpu(string cpu) {
	if (cpu.empty()) throw MyException("Рядок CPU порожній");
	this->cpu = cpu;
};

void Computer::SetGpu(string gpu) {
	if (gpu.empty()) throw MyException("Рядок GPU порожній");
	this->gpu = gpu;
};

void Computer::SetMonitor(string monitor) {
	if (monitor.empty()) throw MyException("Рядок монітора порожній");
	this->monitor = monitor;
};

void Computer::SetKeyboard(string keyboard) {
	if (keyboard.empty()) throw MyException("Рядок клавіатури порожній");
	this->keyboard = keyboard;
};

void Computer::SetHasCdRom(bool hasCdRom) {
	if (hasCdRom != 0 && hasCdRom != 1) throw MyException("Значення CD-ROM має бути 0 або 1");
	this->hasCdRom = hasCdRom;
};

void Computer::SetHasFloppyDisk(bool hasFloppyDisk) {
	if (hasFloppyDisk != 0 && hasFloppyDisk != 1) throw MyException("Значення FloppyDisk має бути 0 або 1");
	this->hasFloppyDisk = hasFloppyDisk;
};

void Computer::SetSizeOfRom(int sizeOfRom) {
	if (sizeOfRom <= 0) throw MyException("Обсяг ROM має бути додатнім числом");
	this->sizeOfRom = sizeOfRom;
};

void Computer::SetInventoryNumber(int inventoryNumber) {
	if (inventoryNumber <= 0) throw MyException("Інвентарний номер має бути більшим за 0");
	this->inventoryNumber = inventoryNumber;
};

void Computer::SetAuditoriumNumber(int auditoriumNumber) {
	if (auditoriumNumber <= 0) throw MyException("Номер аудиторії має бути більшим за 0");
	this->auditoriumNumber = auditoriumNumber;
};


string Computer::GetCpu() const
{
	return cpu;
};

string Computer::GetGpu() const
{
	return gpu;
};

string Computer::GetMonitor() const
{
	return monitor;
};

string Computer::GetKeyboard() const
{
	return keyboard;
};

bool Computer::GetHasCdRom() const
{
	return hasCdRom;
};

bool Computer::GetHasFloppyDisk() const
{
	return hasFloppyDisk;
};

int Computer::GetSizeOfRom() const
{
	return sizeOfRom;
};

int Computer::GetInventoryNumber() const
{
	return inventoryNumber;
};

int Computer::GetAuditoriumNumber() const
{
	return auditoriumNumber;
}


//Get-метод
string Computer::GetComputerFull() const
{
	return
	 "Процесор: " + cpu +
	 " Відеокарта: " + gpu +
	 " Монітор: " + monitor +
	 " Клавіатура: " + keyboard +
	 " Наявність CD-ROM: " + (hasCdRom ? "Так" : "Ні") +
	 " Наявність дискети: " + (hasFloppyDisk ? "Так" : "Ні") +
	 " Обсяг ROM: " + to_string(sizeOfRom) +
	 " Інвентарний номер: " + to_string(inventoryNumber) +
	 " Номер аудиторії: " + to_string(auditoriumNumber);
};
//Копіювальний конструктор
Computer::Computer(const Computer &other)
{
	this->cpu = other.cpu;
	this->gpu = other.gpu;
	this->keyboard = other.keyboard;
	this->monitor = other.monitor;
	this->auditoriumNumber = other.auditoriumNumber;
	this->inventoryNumber = other.inventoryNumber;
	this->hasCdRom = other.hasCdRom;
	this->hasFloppyDisk = other.hasFloppyDisk;
	this->sizeOfRom = other.sizeOfRom;
};

//Конструктор переміщення
Computer::Computer(Computer &&other) noexcept
{
	this->cpu = other.cpu;
	this->gpu = other.gpu;
	this->keyboard = other.keyboard;
	this->monitor = other.monitor;
	this->auditoriumNumber = other.auditoriumNumber;
	this->inventoryNumber = other.inventoryNumber;
	this->hasCdRom = other.hasCdRom;
	this->hasFloppyDisk = other.hasFloppyDisk;
	this->sizeOfRom = other.sizeOfRom;
};

void Computer::MoveAuditorium(int number)
{
	if (number <= 0)
		throw MyException("Номер має бути більшим за 0");
	auditoriumNumber = number;
};

void Computer::HasCdRomUpdate(bool hasCdRom)
{
	this->hasCdRom = hasCdRom;
};

void Computer::HasFloppyDiskUpdate(bool hasFloppyDisk)
{
	if (hasFloppyDisk != 0 && hasFloppyDisk != 1) throw MyException("Значення FloppyDisk має бути 0 або 1");
	this->hasFloppyDisk = hasFloppyDisk;
};

//Деструктор
Computer::~Computer()
{
	cout << "\nВикликано деструктор абстрактного класу\n";
};