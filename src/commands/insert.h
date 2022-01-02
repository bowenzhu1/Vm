#ifndef INSERT_H
#define INSERT_H

#include "commands.h"
#include <string>
#include <vector>

class Insert: public Commands {
    public:
        void runCommand(Vm* v) override;
};

#endif
