#include "InstructionMachine.h"

using namespace SGE_IM;

InstructionMachine::InstructionMachine()
{
    _status = MachineStatus::Standby;
    _instructionIndex = 0;
}

InstructionMachine::~InstructionMachine()
{
    //dtor
}

MachineStatus InstructionMachine::GetStatus(){
    return _status;
}

int InstructionMachine::Peek(){
    if (_stackSize <= 0){
        throw "No value on stack.";
    }

    int index = _stackSize;

    return _stack[--index];
}

void InstructionMachine::SetUserValue(int value){
    _userInputValue = value;
    _status = MachineStatus ::ReadyToResumeExecution;
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
    if (sizeOfInstructions <= 0){
        throw "sizeOfInstructions must be greater than 0.";
    }

    _instructions = bytecode;
    _sizeOfInstructions = std::make_shared<int>(sizeOfInstructions);
    _instructionIndex = 0;
    _status = MachineStatus ::Executing;

    Execute();
}

void InstructionMachine::ResumeExecution(){
    Execute();
}

void InstructionMachine::Execute(){
    if (_sizeOfInstructions == nullptr || _status == MachineStatus::WaitingForInput || (*_sizeOfInstructions) <= 0){
        return;
    }

    int sizeOfInstructions = *_sizeOfInstructions;

    while (_instructionIndex < sizeOfInstructions){
        char instruction = _instructions[_instructionIndex];
        switch (instruction){
            case InstructionMachine::Instructions::Literal:
                {
                    int value = _instructions[++_instructionIndex];
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

        _instructionIndex++;

    }

    // Set state to standby, clear instructions
    _sizeOfInstructions.reset();
    _status = MachineStatus::Standby;
}
