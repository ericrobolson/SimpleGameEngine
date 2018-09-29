#ifndef MESSAGEDEBUGGER_H
#define MESSAGEDEBUGGER_H
#include <string>
#include <iostream>

#define DEBUG

namespace Debugger{
    void DebugMessage(std::string message, int value = 0){
    #ifdef DEBUG
        std::cout << "Debug: " << message << " " << value << std::endl;

    #endif // DEBUG
    }

      void DebugMessage(std::string message, double value = 0){
    #ifdef DEBUG
        std::cout << "Debug: " << message << " " << value << std::endl;

    #endif // DEBUG
    }
}


#endif // MESSAGEDEBUGGER_H
