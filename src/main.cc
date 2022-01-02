#include "display.h"
#include "keyboard.h"
#include <fstream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

int main(int argc, char *argv[]) {
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	string filename;
	vector<vector<char>> file;
	string status;
	vector<int> input;
	shared_ptr<Vm> vm;
	shared_ptr<Display> display;
	unique_ptr<Keyboard> keyboard;

	if(argc == 1) {
		vector<char> tmpVec;
		tmpVec.push_back('\n');
		file.push_back(tmpVec);
		filename = " ";
		status = filename;
		vm = make_shared<Vm>(0, 0, filename, file, status, 0, 0, 0,'c', nullptr);
		display = make_shared<Display>(vm);
		vm->addViews(display);
		keyboard = make_unique<Keyboard>(input);
		vm->addControllers(move(keyboard));
		vm->save = file;
		vm->run();
	}
	else if(argc == 2) {
		filename = argv[1];
		status = filename;
		ifstream f{argv[1]};
		vm = make_shared<Vm>(0, 0, filename, file, status, 0, 0, 0,'c', nullptr);
		display = make_shared<Display>(vm);
		vm->addViews(display);
		keyboard = make_unique<Keyboard>(input);
		vm->addControllers(move(keyboard));
		vm->file = vm->getFile(f);
		vm->save = vm->getFile(f);	
		vm->run();
		f.open(filename, ofstream::out | ofstream::trunc);
	}
	else {
		cout << "USAGE: ./vm [FILE]";
		return 2;
	}
	endwin();

	ofstream g{filename};
	char c;
	for(size_t i = 0; i < vm->save.size(); i++) {
		for(size_t j = 0; j < (vm->save[i]).size(); j++) {
			c = vm->save[i][j];
			g << c;
		}
	}

	return 0;
}
