#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <vector>

class Vm;

class Commands {
    std::vector<int> input;
    protected:
        int getLine(Vm* v);
    public:
        virtual void runCommand(Vm* v) =0;
        virtual ~Commands() {}; 
};

#endif
