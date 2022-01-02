#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <vector>
#include "controller.h"
#include "view.h"

class Model {
	protected:
		std::string getCommand(int mode);
	public:
		std::shared_ptr<View> view;
		std::unique_ptr<Controller> controller;
		void addViews(std::shared_ptr<View> newView);
		void addControllers(std::unique_ptr<Controller>&& newController);
		virtual ~Model() {};
		void updateViews(int cursorY, int cursorX, std::string status);
		void displayViews();
};

#endif
