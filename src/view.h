#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <string>

class View {
	public:
		virtual void displayView() =0;
		virtual ~View() = default;
		//virtual void update() =0;

};

#endif
