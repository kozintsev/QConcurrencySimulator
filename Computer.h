#ifndef Computer_H
#define Computer_H

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
class Computer {
	friend CPU;
public:
	Computer();
	virtual ~Computer();

	/** reads Computer init information from standard input stream */
	void readInputStream();

	/** loads nPrograms to the system (reads its from standard input stream) */
	bool loadProgramms(size_t nPrograms);

	/** clear all programs */
	void unloadProgramms();

	/** execute programs calculation */
	void calculate();

protected:
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
};

#endif // FILESTRUCTURE_H
