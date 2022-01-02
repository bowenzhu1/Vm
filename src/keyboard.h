#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "controller.h"
#include <string>
#include <vector>
#include <map>

class Keyboard: public Controller {

	std::string command(int mode) override;
	
	public:
		std::map<int, std::string> theMap;
		std::vector<int> input;
		std::vector<char> clipboard;
		std::vector<int> getInput() override;
		Keyboard(std::vector<int>);
};

#endif
