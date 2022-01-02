#include "replace.h"
#include "vm.h"
#include <vector>
#include <ncurses.h>

void Replace::runCommand(Vm* v) {
    std::vector<int> input;
    input = std::move((v->controller)->getInput());
    int c = input[1];
    int lines = getLine(v);

    if(c == 27) {
        v->mode = 'c';
    }
    else if (c == 10) {
        std::vector<char> tmp;
        for(size_t i = v->cursorX; i < ((v->file[v->cursorY-lines]).size() - 1);) {
            char tmpVal = (v->file[v->cursorY-lines])[i];
            std::cout<< tmpVal;
            tmp.push_back(tmpVal);
            (v->file[v->cursorY-lines]).erase((v->file[v->cursorY-lines]).begin() + i);
        }
        tmp.push_back('\n');
        (v->file).insert((v->file).begin() + (v->cursorY - lines) + 1, tmp);
        v->cursorY++;
        v->cursorX = 0;
    }
    else {
        int max = (v->file[v->cursorY - lines]).size() - 2;
        if(v->cursorX >= max) {
            v->cursorX = max;
            (v->file[v->cursorY - lines]).insert((v->file[v->cursorY - lines]).begin() + v->cursorX + 1, c);
        }
        else {
            (v->file[v->cursorY - lines])[v->cursorX] = c;
        }
        v->cursorX++;
    }
}
