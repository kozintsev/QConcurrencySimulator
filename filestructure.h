#ifndef FILESTRUCTURE_H
#define FILESTRUCTURE_H

#include <QMainWindow>
#include <QStringList>

static QStringList gQStrLisr; // глобальный список для вывода сообщений

static QStringList gMyConsoleData; // глобальный список для хранения данных из ListView

class FileStructure
{
public:
    FileStructure();
    size_t  nPrograms // the number of programs
            ,unitsNumQuantum
            ,unitsNumAssignment           // time units for operation: Assignment
            ,unitsNumOutput               // time units for operation: Output
            ,unitsNumBeginMutualExclusion // time units for operation: BeginMutualExclusion
            ,unitsNumEndMutualExclusion   // time units for operation: EndMutualExclusion
            ,unitsNumStopExecution        // time units for operation: StopExecution
            ;
    QStringList fileRead;


};

#endif // FILESTRUCTURE_H
