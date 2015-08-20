#ifndef PROGRAMM_H
#define PROGRAMM_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStringListModel>

/** program - set of instructions for computer system */
class Programm {
public:
	enum TState { running, ready };
public:
	Programm(size_t ID_) : state(ready), ID(ID_), instructionsPointer(0), acceptMaxStatements(25) {}
	~Programm() {}

	size_t getID() const {
		return ID;
	}
	void setID(size_t ID_) {
		ID = ID_;
	}

	TState getState() const {
		return state;
	}
	void setStateRunning() {
		state = running;
	}
	void setStateReady() {
		state = ready;
	}

	/** reads the program instructions from standard input stream 
	 *  return true if success - false mean error
	 *  error - string error message
	**/
    bool readInputStream(string& error, std::string strLine);

	/** executes next program instruction 
	 *  instructionsPointer - point to executed instruction 
	 *  returns time units amount
	**/
    size_t nextInstruction(CPU& cpu, std::string &out);

protected:
	/** unique program identifier */
	size_t ID;
	/** current state of the program */
	TState state;
	/** code for program */
	vector<string> code;
	/** pointer to the next instruction of program to execute */
	size_t instructionsPointer;
	/** maximum statements for program */
	const size_t acceptMaxStatements;
};

#endif // PROGRAMM_H
