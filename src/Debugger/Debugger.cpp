#include "Debugger.h"


#include <string>
#include <iostream>

using namespace SGE;
using namespace std;

Debugger::Debugger()
{
    //ctor
}

Debugger::~Debugger()
{
    //dtor
}

void Debugger::WriteMessage(string str){
    cout << str << endl;
}

void Debugger::ThrowException(string str){
    WriteMessage(str);
    throw str;
}
