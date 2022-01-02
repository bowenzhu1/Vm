#ifndef COLON_H
#define COLON_H

#include "commands.h"
#include <string>
#include <vector>

class Colon: public Commands {
    int changesMade(std::vector<std::vector<char>> save, std::vector<std::vector<char>> file);
    public:
        void runCommand(Vm* v) override;
};

#endif
