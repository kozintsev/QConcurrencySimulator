#ifndef Computer_H
#define Computer_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStringListModel>
#include <QObject>

#include "mainwindow.h"
#include "filestructure.h"

/** Computer memory */
class Memory {
public:
	Memory() {
		clear();
	}
	~Memory() {}

	/** clear memory to zero state */
	void clear() {
		memset(variables, 0, sizeof(variables));
	}

	/** gets variable value */
	size_t getValue(char place) const;

	/** assign variable at place given value */
	void setValue(char place, size_t value);
protected:
	/** there are only 26 variables in the computer system */
	size_t variables[26];
};

/** Computer system */
class Computer : public QMainWindow {

    friend class CPU;

//Q_OBJECT

public:
    Computer();
	virtual ~Computer();

	/** reads Computer init information from standard input stream */
    void readInputStream(FileStructure &fs);

	/** loads nPrograms to the system (reads its from standard input stream) */
    bool loadProgramms(size_t nPrograms, std::string strLine, std::string &out);

	/** clear all programs */
	void unloadProgramms();

	/** execute programs calculation */
    void calculate(std::string &out);

//    void sendSignal(const QString& str)
//    {
//        emit sendString(str);
//    }

protected:
    MainWindow *ui;
	/** Computer system CPU */
	CPU cpu;
	/** Computer system Memory */
    Memory memory;
	/** The running program is permitted to continue executing instructions 
	 *  for a period of time called its quantum - this is unitsNumQuantum
	**/
	size_t unitsNumQuantum;
	/** vector of pointers to the loaded programs */
	vector<Programm*> programmsBatch;
	/** queue of blocked programs */
	queue<Programm*, list<Programm*> > blockedQueue;
	/** queue of running programs */
	queue<Programm*, list<Programm*> > readyQueue;
	/** maximum programs accepted */
	const size_t acceptMaxPrograms;
    FileStructure* _fs;

//signals:
//    void sendString(const QString&);

};

#endif // FILESTRUCTURE_H
