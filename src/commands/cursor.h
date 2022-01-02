#ifndef CURSOR_H
#define CURSOR_H

#include "commands.h"
#include <string>
#include <vector>

class Cursor: public Commands {
    public:
        void runCommand(Vm* v) override;
};

#endif
