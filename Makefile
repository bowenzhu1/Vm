CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = vm
OBJECTS = main.o controller.o display.o model.o vm.o keyboard.o commands.o cursor.o insert.o edit.o colon.o clip.o replace.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lncurses

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

