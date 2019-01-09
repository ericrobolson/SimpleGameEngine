#include "InstructionMachine.h"

using namespace SGE_IM;

InstructionMachine::InstructionMachine()
{
    _status = MachineStatus::Standby;
}

InstructionMachine::~InstructionMachine()
{
    //dtor
}

int InstructionMachine::Peek(){
    if (_stackSize <= 0){
        throw "no value";
    }

    int index = _stackSize;

    return _stack[--index];
}


void InstructionMachine::Push(int i){
    if (_stackSize >= MAXSTACK){
        throw "stack overflow";
    }

    _stack[_stackSize++] = i;
}

int InstructionMachine::Pop(){
    if (_stackSize <= 0){
        throw "no value";
    }

    return _stack[--_stackSize];
}

void InstructionMachine::Execute(char bytecode[], int sizeOfInstructions){
    for (int i = 0; i < sizeOfInstructions; i++){
        char instruction = bytecode[i];
        switch (instruction){
            case InstructionMachine::Instructions::Literal:
                {
                    int value = bytecode[++i];
                    Push(value);
                }
                break;
            case InstructionMachine::Instructions::Add:
                {
                    int b = Pop();
                    int a = Pop();
                    Push(a + b);
                }
                break;
            case InstructionMachine::Instructions::Subtract:
                {
                    int b = Pop();
                    int a = Pop();
                    Push(a - b);
                }
                break;
             case InstructionMachine::Instructions::Multiply:
                {
                    int b = Pop();
                    int a = Pop();
                    Push(a * b);
                }
                break;
             case InstructionMachine::Instructions::Divide:
                {
                    int b = Pop();
                    int a = Pop();
                    Push(a / b);
                }
                break;
             case InstructionMachine::Instructions::ReadUserInputValue:
                {
                    Push(_userInputValue);
                }
                break;
            default:
                throw "Not a valid instruction.";
                break;
        }
    }

}
