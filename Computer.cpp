#include "StdAfx.h"

#include "CPU.h"
#include "Programm.h"
#include "Computer.h"


size_t Memory::getValue(char place) const {
	place -= 'a';
	assert(0 <= place && place < 26);
	return variables[place];
}

void Memory::setValue(char place, size_t value) {
	place -= 'a';
	assert(0 <= place && place < 26);
	variables[place] = value;
}

Computer::Computer() : acceptMaxPrograms(10) {
	cpu.setComputer(this);
}
Computer::~Computer() {
	unloadProgramms();
}

void Computer::readInputStream() {
	cpu.readInputStream();
	cin >> unitsNumQuantum;
}

bool Computer::loadProgramms(size_t nPrograms) {
	if (nPrograms > acceptMaxPrograms) {
		cout << "#computer accept only " + convertIntToString(acceptMaxPrograms) + " programs" << endl;
		return false;
	}
	programmsBatch.clear();
	while (!readyQueue.empty()) readyQueue.pop();
	while (!blockedQueue.empty()) blockedQueue.pop();
	const size_t num = 100;
	string::value_type line[num+1];
	// read to the end of line
	string strLine;
	cin.getline(line, num);
	strLine = string(line);
	assert(strLine.empty());
	Programm* programm;
	for (size_t i = 1; i <= nPrograms; ++i) {
		programmsBatch.push_back(programm = new Programm(i));
		string error;
		bool res = programm->readInputStream(error);
		if (!res) {
			cout << error << endl;
			return false;
		}
		readyQueue.push(programm);
	}
	return true;
}

void Computer::unloadProgramms() {
	for (size_t i = 0; i < programmsBatch.size(); ++i) {
		delete programmsBatch[i];
	}
	programmsBatch.clear();
	while (!readyQueue.empty()) readyQueue.pop();
	while (!blockedQueue.empty()) blockedQueue.pop();
}

void Computer::calculate() {
	Programm* current;
	while (!readyQueue.empty()) {
		current = readyQueue.front();
		readyQueue.pop();
		current->setStateRunning();
		size_t timeAmount = 0;
		while (timeAmount < unitsNumQuantum) {
			try {
				size_t timeAmountTmp = current->nextInstruction(cpu);
				if (timeAmountTmp == 0) break;
				timeAmount += timeAmountTmp;
			}
			catch (string::value_type*) {
				blockedQueue.push(current);
				break;
			}
		}
		current->setStateReady();
		if (timeAmount > 0) {
			readyQueue.push(current);
		}
		if (cpu.getLockState() == 0) {
			// cause task declare maximum 10 programs in system
			// I use such simple way to place blocked programs like this
			// "any program at the head of the blocked queue is moved to the head of the ready queue"
			while (!readyQueue.empty()) {
				current = readyQueue.front();
				readyQueue.pop();
				blockedQueue.push(current);
			}
			while (!blockedQueue.empty()) {
				current = blockedQueue.front();
				blockedQueue.pop();
				readyQueue.push(current);
			}
		}
	}
}
