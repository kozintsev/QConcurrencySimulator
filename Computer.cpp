#include "StdAfx.h"
#include "filestructure.h"

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
    QMessageBox::information(this, "Output", "Computer constr", QMessageBox::Ok, QMessageBox::NoButton);
    cpu.setComputer(this);
}
Computer::~Computer() {
	unloadProgramms();
}

void Computer::readInputStream(FileStructure &fs) {
    cpu.readInputStream(fs);
    unitsNumQuantum = fs.unitsNumQuantum;
    _fs = &fs;
    QMessageBox::information(this, "Output", "readInputStream", QMessageBox::Ok, QMessageBox::NoButton);
}

bool Computer::loadProgramms(size_t nPrograms, string strLine, string& out) {
    //QString str;
    //str = QString::fromStdString(error);
	if (nPrograms > acceptMaxPrograms) {
        out =  "#computer accept only " + convertIntToString(acceptMaxPrograms) + " programs";
        //str = "#computer accept only " + QString::fromStdString(convertIntToString(acceptMaxPrograms)) + " programs";
        //gQStrLisr << str;
		return false;
	}
	programmsBatch.clear();
	while (!readyQueue.empty()) readyQueue.pop();
	while (!blockedQueue.empty()) blockedQueue.pop();
	const size_t num = 100;
    //string::value_type line[num+1];
	// read to the end of line
    //string strLine;
    //int count = _fs->fileRead.count();
    //QMessageBox::information(this, "Output", QString::number(count), QMessageBox::Ok, QMessageBox::NoButton);
    //QString str1 = _fs->fileRead.at(count-1);
    //strLine = str1.toStdString();
    //cin.getline(line, num);
    //strLine = string(line);
    //assert(strLine.empty()); // предупреждение если strLine пустая
	Programm* programm;
    QMessageBox::information(this, "Output", "loadProgramms", QMessageBox::Ok, QMessageBox::NoButton);
	for (size_t i = 1; i <= nPrograms; ++i) {
		programmsBatch.push_back(programm = new Programm(i));
		string error;
        bool res = programm->readInputStream(error, strLine);
		if (!res) {
            //str = QString::fromStdString(error);
            //sendSignal(str);
            //cout << error << endl;
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

void Computer::calculate(string& out) {
	Programm* current;
	while (!readyQueue.empty()) {
		current = readyQueue.front();
		readyQueue.pop();
		current->setStateRunning();
		size_t timeAmount = 0;
		while (timeAmount < unitsNumQuantum) {
			try {
                size_t timeAmountTmp = current->nextInstruction(cpu, out);
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
