#include "display.h"
#include <string>
#include <vector>
#include <ncurses.h>

void Display::displayView() {
	int tmpx = 0;
	int tmpy = 0;
	int charCount = 0;
	getmaxyx(stdscr, v->h, v->w);
	size_t hh = v->h;
	int total = 0;
    int tmp;
    size_t y = v->cursorY;
	move(tmpx, tmpy);
	size_t maxY = hh;
	int tmp2;
	int extraLines = 0;


	
	for(size_t i = 0; (i < v->file.size() && i < maxY - extraLines); i++) {
        tmp2 = (v->file[i]).size();
		while(tmp2 > v->w) {
            maxY--;
            tmp2 = tmp2 - v->w;
            extraLines++;            
        }
	}
	//std::cout << "l: " << v->lineCount << " y:" << v->cursorY << "   ";
	for(size_t i = 0; ((i < v->file.size()) && (i < hh)); i++) {
		for(size_t j = 0; j < (v->file[i]).size(); j++) {
			char c = v->file[i][j];
			if(tmpy + 1 < v->h - extraLines) {
				charCount++;
				addch(c);
			}
		}
		if(i < y) {
			tmp = (v->file[i]).size();
			while(tmp > v->w) {
				y--;
				tmp = tmp - v->w;
				total++;            
			}
		}
		tmpy++;
	}
	
	tmpx = 0;
	while(tmpy + 1 < v->h - extraLines) {
		char filler = '~';
		addch(filler);
		tmpy++;
		move(tmpy, tmpx);
	}

	for(size_t k = 0; k < v->status.length(); k++) {
		addch(v->status[k]);
	}
	while(tmpx < v->w - ((v->w)/4)) {
		addch(' ');
		tmpx++;
		move(tmpy, tmpx);
	}
	std::string rowsTmp = std::to_string(v->cursorY);
	const char* rows = rowsTmp.c_str();
	printw(rows);
	addch(',');

	int totalLine = 0;
    int tmpLine;
    size_t tmpMaxY = v->cursorY;
    for(size_t i = 0; (i < v->file.size() && i < tmpMaxY); i++) {
        tmp = (v->file[i]).size();
		while(tmpLine > v->w) {
            tmpMaxY--;
            tmpLine = tmpLine - v->w;
            totalLine++;            
        }
	}
	const char* cols;
	int compareX = (v->file[v->cursorY - totalLine]).size() - 1;
	if(compareX < v->cursorX) {
		std::string colsTmp = std::to_string(compareX);
		cols = colsTmp.c_str();
	}
	else {
		std::string colsTmp = std::to_string(v->cursorX);
		cols = colsTmp.c_str();
	}
	printw(cols);

	int	tmpx2 = v->cursorX;
	int wrapCounter = 0;
	int maxX = (v->file[v->cursorY - total]).size();
	int maxLine = maxX;
	while(tmpx2 >= v->w && maxLine >= v->w){
		tmpx2 -= v->w;
		maxLine -= v->w;
		wrapCounter++;
	}
	
	if (v->cursorX >= maxX - 2) {
		if(maxLine < 2) {
			maxLine = 2;
		}
		move(v->cursorY + wrapCounter, maxLine - 2);
	} 
	else {
		move(v->cursorY + wrapCounter, tmpx2);
	}


	refresh();
}
