#ifndef VM_H
#define VM_H

#include "model.h"
#include "commands.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Vm: public Model {
	public:
		int cursorY;
		int cursorX;
		std::string filename;
		std::vector<std::vector<char>> save;
		std::vector<std::vector<char>> file;
		std::vector<char> clipboard;
		std::string status;
		int h;
		int w;
		int lineCount;
		int mode;
		std::unique_ptr<Commands> command;

		Vm(int cursorY, int cursorX, std::string filename, std::vector<std::vector<char>> file, std::string status, int h, int w, int lineCount, int mode, std::unique_ptr<Commands> command): 
       			cursorY{cursorY}, cursorX{cursorX}, filename{filename}, file{std::move(file)}, status{status}, h{h}, w{w}, lineCount{lineCount}, mode{mode}, command{std::move(command)} {}
		std::vector<std::vector<char>> getFile(std::ifstream &f);
		void run();
		~Vm() {};

};

#endif
