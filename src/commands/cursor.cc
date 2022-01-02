#include "cursor.h"
#include "vm.h"
#include <vector>

void Cursor::runCommand(Vm* v) {
    std::vector<int> input;
    input = std::move((v->controller)->getInput());
    int c = input[1];
    int lines = getLine(v);

    if(c == 'f' && input.size() == 3) {
        size_t tmpx = v->cursorX;
        for(size_t i = tmpx + 1; i < (v->file[v->cursorY - lines]).size(); i++) {
            if((v->file[v->cursorY - lines])[i] == input[2]) {
                v->cursorX = i;
                break;
            }
        }
    }
    if(c == 'F' && input.size() == 3) {
        size_t tmpx = v->cursorX;
        if(tmpx > ((v->file[v->cursorY - lines]).size())) {
            tmpx = ((v->file[v->cursorY - lines]).size());
        }
        for(size_t i = tmpx; i > 0; i--) {
            if((v->file[v->cursorY - lines])[i - 1] == input[2]) {
                v->cursorX = i - 1;
                break;
            }
        }
    }
    if(c == 'h') {
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
    if(c == 'l') {
        int tmp = (v->file[v->cursorY - lines]).size();
        if(v->cursorX >= tmp - 2) {
            v->cursorX = v->cursorX;
        }
        else {
            v->cursorX = v->cursorX + 1;
        }
    }
    if(c == 'j') {
        int tmp = (v->file[v->cursorY - lines]).size();
        int maxSize = v->file.size() - 1;
        if(v->cursorY < v->h - 2 && v->cursorY < maxSize) {
            int counter = 1;
            while(tmp > v->w) {
                tmp -= v->w;
                counter++;
            }
            v->cursorY = v->cursorY + counter;
        }
        //else {
        //    int fileLength = v->file.size();
        //    if((v->cursorY - lines) < fileLength) {
        //        v->lineCount++;
        //    }
        //}
    }    
    if(c == 'k') {
        if(v->cursorY > 0) {
            int tmp = (v->file[v->cursorY - lines - 1]).size();
            int counter = 1;
            while(tmp > v->w) {
                tmp -= v->w;
                counter++;
            }
            v->cursorY = v->cursorY - counter;
            
        }
        //else {
        //    if((v->cursorY - lines) > 0) {
        //        v->lineCount--;
        //    }
        //}
    }
    if(c == '^') {
        for(size_t i = 0; i < (v->file[v->cursorY - lines]).size(); i++) {
            if((v->file[v->cursorY - lines])[i] != ' ' && (v->file[v->cursorY - lines])[i]  != 9) {
                v->cursorX = i;
                break;
            }
        }
    }
    if(c == '$') {
        v->cursorX = (v->file[v->cursorY - lines]).size() - 1;
    }
    if(c == '0') {
        v->cursorX = 0;
    }
    if(c == 'b') {
        int found = 0;
        int counter = 0;
        int tmpX = v->cursorX;
        int tmpY = v->cursorY;
        int size = (v->file[v->cursorY - lines]).size();
        if(v->cursorX > size) {
            tmpX = (v->file[v->cursorY - lines]).size() - 1;
        }
        while (!found) {
            if((tmpX == 0 || tmpX == 1) && counter != 0) {
                v->cursorX = tmpX;
                v->cursorY = tmpY;
                found = 1;
                break;
            }
            for(size_t i = tmpX; i > 0; i--) {
                int j = i;
                if(((v->file[tmpY - lines])[i - 1] == ' ' || (v->file[tmpY - lines])[i - 1]  == 9 || (v->file[tmpY - lines])[i - 1]  == '\n')
                && ((v->file[tmpY - lines])[i] != ' ' && (v->file[tmpY - lines])[i]  != 9 && (v->file[tmpY - lines])[i]  != '\n' &&  j != tmpX)) {
                    v->cursorX = i;
                    v->cursorY = tmpY;
                    found = 1;
                    break;
                }
                if(i == 1 && ((v->file[tmpY - lines])[i] != ' ' && (v->file[tmpY - lines])[i]  != 9 && (v->file[tmpY - lines])[i]  != '\n')) {
                    v->cursorX = i - 1;
                    v->cursorY = tmpY;
                    found = 1;
                    break;
                }
            }
            if(found) {
                break;
            }
            if(tmpY == 0) {
                found = 1;
            }
            else {
                tmpY = tmpY - 1;
                v->cursorY = v->cursorY - 1;
                counter++;
                lines = getLine(v);
                tmpX = (v->file[tmpY - lines]).size() - 1;
            }
        }
        if(!found) {
            v->cursorY += counter;
        }
    }
    if(c == 'w') {
        int found = 0;
        int counter = 0;
        int tmpX = v->cursorX;
        int tmpY = v->cursorY;
        int size = (v->file[v->cursorY - lines]).size();
        if(v->cursorX > size) {
            tmpX = (v->file[v->cursorY - lines]).size() - 1;
        }
        while (!found) {
            if((tmpX == 0 || tmpX == 1) && counter != 0) {
                v->cursorX = tmpX;
                v->cursorY = tmpY;
                found = 1;
                break;
            }
            for(size_t i = tmpX; i < (v->file[v->cursorY - lines]).size(); i++) {
                int j = i;
                if(((v->file[tmpY - lines])[i - 1] == ' ' || (v->file[tmpY - lines])[i - 1]  == 9 || (v->file[tmpY - lines])[i - 1]  == '\n')
                && ((v->file[tmpY - lines])[i] != ' ' && (v->file[tmpY - lines])[i]  != 9 && (v->file[tmpY - lines])[i]  != '\n' &&  j != tmpX)) {
                    v->cursorX = i;
                    v->cursorY = tmpY;
                    found = 1;
                    break;
                }
            }
            if(found) {
                break;
            }
            if(v->cursorY >= v->h - 2) {
                found = 1;
            }
            else {
                int tmp = (v->file[v->cursorY - lines]).size();
                int count = 1;
                while(tmp > v->w) {
                    tmp -= v->w;
                    count++;
                }
                tmpY = tmpY + count;
                v->cursorY = v->cursorY + count;
                counter += count;
                lines = getLine(v);
                tmpX = 0;
            }
        }
        if(!found) {
            v->cursorY += counter;
        }
    }
}
