#ifndef CPU_H
#define CPU_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStringListModel>
//#include <QObject>

//#include "mainwindow.h"
#include "filestructure.h"

class Computer;

/** lock object - a CPU has one LockObject */
class LockObject {
public:
	LockObject() : programmID(0) {}
	~LockObject() {}

	/** try to lock object - if success return true */
	bool lockIt(size_t programmID_) {
		if (programmID != 0) {
			return false;
		}
		programmID = programmID_;
		return true;
	}
	/** unlock object */
	void unlockIt() {
		programmID = 0;
	}
	/** gets lock state */
	size_t getLockState() const {
		return programmID;
	}


protected:
	/** program ID which is lock this object or 0 */
	size_t programmID;
};

/** commands processor */
class CPU {
public:
    CPU() : computer(0) {}
	~CPU() {}

	/** reads CPU init information from standard input stream */
    void readInputStream(FileStructure &fs);

	/** CPU executes one command for the Programm which id is programmID 
	 *  returns time units amount
	**/
    size_t executeCommand(size_t programmID, const string& command, std::string& out);

	/** sets Computer for CPU */
	void setComputer(Computer* computer_) {
		computer = computer_;
	}

	/** gets CPU lock state - if result 0 - CPU unlocked */
	size_t getLockState() const {
		return lock.getLockState();
    }

protected:
	/** time units for operation: Assignment */
	size_t unitsNumAssignment;
	/** time units for operation: Output */
	size_t unitsNumOutput;
	/** time units for operation: BeginMutualExclusion */
	size_t unitsNumBeginMutualExclusion;
	/** time units for operation: EndMutualExclusion */
	size_t unitsNumEndMutualExclusion;
	/** time units for operation: StopExecution */
	size_t unitsNumStopExecution;

	/** lock object for CPU - used for save CPU locking state */
	LockObject lock;
	/** the Computer for CPU */
    Computer* computer;
};


#endif // CPU_H
