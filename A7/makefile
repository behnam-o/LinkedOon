main: actions.o helpers.o main.o menu.o recipe.o system.o user.o warehouse.o
	g++ *.o -o main
actions.o: actions.cpp
	g++ -c actions.cpp
helpers.o: helpers.cpp
	g++ -c helpers.cpp
main.o: main.cpp actions.h system.h helpers.h user.h warehouse.h recipe.h menu.h reserve.h
	g++ -c main.cpp
recipe.o: recipe.cpp recipe.h helpers.h warehouse.h
	g++ -c recipe.cpp
system.o: system.cpp system.h helpers.h user.h warehouse.h recipe.h menu.h reserve.h
	g++ -c system.cpp
user.o: user.cpp user.h
	g++ -c user.cpp
warehouse.o: warehouse.cpp warehouse.h helpers.h
	g++ -c warehouse.cpp