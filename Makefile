CXX = g++ 
CXXFLAGS = -Wall -MMD
EXEC = cc3k
OBJECTS = main.o controller.o game.o map.o cell.o floor.o chamber.o character.o item.o potion.o gold.o monster.o pc.o vampire.o shade.o troll.o goblin.o drow.o dragon.o elf.o human.o orc.o halfling.o dwarf.o merchant.o robot.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

.PHONY: clean
