#include "catch.hpp"
#include "InstructionMachine.h"
using namespace SGE_IM;

SCENARIO("InstructionMachine::Execute: Literal"){
    InstructionMachine im;

    int sizeOfInstructions = 2;
    char bytecode[2];

    bytecode[0] = InstructionMachine::Instructions::Literal;
    bytecode[1] = 234;

    im.Execute(bytecode, sizeOfInstructions);

    REQUIRE(im.Peek() == bytecode[1]);
}

SCENARIO("InstructionMachine::Execute: Add"){
    InstructionMachine im;

    int sizeOfInstructions = 5;
    char bytecode[5];

    bytecode[0] = InstructionMachine::Instructions::Literal;
    bytecode[1] = 1;
    bytecode[2] = InstructionMachine::Instructions::Literal;
    bytecode[3] = 1;
    bytecode[4] = InstructionMachine::Instructions::Add;

    im.Execute(bytecode, sizeOfInstructions);

    REQUIRE(im.Peek() == 2);
}

SCENARIO("InstructionMachine::Execute: Subtract"){
    InstructionMachine im;

    int sizeOfInstructions = 5;
    char bytecode[5];

    bytecode[0] = InstructionMachine::Instructions::Literal;
    bytecode[1] = 1;
    bytecode[2] = InstructionMachine::Instructions::Literal;
    bytecode[3] = 4;
    bytecode[4] = InstructionMachine::Instructions::Subtract;

    im.Execute(bytecode, sizeOfInstructions);

    REQUIRE(im.Peek() == -3);
}

SCENARIO("InstructionMachine::Execute: Multiply"){
    InstructionMachine im;

    int sizeOfInstructions = 5;
    char bytecode[5];

    bytecode[0] = InstructionMachine::Instructions::Literal;
    bytecode[1] = 7;
    bytecode[2] = InstructionMachine::Instructions::Literal;
    bytecode[3] = 3;
    bytecode[4] = InstructionMachine::Instructions::Multiply;

    im.Execute(bytecode, sizeOfInstructions);

    REQUIRE(im.Peek() == 21);
}

SCENARIO("InstructionMachine::Execute: Divide"){
    InstructionMachine im;

    int sizeOfInstructions = 5;
    char bytecode[5];

    bytecode[0] = InstructionMachine::Instructions::Literal;
    bytecode[1] = 21;
    bytecode[2] = InstructionMachine::Instructions::Literal;
    bytecode[3] = 3;
    bytecode[4] = InstructionMachine::Instructions::Divide;

    im.Execute(bytecode, sizeOfInstructions);

    REQUIRE(im.Peek() == 7);
}
