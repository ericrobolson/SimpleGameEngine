#ifndef COMMANDPATTERN_H
#define COMMANDPATTERN_H

namespace SGE_Patterns
{
    class CommandPattern
    {
        public:
            virtual void CommandPattern() = 0;
            virtual ~CommandPattern() {}

            virtual void Execute() = 0;
            virtual void Undo() = 0;
            virtual void Redo() = 0;
    };
}


#endif // COMMANDPATTERN_H
