#include "insert.h"
#include "vm.h"
#include <vector>

void Insert::runCommand(Vm* v) {
    std::vector<int> input;
    input = std::move((v->controller)->getInput());
    int c = input[1];

    v->mode = 'i';
    if(c == 'i') {
        v->mode = 'i';
    } 
    if(c == 'I') {
        v->cursorX = 0;
    }  
    if(c == 'a') {
        v->cursorX = v->cursorX + 1;
    }  
    if(c == 'A') {
        int lines = getLine(v);
        v->cursorX = (v->file[v->cursorY - lines]).size();
    } 
    if(c == 'O') {
        int lines = getLine(v);
        std::vector<char> tmp;
        tmp.push_back('\n');
        (v->file).insert((v->file).begin() + (v->cursorY - lines), tmp);
        v->cursorX = 0;
    }
    if(c == 'o') {
        int lines = getLine(v);
        std::vector<char> tmp;
        tmp.push_back('\n');
        (v->file).insert((v->file).begin() + (v->cursorY - lines + 1), tmp);
        v->cursorY = v->cursorY + 1;
        v->cursorX = 0;
    }
    if(c == 'S') {
        int lines = getLine(v);
        v->clipboard = ((v->file)[v->cursorY - lines]);
        (v->file[v->cursorY - lines]).clear();
        (v->file[v->cursorY - lines]).push_back('\n');
        v->cursorX = 0;
    }
    if(c == 's') {
        int lines = getLine(v);
        if((v->file[v->cursorY - lines]).size() > 1) {
            std::vector<char> tmp;
            int tmpInt;
            tmpInt = (v->file[v->cursorY - lines])[v->cursorX];
            tmp.push_back(tmpInt);
            v->clipboard = tmp;
            (v->file[v->cursorY - lines]).erase((v->file[v->cursorY - lines]).begin() + v->cursorX);
            v->cursorX = v->cursorX;
        }
    }
    if(c == 'c' && input.size() == 3) {
        if(input[2] == 'c') {
            int lines = getLine(v);
            v->clipboard = ((v->file)[v->cursorY - lines]);
            (v->file[v->cursorY - lines]).clear();
            (v->file[v->cursorY - lines]).push_back('\n');
            v->cursorX = 0;
        }
    }
}
