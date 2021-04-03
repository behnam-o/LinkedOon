main: main.o utils.o operator.o operand.o
	g++ -o main main.o utils.o operator.o operand.o
main.o: main.cpp utils.h operand.h operator.h node.h
	g++ -c main.cpp
utils.o: utils.cpp utils.h operand.h operator.h node.h
	g++ -c utils.cpp
operator.o: operator.cpp operator.h node.h
	g++ -c operator.cpp
operand.o: operand.cpp utils.h operand.h operator.h node.h
	g++ -c operand.cpp