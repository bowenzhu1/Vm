#include "clip.h"
#include "vm.h"
#include <vector>
#include <ncurses.h>

void Clip::runCommand(Vm* v) {
    std::vector<int> input;
    input = std::move((v->controller)->getInput());
    int c = input[1];
    int lines = getLine(v);
    if(c == 'y' && input.size() == 3) {
        if(input[2] == 'y') {
            v->clipboard = ((v->file)[v->cursorY - lines]);
        }
    }
    if(c == 'x') {
        int tmpMax = ((v->file)[v->cursorY - lines]).size() - 1;
        std::vector<char> tmp;
        int tmpInt;
        if(v->cursorX > tmpMax) {
            v->cursorX = tmpMax;
        }
        if(v->cursorX < tmpMax - 1) {
            tmpInt = (v->file[v->cursorY - lines])[v->cursorX];
            tmp.push_back(tmpInt);
            v->clipboard = tmp;
            ((v->file)[v->cursorY - lines]).erase(((v->file)[v->cursorY - lines]).begin() + v->cursorX);

        }
        if(v->cursorX == tmpMax - 1) {
            tmpInt = (v->file[v->cursorY - lines])[v->cursorX];
            tmp.push_back(tmpInt);
            v->clipboard = tmp;
            ((v->file)[v->cursorY - lines]).erase(((v->file)[v->cursorY - lines]).begin() + v->cursorX);
            if(v->cursorX != 0) {
                v->cursorX--;
            }
        }
    }
    if(c == 'X') {
        int tmpMax = ((v->file)[v->cursorY - lines]).size() - 1;
        std::vector<char> tmp;
        int tmpInt;
        if(v->cursorX > tmpMax) {
            v->cursorX = tmpMax;
        }
        if(v->cursorX != 0) {
            tmpInt = (v->file[v->cursorY - lines])[v->cursorX - 1];
            tmp.push_back(tmpInt);
            v->clipboard = tmp;
            ((v->file)[v->cursorY - lines]).erase(((v->file)[v->cursorY - lines]).begin() + v->cursorX - 1);
            v->cursorX--;
        }
    }
    if(c == 'p') {
        if(v->clipboard.size() > 1) {
            (v->file).insert((v->file).begin() + (v->cursorY - lines), v->clipboard);
        }
        else if (v->clipboard.size() == 1){
            int tmpMax = ((v->file)[v->cursorY - lines]).size() - 1;
            if(v->cursorX > tmpMax) {
                v->cursorX = tmpMax;
            }
            ((v->file)[v->cursorY - lines]).insert(((v->file)[v->cursorY - lines]).begin() + v->cursorX, v->clipboard[0]);
        }
    }
    if(c == 'P') {
        if(v->clipboard.size() > 1) {
            (v->file).insert((v->file).begin() + (v->cursorY - lines) + 1, v->clipboard);
        }
        else if (v->clipboard.size() == 1){
            int tmpMax = ((v->file)[v->cursorY - lines]).size() - 1;
            if(v->cursorX > tmpMax) {
                v->cursorX = tmpMax;
            }
            if(tmpMax == 0) {
                ((v->file)[v->cursorY - lines]).insert(((v->file)[v->cursorY - lines]).begin(), v->clipboard[0]);
            }
            else {
                ((v->file)[v->cursorY - lines]).insert(((v->file)[v->cursorY - lines]).begin() + v->cursorX + 1, v->clipboard[0]);
            }
        }

    }

    if(c == 'R') {
        v->mode = 'r';
    }
    if(c == 'r' && input.size() == 3) {
        if(input[2] != 10) { //enter 
            if ((v->file[v->cursorY - lines])[v->cursorX] != '\n') {
                (v->file[v->cursorY - lines])[v->cursorX] = input[2];
            }
        }
        else {
            
        }
    }
    if(c == 'J') {
        int tmp = (v->file).size() - 1;
        if(v->cursorY - lines < tmp) {
            int tmpX = (v->file[v->cursorY - lines]).size();
            (v->file[v->cursorY - lines]).pop_back();
            for(size_t i = 0; i < ((v->file)[v->cursorY - lines + 1]).size(); i++) {
                (v->file[v->cursorY - lines]).push_back((v->file[v->cursorY - lines + 1])[i]);
            }
            (v->file).erase((v->file).begin() + (v->cursorY - lines + 1));
            v->cursorX = tmpX;
        }
    }

    if(c == 'd' && input.size() == 3) {
        if(input[2] == 'd') {
            v->clipboard = ((v->file)[v->cursorY - lines]);
            (v->file).erase((v->file).begin() + (v->cursorY - lines));
            for(size_t i = 0; i < (v->file[v->cursorY - lines]).size(); i++) {
                if((v->file[v->cursorY - lines])[i] != ' ' && (v->file[v->cursorY - lines])[i]  != 9) {
                    v->cursorX = i;
                    break;
                }
            }
        }
    }
}
