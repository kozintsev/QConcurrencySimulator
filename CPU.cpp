#include "StdAfx.h"
#include "filestructure.h"

#include "CPU.h"
#include "Programm.h"
#include "Computer.h"


void CPU::readInputStream(FileStructure &fs) {
    unitsNumAssignment = fs.unitsNumAssignment;
    unitsNumOutput = fs.unitsNumOutput;
    unitsNumBeginMutualExclusion = fs.unitsNumBeginMutualExclusion;
    unitsNumEndMutualExclusion = fs.unitsNumEndMutualExclusion;
    unitsNumStopExecution = fs.unitsNumStopExecution;
}

size_t CPU::executeCommand(size_t programmID, const string& command) {
	size_t timeAmount = 0;
	if (command.substr(0, 6).compare("print ") == 0) {
        QString str;
        str = QString::number(programmID) + ": " + QString::number(computer->memory.getValue(command[6]));
        //computer->sendString(str);
        //sendSignal(str);
        //ui->mylistWidget->addItem(str);
        //programmID << ": " << computer->memory.getValue(command[6]);
        //cout << programmID << ": " << computer->memory.getValue(command[6]) << endl;

		timeAmount = unitsNumOutput;
	}
	else if (command.compare("lock") == 0) {
		bool res = lock.lockIt(programmID);
		// if the CPU is locked!
		if (!res) throw "CPU locked!";
		timeAmount = unitsNumBeginMutualExclusion;
	}
	else if (command.compare("unlock") == 0) {
		lock.unlockIt();
		timeAmount = unitsNumEndMutualExclusion;
	}
	else if (command.compare("end") == 0) {
		timeAmount = unitsNumStopExecution;
	}
	else {
		computer->memory.setValue(command[0], convertStringToInt(command.substr(4, command.length())));
		timeAmount = unitsNumAssignment;
	}
	return timeAmount;
}
