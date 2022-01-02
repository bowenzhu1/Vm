#include "commands.h"
#include "vm.h"

int Commands::getLine(Vm* v) {
    int total = 0;
    int tmp;
    size_t y = v->cursorY;
    for(size_t i = 0; (i < v->file.size() && i < y); i++) {
        tmp = (v->file[i]).size();
		while(tmp > v->w) {
            y--;
            tmp = tmp - v->w;
            total++;            
        }
	}
    return total;
}
