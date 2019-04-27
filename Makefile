Table.o: Table.cpp
	g++ -c Table.cpp
Member.o: Member.cpp
	g++ -c Member.cpp
main:Table.o Member.o
	g++ Table.o Member.o -o main
