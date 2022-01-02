#ifndef REPLACE_H
#define REPLACE_H

#include "commands.h"
#include <string>
#include <vector>

class Replace: public Commands {
    public:
        void runCommand(Vm* v) override;
};

#endif
