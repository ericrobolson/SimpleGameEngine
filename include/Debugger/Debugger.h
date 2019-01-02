#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <string>
namespace SGE{
    class Debugger
    {
        public:
            static Debugger& Instance(){
                static Debugger *instance = new Debugger();
                return *instance;
            };
            virtual ~Debugger();

            void WriteMessage(std::string str);
            void ThrowException(std::string str);

        private:
            Debugger();

    };
}



#endif // DEBUGGER_H
