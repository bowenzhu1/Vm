#ifndef CLIP_H
#define CLIP_H

#include "commands.h"
#include <string>
#include <vector>

class Clip: public Commands {
    public:
        void runCommand(Vm* v) override;
};

#endif
