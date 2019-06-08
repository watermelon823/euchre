CXX=g++
CXXFLAGS=-std=c++14 -Wall -Werror -g -MMD
EXEC=euchre
OBJECTS=card.o deck.o Hand.o Player.o HumanPlayer.o ComputerPlayer.o Game.o main.o MyDisplay.o window.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -L/usr/X11R6/lib -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

.PHONY: clean
