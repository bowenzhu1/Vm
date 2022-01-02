#include "edit.h"
#include "vm.h"
#include <vector>
#include <ncurses.h>

void Edit::runCommand(Vm* v) {
    std::vector<int> input;
    input = std::move((v->controller)->getInput());
    int c = input[1];
    int lines = getLine(v);

    if(c == 27) { //esc
        v->mode = 'c';
        int tmp = (v->file[v->cursorY - lines]).size();
        if(v->cursorX == 0) {
            v->cursorX = v->cursorX;
        }
        else {
            if(v->cursorX >= tmp) {
                v->cursorX = tmp - 3;
            }
            else {
                v->cursorX = v->cursorX - 1;
            }        
        }
    }
    else if(c == KEY_BACKSPACE) { //
        if(v->cursorX == 0) {
            if((v->cursorY - lines) > 0) {
                int tmp = (v->file).size() - 1;
                if(v->cursorY - lines < tmp) {
                    if((v->file[v->cursorY - lines]).size() != 1) {
                        int tmpX = (v->file[v->cursorY - lines - 1]).size();
                        (v->file[v->cursorY - lines - 1]).pop_back();
                        for(size_t i = 0; i < ((v->file)[v->cursorY - lines]).size(); i++) {
                            (v->file[v->cursorY - lines - 1]).push_back((v->file[v->cursorY - lines])[i]);
                        }
                        (v->file).erase((v->file).begin() + (v->cursorY - lines));
                        int counter = 1;
                        int tmp2 = ((v->file)[v->cursorY - lines - 1]).size();
                        while(tmp2 > v->w) {
                            tmp2 -= v->w;
                            counter++;
                        }
                        v->cursorY = v->cursorY - counter;
                        v->cursorX = tmpX - 1;
                    }
                }
            }
        }
        else {
            (v->file[v->cursorY - lines]).erase((v->file[v->cursorY - lines]).begin() + v->cursorX - 1);
            int tmp = (v->file[v->cursorY - lines]).size();
            if(v->cursorX == 0) {
                v->cursorX = v->cursorX;
            }
            else {
                if(v->cursorX >= tmp) {
                    v->cursorX = tmp - 3;
                }
                else {
                    v->cursorX = v->cursorX - 1;
                }        
            }
        }
        
    }
    else if(c == 10) { //enter
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
        int max = ((v->file)[v->cursorY-lines]).size() - 1;
        if(v->cursorX > max) {
            v->cursorX = max;
        }
        ((v->file)[v->cursorY - lines]).insert(((v->file)[v->cursorY - lines]).begin() + v->cursorX, 1, c);
        v->cursorX = v->cursorX + 1;
    }

}
