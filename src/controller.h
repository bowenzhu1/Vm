#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>

class Controller {

	//std::map<int, std::string> theMap;
	
	virtual std::string command(int mode) =0;
	public:
		std::string getCommand(int mode);
		virtual std::vector<int> getInput() =0;
		virtual ~Controller() = default;
};

#endif
