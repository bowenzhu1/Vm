#include "model.h"
#include <vector>
#include <string>

void Model::addViews(std::shared_ptr<View> newView) {
	view = std::move(newView);
}

void Model::addControllers(std::unique_ptr<Controller>&& newController) {
	controller = std::move(newController);
}

void Model::displayViews() {
	view->displayView();
}

std::string Model::getCommand(int mode) {
	return controller->getCommand(mode);
}
