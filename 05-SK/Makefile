ifeq ($(OS), Windows_NT)
		EXECUTABLE=driver.exe
else
		EXECUTABLE=driver.out
endif

all: mytest.o rqueue.o
	g++ -Wall -Werror -std=c++11 mytest.o rqueue.o -o $(EXECUTABLE) 

mytest.o: mytest.cpp
	g++ -g -Wall -Werror -std=c++11 -c mytest.cpp

rqueue.o: rqueue.cpp rqueue.h
	g++ -g -Wall -Werror -std=c++11 -c rqueue.cpp

valgrind:
		valgrind -s --track-origins=yes ./driver.out

run:
		./$(EXECUTABLE)

clean:
		rm mytest.o
		rm rqueue.o
		rm *.out
