#include "keyboard.h"
#include <ncurses.h>
#include <vector>
#include <string>
#include <iostream>

Keyboard::Keyboard(std::vector<int> input): input{input} {
	theMap['h'] = "CURSOR";
	theMap['j'] = "CURSOR";
	theMap['k'] = "CURSOR";
	theMap['l'] = "CURSOR";
	theMap['^'] = "CURSOR";
	theMap['$'] = "CURSOR";
	theMap['0'] = "CURSOR";
	theMap['b'] = "CURSOR";
	theMap['w'] = "CURSOR"; 
	theMap['/'] = "CURSOR"; //
	theMap['?'] = "CURSOR"; //
	theMap['f'] = "CURSOR";
	theMap['F'] = "CURSOR";

	theMap['i'] = "INSERT"; 
	theMap['I'] = "INSERT";
	theMap['a'] = "INSERT";
	theMap['A'] = "INSERT";
	theMap['O'] = "INSERT";
	theMap['o'] = "INSERT";
	theMap['S'] = "INSERT";
	theMap['s'] = "INSERT";
	theMap['c'] = "INSERT";

	theMap['r'] = "CLIP";
	theMap['R'] = "CLIP";
	theMap['J'] = "CLIP";
	theMap['d'] = "CLIP";
	theMap['x'] = "CLIP";
	theMap['X'] = "CLIP";
	theMap['p'] = "CLIP";
	theMap['P'] = "CLIP";
	theMap['y'] = "CLIP";
	//theMap[7] = "STATUS"; //ctrl g 
	theMap[':'] = "COLON";

}

std::vector<int> Keyboard::getInput() {
	return input;
}

std::string Keyboard::command(int mode) {
	int c;
	c = getch();

	if(mode == 'i') {
		input.clear();
		input.push_back(1);
		input.push_back(c);
		std::string edit = "EDIT";
		return edit;
	}
	if(mode == 'r') {
		input.clear();
		input.push_back(1);
		input.push_back(c);
		std::string replace = "REPLACE";
		return replace;
	}
		
	if(c == '.') {
		return theMap[input[1]];
	}
	if(c == ';') {
		if(input[1] == 'f' || input[1] == 'F') {
			return theMap[input[1]];
		}
	}

	input.clear();
	input.push_back(1);
	if(c) {
		if(c == 7) {
			input.push_back(c);
		}
		else if(c >= '1' && c <= '9') {
			int tmp = c - 49;
			input[0] += tmp;
			c = getch();
		}
		else {
			input.push_back(c);
		}
	}
	if(input.size() > 0 && input[1] == ':') {
		c = getch();
		while(c != 10) {
			input.push_back(c);
			c = getch();
		}
	}
	if(input[1] == 'c') {
		c = getch();
		if(c == 'c') {
			input.push_back(c);
		}
	}
	if(input[1] == 'f' || input[1] == 'F' || input[1] == 'r' || input[1] == 'd' || input[1] == 'y') {
		c = getch();
		input.push_back(c);
	}
	return theMap[input[1]];
}
