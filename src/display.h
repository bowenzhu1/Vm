#ifndef DISPLAY_H
#define DISPLAY_H

#include "view.h"
#include "vm.h"
#include <ncurses.h>
#include <string>
#include <vector>
#include <memory>

class Display: public View {
	public:
		std::shared_ptr<Vm> v;

		Display(std::shared_ptr<Vm> v): v{v} {}
		void displayView() override;
		~Display() {};

};


#endif
