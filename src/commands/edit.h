#ifndef EDIT_H
#define EDIT_H

#include "commands.h"
#include <string>
#include <vector>

class Edit: public Commands {
    public:
        void runCommand(Vm* v) override;
};

#endif
