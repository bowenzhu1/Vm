#include "vm.h"
#include "cursor.h"
#include "insert.h"
#include "edit.h"
#include "colon.h"
#include "replace.h"
#include "clip.h"
#include <string>
#include <vector>
#include <ncurses.h>

std::vector<std::vector<char>> Vm::getFile(std::ifstream &f) {
	std::vector<char> line;
	std::vector<std::vector<char>> file;
	f >> std::noskipws;
	char c;
	while(f >> c) {
		line.push_back(c);
		if(c == '\n') {
			file.push_back(line);
			line.clear();
		}
	}

	return file;
}

void Vm::run() {
	displayViews();
	std::string s;
	s = getCommand(mode);
	while (lineCount == 0) {
		if(mode == 'i') {
			command = std::make_unique<Edit>();
		}
		else if (mode == 'r') {
			command = std::make_unique<Replace>();
		}
		else if(s == "COLON") {
			command = std::make_unique<Colon>();
		}
		else if(s == "CURSOR") {
			command = std::make_unique<Cursor>();
		}
		else if(s == "INSERT") {
			command = std::make_unique<Insert>();
		}
		else if(s == "CLIP") {
			command = std::make_unique<Clip>();
		}
		if(s.length()) {
			std::vector<int> multiplier = controller->getInput();
			for(int i = 0; i < multiplier[0]; i++) {
				command->runCommand(this);
			}
		}
		if(lineCount != 0) {
			break;
		}
		if(mode == 'i') {
			status = "-- INSERT --";
		}
		else if (mode == 'r') {
			status = "-- REPLACE --";
		}
		else if (s == "STATUS") {
			status = filename;
		}
		else if (s == "COLON") {
			status = status;
		}
		else {
			status = "            ";
		}
		displayViews();
		refresh();
		s.clear();
		s = getCommand(mode);
	}
}
