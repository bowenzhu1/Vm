#include "colon.h"
#include "vm.h"
#include <vector>
#include <ncurses.h>

int Colon::changesMade(std::vector<std::vector<char>> save, std::vector<std::vector<char>> file) {
    if(save.size() != file.size()) {
        return 1;
    }
    for(size_t i = 0; i < save.size(); i++) {
        if((save[i]).size() != (file[i]).size()) {
            return 1;
        }
        for(size_t j = 0; j < (save[i]).size(); j++) {
            if((save[i])[j] != (file[i])[j]) {
                return 1;
            }
        }
    }
    return 0;
}

void Colon::runCommand(Vm* v) {
    std::vector<int> input;
    input = std::move((v->controller)->getInput());
    int c = input[2];

    if(input.size() == 3) {
        if(c == 'w') {
            v->save = v->file;
            v->status = v->filename;
        }
        if(c == 'q') {
            if(changesMade(v->save, v->file) == 0) {
                v->lineCount = 1;
            }
            else {
                v->status = "No write since last change";
            }
        }
        if(c == '0') {
            v->cursorX = 0;
            v->cursorY = 0;
        }
        if(c == '$') {
            v->cursorY = (v->file).size();
            v->cursorX = ((v->file)[v->cursorY]).size();
        }
        if(c >= '0' && c <= '9') {
            int tmp = c - 48;
            int max = (v->file).size();
            if(tmp > max) {
                tmp = max;
            }
            if(tmp == 0) {
                tmp = 1;
            }
            v->cursorY = tmp;
            v->cursorX = 0;
        }
    }
    if(input.size() == 4) {
        if(c == 'w' && input[3] == 'q') {
            v->save = v->file;
            v->lineCount = 1;
        }
        if(c == 'q' && input[3] == '!') {
            v->lineCount = 1;
        }
        if(c >= '1' && c <= '9' && input[3] >= '1' && input[3] <= '9') {
            int tmp = 0;
            tmp += (c - 48) * 10;
            tmp += input[3] - 48;
            int max = (v->file).size();
            if(tmp > max) {
                tmp = max;
            }
            v->cursorY = tmp;
            v->cursorX = 0;
        }
    }

}
