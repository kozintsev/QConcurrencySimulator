#include "StdAfx.h"

#include "CPU.h"
#include "Programm.h"

inline bool isLetter(string command)
{
  if (command.length() == 1 && ('a' <= command[0]) && (command[0] <='z'))
      return true;
    return false;
}

inline bool isLock(string command)
{
  if (command.compare("lock") == 0)
      return true;
    return false;
}

#define IS_UNLOCK(command)    (command.compare("unlock") == 0)
#define IS_END(command)       (command.compare("end") == 0)
#define IS_PRINT(command)     (command.compare("print") == 0)
#define IS_EQUATION(command)  (command.compare("=") == 0)

#define ERROR_UNKNOWN(ID, nLines, error)                       (error = "#progID " + \
	convertIntToString(ID) + " line " + convertIntToString(nLines) + ": unkown command")

#define ERROR_OUTRANGE(ID, nLines, error)                      (error = "#progID " + \
	convertIntToString(ID) + " line " + convertIntToString(nLines) + ": number out of range")

#define ERROR_EMPTYLINE(ID, nLines, error)                     (error = "#progID " + \
	convertIntToString(ID) + " line " + convertIntToString(nLines) + ": is empty line")

#define ERROR_TOOBIG(ID, nLines, error, acceptMaxStatements)   (error = "#progID " + \
	convertIntToString(ID) + " line " + convertIntToString(nLines) + \
	": too big program (only " + convertIntToString(acceptMaxStatements) + " statements accepted)")

bool Programm::readInputStream(string& error) {
	error.clear();
	const size_t num = 100;
	string::value_type line[num+1];
	string strLine;
	strLine.reserve(num);
	code.clear();
	const string::value_type delimiters[] = "\n\t\r\f\v ";
	size_t nLines = 0;
	for ( ; strLine.compare("end") && nLines < acceptMaxStatements; ++nLines) {
		cin.getline(line, num);
		strLine = string(line);
		trimStringRight(strLine, delimiters);
		if (strLine.empty()) {
			ERROR_EMPTYLINE(ID, nLines, error);
			return false;
		}
		string::size_type index = 0;
		string command = getToken(strLine, index, delimiters);
		if (index >= strLine.length()) {
            bool accept = isLock(command) || IS_UNLOCK(command) || IS_END(command) || isLetter(command);
			if (!accept) {
				ERROR_UNKNOWN(ID, nLines, error);
				return false;
			}
			code.push_back(command);
			continue;
		}
        bool accept = IS_PRINT(command) || isLetter(command);
		if (!accept) {
			ERROR_UNKNOWN(ID, nLines, error);
			return false;
		}
		string token = getToken(strLine, index, delimiters);
        accept = IS_PRINT(command) && isLetter(token);
		if (accept) {
			command += " " + token;
			code.push_back(command);
			continue;
		}
        accept = isLetter(command) && IS_EQUATION(token);
		if (index >= strLine.length() || !accept) {
			ERROR_UNKNOWN(ID, nLines, error);
			return false;
		}
		command += " " + token;
		token = getToken(strLine, index, delimiters);
		int num = convertStringToInt(token);
		if (num >= 100 || num < 0) {
			ERROR_OUTRANGE(ID, nLines, error);
			return false;
		}
		command += " " + token;
		code.push_back(command);
		if (index < strLine.length()) {
			ERROR_UNKNOWN(ID, nLines, error);
			return false;
		}
	}
	if (nLines >= acceptMaxStatements) {
		ERROR_TOOBIG(ID, nLines, error, acceptMaxStatements);
		return false;
	}
	return true;
}

size_t Programm::nextInstruction(CPU& cpu) {
	if (instructionsPointer >= code.size()) {
		// the program execute all its instructions
		return 0;
	}
	size_t units = cpu.executeCommand(ID, code[instructionsPointer]);
	instructionsPointer++;
	return units;
}
