#include "controller.h"
#include <string>

std::string Controller::getCommand(int mode) {
	return command(mode);
}
