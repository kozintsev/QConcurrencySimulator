#include "filestructure.h"


FileStructure::FileStructure()
{
    nPrograms = 0;                    // the number of programs
    unitsNumQuantum = 0;              //
    unitsNumAssignment = 0;           // time units for operation: Assignment
    unitsNumOutput = 0;               // time units for operation: Output
    unitsNumBeginMutualExclusion = 0; // time units for operation: BeginMutualExclusion
    unitsNumEndMutualExclusion = 0;   // time units for operation: EndMutualExclusion
    unitsNumStopExecution = 0;        // time units for operation: StopExecution
}

